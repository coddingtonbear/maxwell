#include <Arduino.h>
#include <SerialCommand.h>
#include <CANCommand.h>

#include "can.h"
#include "gps.h"
#include "main.h"
#include "serial_commands.h"
#include "can_message_ids.h"
#include "pin_map.h"
#include "neopixel.h"
#include "power.h"

SerialCommand commands(&Output);
//CANCommand canCommands;

uint8_t testId = 0;

void setupCommands() {
    commands.addCommand("uptime", uptime);
    commands.addCommand("ping", hello);
    commands.addCommand("beep", doBeep);
    //canCommands.addCommand(CAN_CMD_BEEP, doBeep);
    commands.addCommand("led", led);
    //canCommands.addCommand(CAN_CMD_LED_CYCLE, setLedCycle);
    //canCommands.addCommand(CAN_CMD_LED_COLOR, setLedColor);
    //canCommands.addCommand(CAN_CMD_LED_BRIGHTNESS, setLedBrightness);
    //canCommands.addCommand(CAN_CMD_LED_INTERVAL, setLedInterval);
    commands.addCommand("bridge_uart", doBridgeUART);

    commands.addCommand("voltage", voltageMeasurement);
    commands.addCommand("charge", charge);
    commands.addCommand("is_charging", isChargingNow);
    commands.addCommand("current", currentUsage);

    commands.addCommand("sleep", doSleep);
    commands.addCommand("btcmd", bluetooth);
    commands.addCommand("reset", reset);
    //canCommands.addCommand(CAN_CMD_MAIN_MC_RESET, reset);

    commands.addCommand("flash", flash);
    //canCommands.addCommand(CAN_CMD_MAIN_MC_FLASH, flash);
    commands.addCommand("flash_esp", flashEsp32);
    commands.addCommand("enable_esp", enableEsp32);
    commands.addCommand("disable_esp", disableEsp32);

    commands.addCommand("coordinates", coordinates);

    //commands.addCommand("emit_can", emit_can);
    //canCommands.addCommand(CAN_TEST, emit_can);

    commands.setDefaultHandler(unrecognized);
}

void commandPrompt() {
    commands.prompt();
}

void commandLoop() {
    commands.readSerial();
}

/*
void handleCANCommand(CANCommand::CANMessage* command) {
    canCommands.processCANMessage(command);
}

void setLedCycle() {
    byte cycleType = canCommands.message->Data[0];

    if(cycleType == CAN_CMD_LED_CYCLE_OFF) {
        ledSetCycle(LED_CYCLE_OFF);
    } else if(cycleType == CAN_CMD_LED_CYCLE_RANDOM) {
        ledSetCycle(LED_CYCLE_RANDOM);
    } else if(cycleType == CAN_CMD_LED_CYCLE_MOTION) {
        ledSetCycle(LED_CYCLE_MOTION);
    } else if(cycleType == CAN_CMD_LED_CYCLE_BLINK) {
        ledSetCycle(LED_CYCLE_BLINK);
    }
}

void setLedColor() {
    byte red = canCommands.message->Data[0];
    byte green = canCommands.message->Data[1];
    byte blue = canCommands.message->Data[2];
    ledSetColor(red, green, blue);
}

void setLedBrightness() {
    byte brightness = canCommands.message->Data[0];

    ledSetMaxBrightness(brightness);
}

void setLedInterval() {
    int32 interval = reinterpret_cast<int>(canCommands.message->Data);

    ledSetInterval(interval);
}
*/

