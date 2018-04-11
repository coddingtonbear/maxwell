#include <Arduino.h>
#include <libmaple/iwdg.h>
#include <SerialCommand.h>
#include <CANCommand.h>
#include <SdFs.h>

#include "can.h"
#include "gps.h"
#include "main.h"
#include "serial_commands.h"
#include "can_message_ids.h"
#include "pin_map.h"
#include "neopixel.h"
#include "power.h"

SerialCommand commands(&Output);
CANCommand canCommands;

FsFile root;
FsFile openFile;

uint8_t testId = 0;

void setupCommands() {
    commands.addCommand("uptime", uptime);
    commands.addCommand("ping", hello);
    commands.addCommand("beep", doBeep);
    canCommands.addCommand(CAN_CMD_BEEP, canBeep);
    commands.addCommand("led", led);
    canCommands.addCommand(CAN_CMD_LED_CYCLE, canSetLedCycle);
    canCommands.addCommand(CAN_CMD_LED_COLOR, canSetLedColor);
    canCommands.addCommand(CAN_CMD_LED_BRIGHTNESS, canSetLedBrightness);
    canCommands.addCommand(CAN_CMD_LED_INTERVAL, canSetLedInterval);
    canCommands.addCommand(CAN_CMD_LED_ENABLE, canLedEnable);
    canCommands.addCommand(CAN_CMD_LED_PRESET, canLedPreset);
    canCommands.addCommand(CAN_CMD_LED_COLOR2, canSetLedColor2);
    commands.addCommand("bridge_uart", doBridgeUART);
    commands.addCommand("stats", printStatistics);

    commands.addCommand("voltage", voltageMeasurement);
    commands.addCommand("charge", charge);
    commands.addCommand("charging_status", isChargingNow);
    commands.addCommand("current", currentUsage);

    commands.addCommand("sleep", doSleep);
    commands.addCommand("btcmd", bluetooth);
    commands.addCommand("reset", reset);
    canCommands.addCommand(CAN_CMD_MAIN_MC_RESET, reset);
    canCommands.addCommand(CAN_CMD_MAIN_MC_SLEEP, doSleep);
    canCommands.addCommand(CAN_CMD_CHARGE_ENABLE, canChargeEnable);

    commands.addCommand("flash", flash);
    canCommands.addCommand(CAN_CMD_MAIN_MC_FLASH, flash);
    commands.addCommand("flash_esp", flashEsp32);
    commands.addCommand("enable_esp", enableEsp32);
    commands.addCommand("disable_esp", disableEsp32);
    canCommands.addCommand(CAN_CMD_ESP_ENABLE, canEnableEsp);
    canCommands.addCommand(CAN_CMD_BT_ENABLE, canEnableBluetooth);
    canCommands.addCommand(CAN_CMD_AUTOSLEEP_ENABLE, canAutosleepEnable);

    commands.addCommand("coordinates", coordinates);

    commands.addCommand("debug_can", debug_can);
    commands.addCommand("send_can", send_can);
    commands.addCommand("emit_can", emit_can);
    canCommands.addCommand(CAN_TEST, emit_can);

    commands.addCommand("log_status", logStatus);
    commands.addCommand("list_logs", logList);
    commands.addCommand("delete_log", logDelete);
    commands.addCommand("print_log", logPrint);
    commands.addCommand("search_log", logSearch);

    commands.setDefaultHandler(unrecognized);
}

void commandPrompt() {
    commands.prompt();
}

void commandLoop() {
    commands.readSerial();
}

void handleCANCommand(CANCommand::CANMessage* command) {
    canCommands.processCANMessage(command);
}

void canSetLedCycle() {
    uint8_t data[8];
    canCommands.getData(data);
    byte cycleType = data[0];

    ledSetCycle(cycleType);
}

void canSetLedColor() {
    uint8_t data[8];
    canCommands.getData(data);

    ledSetColor(data[0], data[1], data[2]);
}

void canSetLedBrightness() {
    uint8_t data[8];
    canCommands.getData(data);

    ledSetMaxBrightness(data[0]);
}

void canSetLedInterval() {
    uint8_t data[8];
    canCommands.getData(data);

    uint32 interval = reinterpret_cast<uint32>(data);

    ledSetInterval(interval);
}

