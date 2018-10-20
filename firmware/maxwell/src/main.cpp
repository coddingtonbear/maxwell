#include <CANCommand.h>
#include <STM32Sleep.h>
#include <Arduino.h>
#include <TimerFreeTone.h>
#include <HardwareCAN.h>
#include <libmaple/iwdg.h>
#include <SdFat.h>
#include <SPI.h>
#include <ArduinoJson.h>
#include <SC16IS750.h>

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


uint32 lastKeepalive = 0;
uint32 lastBluetoothKeepalive = 0;

bool autosleepEnabled = true;

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

    // I2C_SCL has a pull-up to 3.3v naturally, so we can
    // use that line being pulled down at initialization to
    // prevent the UART from being activated
    bool skipSerialInit = false;
    pinMode(I2C_SCL, INPUT);
    if(digitalRead(I2C_SCL) == LOW) {
        skipSerialInit = true;
    }

    if(!skipSerialInit) {
        Output.addInterface(&BTSerial);
    }
    Output.begin(230400, SERIAL_8E1);
    Output.println("[Maxwell 2.0]");
    Output.flush();

    if(Clock.getTime() < 100000) {
        restoreBackupTime();
    }

    SPIBus.begin();

    LTEUart.setSpiBus(&SPIBus);
    LTEUart.begin(115200, true);
    if(!LTEUart.ping()) {
        Output.println("Error connecting to UART over SPI; no LTE available.");
    } else {
        LTEUart.GPIOSetPinMode(PIN_LTE_DTR, OUTPUT);
        LTEUart.GPIOSetPinMode(PIN_LTE_OE, OUTPUT);
        LTEUart.GPIOSetPinState(PIN_LTE_DTR, LOW);
        LTEUart.GPIOSetPinState(PIN_LTE_OE, HIGH);
    }

    asyncEnableLte();

    if(!filesystem.begin(PIN_SPI_CS_A, SD_SCK_MHZ(18))) {
        Output.println("Error initializing SD Card");
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

    pinMode(PIN_BUZZER, OUTPUT);
    digitalWrite(PIN_BUZZER, LOW);
    digitalWrite(PIN_BT_KEY, LOW);
    pinMode(PIN_BT_KEY, OUTPUT);
    digitalWrite(PIN_BT_DISABLE_, HIGH);
    pinMode(PIN_BT_DISABLE_, OUTPUT);

    pinMode(PIN_I_POWER_ON, INPUT_PULLUP);
    pinMode(PIN_I_BATT_CHARGING_, INPUT_ANALOG);
    pinMode(PIN_I_BATT_VOLTAGE, INPUT_ANALOG);
    pinMode(PIN_I_CURRENT_SENSE, INPUT_ANALOG);
    pinMode(PIN_ENABLE_BATT_POWER, OUTPUT);
    digitalWrite(PIN_ENABLE_BATT_POWER, LOW);
    pinMode(PIN_ENABLE_BATT_CHARGE_, OUTPUT);
    digitalWrite(PIN_ENABLE_BATT_CHARGE_, LOW);

    pinMode(PIN_I_SPEED, INPUT_PULLDOWN);
    attachInterrupt(PIN_I_SPEED, status::intSpeedUpdate, RISING);

    initADCs();
    enableBatteryCharging(true);

    TimerFreeTone(PIN_BUZZER, CHIRP_INIT_FREQUENCY, CHIRP_INIT_DURATION);

    //GPSSerial.begin(9600);
    //gpsWake();
    delay(100);
    //gpsPMTK(161, ",0");  // Disable the GPS

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

    ledSetup();

    setupCommands();
    commandPrompt();

    Output.println("Ready.");
    Log.log("Ready");
}

String sendBluetoothCommand(String command) {
    String result;

    Output.flush();

    delay(250);
    digitalWrite(PIN_BT_KEY, HIGH);
    delay(250);
    Output.println(command);
    Output.flush();
    delay(250);
    digitalWrite(PIN_BT_KEY, LOW);
    delay(250);

    uint32 started = millis();

    Output.flush();
    while(millis() < started + 1000) {
        while(Output.available() > 0) {
            result += (char)Output.read();
        }
    }
    Output.flush();
    delay(100);

    return result;
}

void bridgeUART(HardwareSerial* bridged, uint32_t baud) {
    bridged->begin(baud);

    while(true) {
        iwdg_feed();
        if (Output.available()) {
            uint8_t value = Output.read();

            if (value == 4) {
                break;
            }
            bridged->write(value);
        }
        if (bridged->available()) {
            Output.write(bridged->read());
        }
    }

    Output.begin();
}

void bridgeUART(SC16IS750* bridged) {
    while(true) {
        iwdg_feed();
        if (Output.available()) {
            uint8_t value = Output.read();

            if (value == 4) {
                break;
            }
            bridged->write(value);
        }
        if (bridged->available()) {
            Output.write(bridged->read());
        }
    }

    Output.begin();
}