void led() {
    char* subcommandBytes = commands.next();
    if(subcommandBytes == NULL) {
        Output.println(
            "Subcommand required: cycle, color, interval"
        );
        return;
    }

    String subcommand = String(subcommandBytes);

    if(subcommand == "cycle") {
        char* cycleNameBytes = commands.next();
        if(cycleNameBytes == NULL) {
            Output.println(
                "Cycle name required."
            );
            return;
        }
        String cycleName = String(cycleNameBytes);

        if (cycleName == "off") {
            ledSetCycle(LED_CYCLE_OFF);
        } else if (cycleName == "on") {
            ledSetCycle(LED_CYCLE_ON);
        } else if(cycleName == "random") {
            ledSetCycle(LED_CYCLE_RANDOM);
        } else if(cycleName == "motion") {
            ledSetCycle(LED_CYCLE_MOTION);
        } else if(cycleName == "blink") {
            ledSetCycle(LED_CYCLE_BLINK);
        } else if(cycleName == "twinkle") {
            ledSetCycle(LED_CYCLE_TWINKLE);
        } else if(cycleName == "rainbow") {
            ledSetCycle(LED_CYCLE_RAINBOW);
        } else {
            Output.println("Unkonwn cycle name");
        }
    } else if (subcommand == "color") {
        char* redBytes = commands.next();
        char* greenBytes = commands.next();
        char* blueBytes = commands.next();
        if(redBytes == NULL || greenBytes == NULL || blueBytes == NULL) {
            Output.println(
                "Required three 8-bit decimal colors in RGB order."
            );
            return;
        }
        ledSetColor(
            atoi(redBytes),
            atoi(greenBytes),
            atoi(blueBytes)
        );
    } else if (subcommand == "segment") {
        char* segmentBytes = commands.next();

        ledSetSegmentSize(atoi(segmentBytes));
    } else if (subcommand == "interval") {
        char* intervalBytes = commands.next();
        if(intervalBytes == NULL) {
            Output.println(
                "Required interval in milliseconds"
            );
            return;
        }

        ledSetInterval(atoi(intervalBytes));
    } else if (subcommand == "brightness") {
        char* brightnessBytes = commands.next();
        if(brightnessBytes == NULL) {
            Output.println(
                "Required 8-bit brightness value."
            );
            return;
        }

        ledSetMaxBrightness(atoi(brightnessBytes));
    } else if (subcommand == "preset") {
        char* presetNameBytes = commands.next();
        if(presetNameBytes == NULL) {
            Output.println(
                "Preset name required."
            );
            return;
        }
        String presetName = String(presetNameBytes);

        if(presetName == "safety") {
            ledSetCycle(LED_CYCLE_MOTION);
            ledSetColor(255, 100, 0);
        } else {
            Output.println("Unknown preset.");
        }
    } else if (subcommand == "disable") {
        ledEnable(false);
    } else if (subcommand == "ensable") {
        ledEnable(true);
    }
}

void reset() {
    Output.println(
        "Disconnect within 5 seconds to prevent booting into Flash mode..."
    );
    Output.print("5...");
    Output.flush();
    delay(1000);
    Output.print("4...");
    Output.flush();
    delay(1000);
    Output.print("3...");
    Output.flush();
    delay(1000);
    Output.print("2...");
    Output.flush();
    delay(1000);
    Output.println("1...");
    Output.flush();
    delay(1000);
    Output.println("Resetting device...");
    Output.flush();

    nvic_sys_reset();
}

void doBeep() {
    int frequency = 554;
    int duration = 100;
    
    char* frequencyString = commands.next();
    if(frequencyString != NULL) {
        frequency = atoi(frequencyString);
    }
    char* durationString = commands.next();
    if(durationString != NULL) {
        duration = atoi(durationString);
    }

    beep(frequency, duration);
}

/*
void doBeep() {
    uint32 frequency = *(reinterpret_cast<uint32*>(canCommands.message->Data));
    uint32 duration = *(
        reinterpret_cast<uint32*>(&canCommands.message->Data[4])
    );

    tone(PIN_BUZZER, frequency, duration);
}
*/

void charge() {
    int enable = 1;
    char* state = commands.next();
    if(state != NULL) {
        enable = atoi(state);
    }

    enableBatteryCharging(enable);
    if(enable) {
        Output.println("Battery charging enabled.");
    } else {
        Output.println("Battery charging disabled.");
    }
}

void isChargingNow() {
    if(!digitalRead(PIN_I_BATT_CHARGING_)) {
        Output.println("Yes");
    } else {
        Output.println("No");
    }
}

void currentUsage() {
    Output.println(getCurrentUsage(), 6);
}

void voltageMeasurement() {
    String source = String((char*)commands.next());

    if(source == "dynamo") {
        Output.println(getVoltage(VOLTAGE_DYNAMO), 6);
    } else if(source == "battery") {
        Output.println(getVoltage(VOLTAGE_BATTERY), 6);
    } else if(source == "sense") {
        Output.println(getVoltage(VOLTAGE_SENSE), 6);
    } else {
        Output.println("Unknown source: " + source);
    }
}

void unrecognized(const char *command) {
    Output.print("Unknown command: ");
    Output.println(command);
}

void uptime() {
    Output.println(millis());
}