void canLedEnable() {
    uint8_t data[8];
    canCommands.getData(data);

    uint8_t enabled = *(reinterpret_cast<uint8_t*>(data));

    ledEnable(enabled);
}

void canLedPreset() {
    uint8_t data[8];
    canCommands.getData(data);

    uint8_t preset = *(reinterpret_cast<uint8_t*>(data));

    ledActivatePreset(preset);
}

void canSetLedColor2() {
    uint8_t data[8];
    canCommands.getData(data);

    ledSetSecondaryColor(data[0], data[1], data[2]);
}

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
    } else if (subcommand == "color2") {
        char* redBytes = commands.next();
        char* greenBytes = commands.next();
        char* blueBytes = commands.next();
        if(redBytes == NULL || greenBytes == NULL || blueBytes == NULL) {
            Output.println(
                "Required three 8-bit decimal colors in RGB order."
            );
            return;
        }
        ledSetSecondaryColor(
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
            ledActivatePreset(LED_PRESET_SAFETY);
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

void canBeep() {
    uint8_t data[8];
    canCommands.getData(data);

    uint32 frequency = *(reinterpret_cast<uint32*>(&data));
    uint32 duration = *(
        reinterpret_cast<uint32*>(&data[4])
    );

    tone(PIN_BUZZER, frequency, duration);
}

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
    uint8_t chargingStatus = getChargingStatus();

    switch (chargingStatus) {
        case CHARGING_STATUS_CHARGING_NOW:
            Output.println("Charging");
            break;
        case CHARGING_STATUS_FULLY_CHARGED:
            Output.println("Fully Charged");
            break;
        case CHARGING_STATUS_SHUTDOWN:
            Output.println("Shutdown");
            break;
    }
}

void currentUsage() {
    Output.println(getCurrentUsage(), 6);
}

void voltageMeasurement() {
    String source = String((char*)commands.next());

    if(source == "battery") {
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
    CanMsg flashNoticeMsg;
    flashNoticeMsg.IDE = CAN_ID_STD;
    flashNoticeMsg.RTR = CAN_RTR_DATA;
    flashNoticeMsg.ID = CAN_MAIN_MC_FLASH_BEGIN;
    flashNoticeMsg.DLC = 0;
    canTx(&flashNoticeMsg);

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
    canTx(&testMsg);
}

void send_can() {
    CanMsg testMsg;
    testMsg.IDE = CAN_ID_STD;
    testMsg.RTR = CAN_RTR_DATA;

    char* id = commands.next();
    if(id == NULL) {
        Output.println("Message ID required");
        return;
    }
    testMsg.ID = strtol(id, NULL, 16);
    testMsg.DLC = 0;

    while(true) {
        char* argument = commands.next();
        if(argument == NULL) {
            break;
        }
        testMsg.Data[testMsg.DLC] = strtol(argument, NULL, 16);
        testMsg.DLC++;
    }

    canTx(&testMsg);
}

void debug_can() {
    bool enabled = 1;

    char* enabledStr = commands.next();
    if(enabledStr != NULL) {
        enabled = atoi(enabledStr);
    }

    enableCanDebug(enabled);
}


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

    HardwareSerial* uart = uartNumberToInterface(uartNumber);

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

void canEnableEsp() {
    uint8_t data[8];
    canCommands.getData(data);

    uint8_t enabled = *(reinterpret_cast<uint8_t*>(data));

    enableEsp(enabled);
}

void canEnableBluetooth() {
    uint8_t data[8];
    canCommands.getData(data);

    uint8_t enabled = *(reinterpret_cast<uint8_t*>(data));

    enableBluetooth(enabled);
}

void printStatistics() {
    for(uint8_t i = 0; i < Statistics.count(); i++) {
        auto key = Statistics.keyAt(i);
        auto value = Statistics.valueFor(key);
        Output.print(key);
        Output.print(": ");
        Output.println(value, 4);
    }
}

void canChargeEnable() {
    uint8_t data[8];
    canCommands.getData(data);

    uint8_t enabled = *(reinterpret_cast<uint8_t*>(data));

    enableBatteryCharging(enabled);
}

void canAutosleepEnable() {
    uint8_t data[8];
    canCommands.getData(data);

    uint8_t enabled = *(reinterpret_cast<uint8_t*>(data));

    enableAutosleep(enabled);
}

void logStatus() {
    uint32 errCode = Log.getErrorCode();
    uint32 messageCount = Log.getLogCount();

    if(errCode) {
        Output.println("Status: ERROR " + String(errCode));
    } else {
        Output.println("Status: OK");
    }
    Output.println("Message Count: " + String(messageCount));
    Output.println("Filename: " + String(Log.getLogFileName()));
}

void logList() {
    if(!root.open("/")) {
        Output.println("Error opening /");
        return;
    }
    char filename[50];
    while(openFile.openNext(&root, O_READ)) {
        openFile.getName(filename, 50);
        if(!openFile.isHidden() && filename[0] != '.') {
            Output.print(filename);
            Output.print(" (");
            Output.print(openFile.fileSize());
            Output.println(")");
        }
        openFile.close();
    }
    root.close();
}

void logDelete() {
    char* filenameBytes = commands.next();

    if(!openFile.open(&filesystem, filenameBytes, O_READ)) {
        Output.println("Error opening file " + String(filenameBytes));
        return;
    }
    openFile.remove();
    Output.println("Deleted");
}

void logPrint() {
    char* filenameBytes = commands.next();
    char* afterByteBytes = commands.next();
    char* lengthBytes = commands.next();

    if(!openFile.open(&filesystem, filenameBytes, O_READ)) {
        Output.println("Error opening file " + String(filenameBytes));
        return;
    }
    int32_t afterByte = 0;
    if(afterByteBytes != NULL) {
        if(atoi(afterByteBytes) < 0) {
            afterByte = openFile.fileSize() + atoi(afterByteBytes);
        } else {
            afterByte = atoi(afterByteBytes);
        }
    }
    int32_t length = openFile.fileSize();
    if(lengthBytes != NULL) {
        length = atoi(lengthBytes);
    }

    int32_t currByte = 0;
    int32_t lengthPrinted = 0;
    while(openFile.available()) {
        iwdg_feed();
        if(currByte >= afterByte) {
            Output.print((char)openFile.read());
            lengthPrinted++;
        } else {
            openFile.read();
        }
        currByte++;

        if(lengthPrinted >= length) {
            break;
        }
    }
    openFile.close();
}

void logSearch() {
    char* filenameBytes = commands.next();
    char* findBytes;
    char findBuffer[100];
    char currentLine[100];
    char currentLineLower[100];
    uint8_t currentIndex = 0;

    for(uint8_t i = 0; i < 100; i++) {
        currentLineLower[i] = '\0';
        currentLine[i] = '\0';
    }
    if(!openFile.open(&filesystem, filenameBytes, O_READ)) {
        Output.println("Error opening file " + String(filenameBytes));
        return;
    }
    uint8_t bufferIndex = 0;
    for(uint8_t j = 0; j < 100; j++) {
        findBytes = commands.next();
        if(findBytes == NULL) {
            findBuffer[bufferIndex] = '\0';
            break;
        }
        if(strlen(findBuffer) > 0) {
            findBuffer[bufferIndex] = ' ';
            bufferIndex++;
        }
        for(uint8_t i = 0; i < 100; i++) {
            findBuffer[bufferIndex] = tolower(findBytes[i]);
            if(findBytes[i] == '\0') {
                break;
            }
            bufferIndex++;
        }
    }

    Output.print("Searching for: '");
    Output.print(findBuffer);
    Output.println("'");

    uint16_t match_count = 0;
    while(openFile.available()) {
        currentLine[currentIndex] = (char)openFile.read();
        if (currentLine[currentIndex] == '\n') {
            for(uint8_t i = 0; i < 100; i++) {
                currentLineLower[i] = tolower(currentLine[i]);
            }
            if(strstr(currentLineLower, findBuffer) != NULL) {
                Output.print(currentLine);
                match_count++;
            }

            for(uint8_t i = 0; i < 100; i++) {
                currentLineLower[i] = '\0';
                currentLine[i] = '\0';
            }
            currentIndex = 0;
        } else {
            currentIndex++;
        }
    }
    Output.print(match_count);
    Output.println(" matches found.");
}
