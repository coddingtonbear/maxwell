#include "main.h"
#include <Arduino.h>
#undef min
#undef max
#include <libmaple/iwdg.h>
#include <SdFat.h>
#include <SPI.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include <SC16IS750.h>
#include <multiserial.h>

#include "multiserial.h"
#include "power.h"
#include "neopixel.h"
#include "serial_commands.h"
#include "power.h"
#include "pin_map.h"
#include "main.h"
#include "lte.h"
#include "status.h"
#include "tasks.h"
#include "bluetooth.h"
#include "util.h"
#include "display.h"

SC16IS750 LTEUart = SC16IS750(
    PIN_SPI_CS_B,
    SC16IS750_CHAN_A,
    14745600UL
);

MultiSerial Output;

HashMap<String, double> Statistics;

SdFat filesystem(&SPI);

Logger Log(&filesystem);

HardwareSerial GPSUart = UART4;

void setup() {
    power::setWake(true);

    afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY);
    iwdg_init(IWDG_PRE_256, 4095);

    Output.addInterface(&BTSerial);
    Output.begin(230400, SERIAL_8E1);
    Output.println("[Maxwell 2.0]");
    Output.flush();

    Wire.begin();
    power::init();

    digitalWrite(PIN_SPI_CS_A, HIGH);
    digitalWrite(PIN_SPI_CS_B, HIGH);
    digitalWrite(DISPLAY_CS, HIGH);
    pinMode(PIN_SPI_CS_A, OUTPUT);
    pinMode(PIN_SPI_CS_B, OUTPUT);
    pinMode(DISPLAY_CS, OUTPUT);

    SPI.setModule(2);
    SPI.begin();

    if(!filesystem.begin(PIN_SPI_CS_A, SD_SCK_MHZ(8))) {
        filesystem.initErrorPrint(&Output);
    } else {
        Log.begin();
    }

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

    digitalWrite(PIN_BT_KEY, LOW);
    pinMode(PIN_BT_KEY, OUTPUT);
    digitalWrite(PIN_BT_DISABLE_, HIGH);
    pinMode(PIN_BT_DISABLE_, OUTPUT);

    delay(100);

    Display.begin();
    Display.setContrast(180);

    // power::init() is earlier
    bluetooth::init();
    tasks::init();
    neopixel::init();
    console::init();
    status::init();
    display::init();

    LTEUart.setSpiBus(&SPI);
    LTEUart.begin(115200, true);
    if(!LTEUart.ping()) {
        Output.println("Error connecting to UART over SPI; no LTE available.");
    } else {
        LTEUart.GPIOSetPinMode(PIN_LTE_DTR, OUTPUT);
        LTEUart.GPIOSetPinMode(PIN_LTE_OE, OUTPUT);
        LTEUart.GPIOSetPinState(PIN_LTE_DTR, LOW);
        LTEUart.GPIOSetPinState(PIN_LTE_OE, HIGH);
        lte::asyncEnable();
    }

    console::prompt();

    Output.println("Ready.");
    Output.flush();
    Log.log("Ready");
}

void loop() {
    loopModules();

    console::loop();
}

void loopModules() {
    iwdg_feed();

    tasks::loop();
}