HardwareSerial* uartNumberToInterface(uint32_t uartNumber) {
    HardwareSerial* uart;
    if(uartNumber == 1) {
        uart = &BTSerial;
    } else if (uartNumber == 2) {
        uart = &UART2;
    } else if (uartNumber == 3) {
        uart = &UART3;
    } else if (uartNumber == 4) {
        uart = &UART4;
    } else if (uartNumber == 5) {
        uart = &UART5;
    }

    return uart;
}

void beep(uint32_t frequency, uint32_t duration) {
    TimerFreeTone(PIN_BUZZER, frequency, duration);
}

void loop() {
    iwdg_feed();

    // If we're past the keepalive duration; go to sleep
    if((millis() > (lastKeepalive + INACTIVITY_SLEEP_DURATION)) && autosleepEnabled) {
        sleep();
    }
    // If we're past the keepalive for bluetooth, deactivate bluetooth, too.
    if((millis() > (lastBluetoothKeepalive + BLUETOOTH_TIMEOUT)) && autosleepEnabled) {
        ble::enableBluetooth(false);
    }
    // If there are bytes on the serial buffer; keep the device alive
    if(Output.available()) {
        renewKeepalive();
        renewBluetoothKeepalive();
    }
    commandLoop();

    ledCycle();

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

            handleCANCommand(&command);

            CanBus.free();
        }
    }
}

void sleep(bool allowMovementWake) {
    Log.log("Sleep requested");
    if(allowMovementWake) {
        Log.log("Movement wake enabled");
    }

    TimerFreeTone(PIN_BUZZER, CHIRP_INIT_FREQUENCY, CHIRP_INIT_DURATION);

    // Stop LTE module
    disableLTE();
    LTEUart.GPIOSetPinMode(PIN_LTE_OE, INPUT);
    LTEUart.sleep();

    // Stop logging
    Log.end();
    filesystem.card()->spiStop();

    Output.end();

    // Disable canbus
    CanMsg sleepMsg;
    sleepMsg.IDE = CAN_ID_STD;
    sleepMsg.RTR = CAN_RTR_DATA;
    sleepMsg.ID = CAN_MAIN_MC_SLEEP;
    sleepMsg.DLC = 0;
    CanBus.send(&sleepMsg);
    CanBus.end();

    setGPIOModeToAllPins(GPIO_INPUT_FLOATING);
    // Turn of CAN transceiver
    pinMode(PIN_CAN_RS, OUTPUT);
    digitalWrite(PIN_CAN_RS, HIGH);
    // Disable buzzer
    pinMode(PIN_BUZZER, OUTPUT);
    digitalWrite(PIN_BUZZER, LOW);
    //pinMode(PIN_ESP_BOOT_FLASH_, OUTPUT);
    //digitalWrite(PIN_ESP_BOOT_FLASH_, LOW);
    // Disable Bluetooth
    pinMode(PIN_BT_DISABLE_, OUTPUT);
    digitalWrite(PIN_BT_DISABLE_, LOW);
    // Disable neopixel battery drain
    pinMode(PIN_ENABLE_BATT_POWER, OUTPUT);
    digitalWrite(PIN_ENABLE_BATT_POWER, LOW);
    // Enable battery charging
    pinMode(PIN_ENABLE_BATT_CHARGE_, OUTPUT);
    digitalWrite(PIN_ENABLE_BATT_CHARGE_, LOW);
    // Configure wake conditions
    attachInterrupt(PIN_I_POWER_ON, nvic_sys_reset, RISING);
    if (allowMovementWake && MOVEMENT_WAKE_ENABLED) {
        pinMode(PIN_I_SPEED, INPUT_PULLDOWN);
        attachInterrupt(PIN_I_SPEED, nvic_sys_reset, RISING);
    }

    systick_disable();
    adc_disable_all();
    disableAllPeripheralClocks();
    bkp_init();
    bkp_enable_writes();
    while(true) {
        iwdg_feed();
        saveBackupTime();
        sleepAndWakeUp(STOP, &Clock, 14);
    }
}

void renewKeepalive() {
    if(lastKeepalive < millis()) {
        setKeepalive(millis());
    }
}

void setBluetoothKeepalive(uint32_t newValue) {
    lastBluetoothKeepalive = newValue;
}

void setKeepalive(uint32_t newValue) {
    lastKeepalive = newValue;
}

void enableAutosleep(bool enable) {
    Log.log("Autosleep enabled: " + String(enable));
    autosleepEnabled = enable;
}

void renewBluetoothKeepalive() {
    if(lastBluetoothKeepalive < millis()) {
        setBluetoothKeepalive(millis());
    }
}

bool syncTimestampWithLTE() {
    if(!lteIsEnabled()){
        return false;
    }
    time_t lteTimestamp = getLTETimestamp();

    if(lteTimestamp < 1) {
        return false;
    }

    // Now convert to my timezone
    lteTimestamp += (TIMEZONE_OFFSET_MINUTES * 60);

    Clock.setTime(lteTimestamp);
    return true;
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