void flash() {
    /*
    CanMsg flashNoticeMsg;
    flashNoticeMsg.IDE = CAN_ID_STD;
    flashNoticeMsg.RTR = CAN_RTR_DATA;
    flashNoticeMsg.ID = CAN_MAIN_MC_FLASH_BEGIN;
    flashNoticeMsg.DLC = 0;
    sendCanMessage(&flashNoticeMsg);
    */

    Output.println("Resetting device...");
    Output.flush();

    delay(250);

    // Note that resetting while connected via Bluetooth will
    // cause the device to enter flash mode due to to the BT module's
    // 'connected device' line being connected to the BOOT0 net.
    nvic_sys_reset();
}

void hello() {
    char *arg;
    arg = commands.next();

    Output.print("pong");
    if (arg != NULL) {
        Output.print(' ');
        Output.print(String(arg));
    }
    Output.println();
}

void bluetooth() {
    String btcommand;

    char *arg;
    bool firstArg = true;
    while (true) {
        arg = commands.next();
        if(arg == NULL) {
            break;
        }

        if (!firstArg) {
            btcommand += " ";
        }
        firstArg = false;
        btcommand += String(arg);
    }

    String result = sendBluetoothCommand(btcommand);

    Output.print(result);
}

/*
void emit_can() {
    byte* canIdBytes = reinterpret_cast<byte*>(&testId);

    CanMsg testMsg;
    testMsg.IDE = CAN_ID_STD;
    testMsg.RTR = CAN_RTR_DATA;
    testMsg.ID = CAN_TEST;
    testMsg.DLC = 0;

    for(uint8 i = 0; i < sizeof(uint8_t); i++) {
        testMsg.Data[i] = canIdBytes[i];
    }

    testId++;
    sendCanMessage(&testMsg);
}*/


void flashEsp32() {
    Output.println("Resetting ESP32...");

    digitalWrite(PIN_ESP_BOOT_FLASH_, LOW);
    digitalWrite(PIN_DISABLE_ESP_, LOW);
    delay(1000);
    digitalWrite(PIN_DISABLE_ESP_, HIGH);

    ESPSerial.begin(115200);
    UART5.begin(115200);

    BTSerial.println("Ready to flash ESP32 via UART5 (115200); press ENTER to finish.");

    while(true) {
        if(BTSerial.read() == '\n') {
            break;
        }
        if(UART5.available()) {
            uint8_t value = UART5.read();
            ESPSerial.write(value);
            //BTSerial.print("-> ");
            //BTSerial.println(value);
        }
        if(ESPSerial.available()) {
            uint8_t value = ESPSerial.read();
            UART5.write(value);
            //BTSerial.print("<- ");
            //BTSerial.println(value);
        }
    }

    Output.begin();

    Output.println("Re-enabling ESP32.");
    enableEsp(true);
    Output.println("Finished.");
}

void enableEsp32() {
    enableEsp(true);
    Output.println("ESP32 Enabled.");
}

void disableEsp32() {
    enableEsp(false);
    Output.println("ESP32 Disabled.");
}

void doSleep() {
    sleep();
}

void coordinates() {
    gps_fix fix = gps.read();

    Output.print(fix.latitude(), 6);
    Output.print(", ");
    Output.print(fix.longitude(), 6);
    Output.print("; Altitude: ");
    Output.print(fix.altitude(), 6);
    Output.println();
}

void doBridgeUART() {
    char* uartNumberString = commands.next();
    uint8_t uartNumber;
    uint baud;

    if(uartNumberString != NULL) {
        uartNumber = atoi(uartNumberString);
    } else {
        Output.println("UART number required.");
        return;
    }
    char* baudString = commands.next();
    if(baudString != NULL) {
        baud = atoi(baudString);
    } else {
        Output.println("Baud rate required.");
        return;
    }

    HardwareSerial* uart;
    if(uartNumber == 3) {
        uart = &GPSSerial;
    } else if (uartNumber == 4) {
        uart = &UART4;
    } else if (uartNumber == 5) {
        uart = &UART5;
    } else {
        Output.println("Invalid UART number");
        return;
    }

    Output.print("Bridging with UART ");
    Output.print(uartNumber);
    Output.print(" at ");
    Output.print(baud);
    Output.println(" bps");
    Output.println("==========");
    bridgeUART(uart, baud);
    Output.println();
    Output.println("==========");
    Output.println("Bridge teardown completed");
}
