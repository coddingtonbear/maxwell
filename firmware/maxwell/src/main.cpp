#include <CANCommand.h>
#include "main.h"
#include <Arduino.h>
#undef min
#undef max
#include <HardwareCAN.h>
#include <libmaple/iwdg.h>
#include <SdFat.h>
#include <SPI.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include <SC16IS750.h>
#include <multiserial.h>

#include "multiserial.h"
#include "can_message_ids.h"
#include "power.h"
#include "neopixel.h"
#include "serial_commands.h"
#include "power.h"
#include "can.h"
#include "pin_map.h"
#include "main.h"
#include "lte.h"
#include "status.h"
#include "tasks.h"
#include "bluetooth.h"
#include "util.h"


SC16IS750 LTEUart = SC16IS750(
    PIN_SPI_CS_B,
    SC16IS750_CHAN_A,
    14745600UL
);

MultiSerial Output;

HashMap<String, double> Statistics;

SdFat filesystem(2);

Logger Log(&filesystem);

RTClock Clock(RTCSEL_LSE);

SPIClass SPIBus(2);

void setup() {
    afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY);
    iwdg_init(IWDG_PRE_256, 4095);

    util::beep(CHIRP_INIT_FREQUENCY, CHIRP_INIT_DURATION);

    Output.addInterface(&BTSerial);
    Output.begin(230400, SERIAL_8E1);
    Output.println("[Maxwell 2.0]");
    Output.flush();

    if(Clock.getTime() < 100000) {
        restoreBackupTime();
    }

    Wire.begin();
    power::init();

    SPIBus.begin();
    LTEUart.setSpiBus(&SPIBus);
    LTEUart.begin(115200, true);
    bool ltePinged = false;
    if(!LTEUart.ping()) {
        Output.println("Error connecting to UART over SPI; no LTE available.");
    } else {
        ltePinged = true;
        LTEUart.GPIOSetPinMode(PIN_LTE_DTR, OUTPUT);
        LTEUart.GPIOSetPinMode(PIN_LTE_OE, OUTPUT);
        LTEUart.GPIOSetPinState(PIN_LTE_DTR, LOW);
        LTEUart.GPIOSetPinState(PIN_LTE_OE, HIGH);
    }

    if(!filesystem.begin(PIN_SPI_CS_A, SD_SCK_MHZ(4))) {
        filesystem.initErrorPrint(&Output);
    }
    Log.begin();
    Log.log(String("Device reset: ") + String(RCC_BASE->CSR, HEX));
    Output.print("Device reset: ");
    if(RCC_BASE->CSR & (1 << 31)) {
        Log.log("Reset reason: Low Power");
        Output.println("Low Power");
    }
    if(RCC_BASE->CSR & (1 << 30)) {
        Log.log("Reset reason: Window Watchdog");
        Output.println("Window Wathdog");
    }
    if(RCC_BASE->CSR & (1 << 29)) {
        Log.log("Reset reason: Independent Watchdog");
        Output.println("Independent Wathdog");
    }
    if(RCC_BASE->CSR & (1 << 28)) {
        Log.log("Reset reason: Software Reset");
        Output.println("Software Reset");
    }
    if(RCC_BASE->CSR & (1 << 27)) {
        Log.log("Reset reason: POR/PDR");
        Output.println("POR/PDR");
    }
    if(RCC_BASE->CSR & (1 << 26)) {
        Log.log("Reset reason: NRST");
        Output.println("NRST");
    }
    if(RCC_BASE->CSR & (1 << 25)) {
        Log.log("Reset reason: BOR");
        Output.println("BOR");
    }
    // Clear reset flags
    RCC_BASE->CSR |= RCC_CSR_RMVF;

    digitalWrite(PIN_CAN_RS, LOW);
    pinMode(PIN_CAN_RS, OUTPUT);
    pinMode(PIN_BUZZER, OUTPUT);
    digitalWrite(PIN_BUZZER, LOW);
    digitalWrite(PIN_BT_KEY, LOW);
    pinMode(PIN_BT_KEY, OUTPUT);
    digitalWrite(PIN_BT_DISABLE_, HIGH);
    pinMode(PIN_BT_DISABLE_, OUTPUT);

    pinMode(PIN_I_POWER_ON, INPUT_PULLUP);

    delay(100);

    CanBus.map(CAN_GPIO_PB8_PB9);
    CanBus.begin(CAN_SPEED_1000, CAN_MODE_NORMAL);
    CanBus.filter(0, 0, 0);
    CanBus.set_poll_mode();

    CanMsg wakeMessage;
    wakeMessage.IDE = CAN_ID_STD;
    wakeMessage.RTR = CAN_RTR_DATA;
    wakeMessage.ID = CAN_MAIN_MC_WAKE;
    wakeMessage.DLC = 0;
    CanBus.send(&wakeMessage);

    tasks::init();
    neopixel::init();
    can::init();
    console::init();
    status::init();

    if(ltePinged) {
        lte::asyncEnable();
    }

    console::prompt();

    Output.println("Ready.");
    Output.flush();
    Log.log("Ready");
}

void loop() {
    iwdg_feed();

    power::checkSleepTimeout();
    ble::checkTimeout();
    // If there are bytes on the serial buffer; keep the device alive
    if(Output.available()) {
        power::refreshSleepTimeout();
        ble::refreshTimeout();
    }

    lte::loop();
    console::loop();
    neopixel::loop();
    tasks::loop();

    if(CanBus.available()) {
        CanMsg* canMsg;
        if((canMsg = CanBus.recv()) != NULL) {
            CANCommand::CANMessage command;
            command.ID = canMsg->ID;
            command.DLC = canMsg->DLC;

            for (uint8_t i = 0; i < canMsg->DLC; i++) {
                command.Data[i] = canMsg->Data[i];
            }

            #ifdef CAN_DEBUG
                Output.print("Can Message: [");
                Output.print(canMsg->ID, HEX);
                Output.print("](");
                Output.print(canMsg->DLC, HEX);
                Output.print(") ");
                for(uint8_t i = 0; i < canMsg->DLC; i++) {
                    Output.print(canMsg->Data[i], HEX);
                }
                Output.println();
            #endif
            Log.logCanIncoming(canMsg);

            can::handle(&command);

            CanBus.free();
        }
    }
}

void restoreBackupTime() {
    uint16_t backedUp = bkp_read(0);
    uint16_t uptime = millis() / 1000;

    Clock.setTime(backedUp + uptime);
}

void saveBackupTime() {
    time_t currentTime = Clock.getTime();
    bkp_write(0, currentTime);
}

