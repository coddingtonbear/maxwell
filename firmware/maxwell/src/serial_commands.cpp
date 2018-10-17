#include <Arduino.h>
#include <libmaple/iwdg.h>
#include <SerialCommand.h>
#include <CANCommand.h>
#include <SdFat.h>

#include "can.h"
#include "main.h"
#include "serial_commands.h"
#include "can_message_ids.h"
#include "pin_map.h"
#include "neopixel.h"
#include "power.h"
#include "lte.h"

SerialCommand commands(&Output);
CANCommand canCommands;

SdFile openFile;

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
    canCommands.addCommand(CAN_CMD_AUTOSLEEP_ENABLE, canAutosleepEnable);
    commands.addCommand("enable_autosleep", cmdEnableAutosleep);
    commands.addCommand("disable_autosleep", cmdEnableAutosleep);
    commands.addCommand("disable_bluetooth", cmdDisableBluetooth);
    commands.addCommand("enable_bluetooth", cmdEnableBluetooth);
    commands.addCommand("delay_bt_timeout", setBluetoothTimeoutSeconds);

    commands.addCommand("enable_lte", enableLTE);
    commands.addCommand("disable_lte", disableLTE);
    commands.addCommand("get_lte_status", getLTEStatus);
    commands.addCommand("get_lte_rssi", getLTERSSI);
    commands.addCommand("send_text_message", sendTextMessage);

    commands.addCommand("debug_can", debug_can);
    commands.addCommand("send_can", send_can);
    commands.addCommand("emit_can", emit_can);
    canCommands.addCommand(CAN_TEST, emit_can);

    commands.addCommand("set_uart_register", setUartRegister);
    commands.addCommand("get_uart_register", getUartRegister);

    commands.addCommand("log_status", logStatus);
    commands.addCommand("list_logs", logList);
    commands.addCommand("delete_log", logDelete);
    commands.addCommand("delete_all_logs", logDeleteAll);
    commands.addCommand("print_log", logPrint);
    commands.addCommand("search_log", logSearch);
    commands.addCommand("sd_error_state", sdErrorState);

    commands.addCommand("set_time", setTime);
    commands.addCommand("get_time", getTime);

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

    CANLedStatusColor color = *(reinterpret_cast<CANLedStatusColor*>(data));

    ledSetColor(color.red, color.green, color.blue);
    ledSetSecondaryColor(color.red2, color.green2, color.blue2);
}

void canSetLedBrightness() {
    uint8_t data[8];
    canCommands.getData(data);

    ledSetMaxBrightness(data[0]);
}

void canSetLedInterval() {
    uint8_t data[8];
    canCommands.getData(data);

    uint32_t interval = *(reinterpret_cast<uint32_t*>(data));

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

void doSleep() {
    sleep();
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

    if(uartNumber == 10) {
        SC16IS750 uart = LTEUart;

        Output.print("Bridging with UART ");
        Output.println(uartNumber);
        Output.println("==========");
        bridgeUART(&uart);
        Output.println();
        Output.println("==========");
        Output.println("Bridge teardown completed");
    } else {
        HardwareSerial* uart = uartNumberToInterface(uartNumber);

        char* baudString = commands.next();
        if(baudString != NULL) {
            baud = atoi(baudString);
        } else {
            Output.println("Baud rate required.");
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

void cmdEnableAutosleep() {
    enableAutosleep(true);
}

void cmdDisableAutosleep() {
    enableAutosleep(false);
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
    filesystem.vwd()->rewind();
    char filename[50];
    while(openFile.openNext(filesystem.vwd(), O_READ)) {
        iwdg_feed();
        openFile.getName(filename, 50);
        if(!openFile.isHidden() && filename[0] != '.') {
            Output.print(filename);
            Output.print(" (");
            Output.print(openFile.fileSize());
            Output.println(")");
        }
        openFile.close();
    }
}

void logDelete() {
    char* filenameBytes = commands.next();

    if(!openFile.open(&filesystem, filenameBytes, O_READ | O_WRITE)) {
        Output.println("Error opening file " + String(filenameBytes));
        return;
    }
    openFile.remove();
    Output.println("Deleted");
}

void logDeleteAll() {
    filesystem.vwd()->rewind();
    char filename[50];
    char* currentLogFilename = Log.getLogFileName();
    while(openFile.openNext(filesystem.vwd(), O_READ)) {
        iwdg_feed();
        bool isHidden = openFile.isHidden();
        openFile.getName(filename, 50);
        openFile.close();
        if(
            !isHidden &&
            filename[0] != '.' &&
            strcmp(filename, currentLogFilename) != 0
        ) {
            Output.print(filename);
            if(filesystem.remove(filename)) {
                Output.println(" deleted");
            } else {
                Output.println(" could not be deleted");
            }
        }
    }
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
        iwdg_feed();
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
    openFile.close();
    Output.print(match_count);
    Output.println(" matches found.");
}

void cmdEnableBluetooth() {
    enableBluetooth(true);
}

void cmdDisableBluetooth() {
    enableBluetooth(false);
}

void setBluetoothTimeoutSeconds() {
    char* seconds = commands.next();
    if(seconds != NULL) {
        setBluetoothKeepalive(millis() + (atoi(seconds) * 1000));
    }
}

void sdErrorState() {
    filesystem.initErrorPrint(&Output);
}

void setTime() {
    char* timestampBytes = commands.next();
    uint32_t timestamp = atoi(timestampBytes);

    Clock.setTime(timestamp);
}

void getTime() {
    time_t time = Clock.getTime();

    Output.print("Current time: ");
    Output.println(String((uint32)time));
}

void getUartRegister() {
    char* registerId = commands.next();
    if(!registerId) {
        Output.println("Must supply register ID");
        return;
    }

    uint8_t registerIdInt = strtoul(registerId, NULL, 16);
    uint8_t value;

    if(registerIdInt == 0xff) {
        value = LTEUart.gpioState;
    } else {
        value = LTEUart.ReadRegister(registerIdInt);
    }

    Output.print("Register ");
    Output.print(registerIdInt, HEX);
    Output.print(": ");
    Output.println(value, BIN);
}

void setUartRegister() {
    char* registerId = commands.next();
    if(!registerId) {
        Output.println("Must supply register ID");
        return;
    }

    char* value = commands.next();
    if(!value) {
        Output.println("Must supply value");
        return;
    }

    uint8_t registerIdInt = strtoul(registerId, NULL, 16);
    uint8_t valueInt = strtoul(value, NULL, 2);

    Output.print(
        "Register "
    );
    Output.print(registerIdInt, HEX);
    Output.print(" set to ");
    Output.println(valueInt, BIN);
    LTEUart.WriteRegister(registerIdInt, valueInt);
}

void getLTEStatus() {
    uint8_t n = LTE.getNetworkStatus();

    if (n == 0) Output.println(F("Not registered"));
    if (n == 1) Output.println(F("Registered (home)"));
    if (n == 2) Output.println(F("Not registered (searching)"));
    if (n == 3) Output.println(F("Denied"));
    if (n == 4) Output.println(F("Unknown"));
    if (n == 5) Output.println(F("Registered roaming"));
}

void getLTERSSI() {
    // read the RSSI
    uint8_t n = LTE.getRSSI();
    int8_t r;

    Output.print(F("RSSI = ")); Output.print(n); Output.print(": ");
    if (n == 0) r = -115;
    if (n == 1) r = -111;
    if (n == 31) r = -52;
    if ((n >= 2) && (n <= 30)) {
        r = map(n, 2, 30, -110, -54);
    }
    Output.print(r); Output.println(F(" dBm"));
}

void sendTextMessage() {
    char* msisdn = commands.next();
    if(!msisdn) {
        Output.println("Must supply MSISDN");
        return;
    }

    char* message = commands.next();
    if(!message) {
        Output.println("Must supply message");
        return;
    }

    if(LTE.sendSMS(msisdn, message)) {
        Output.println("OK");
    } else {
        Output.println("Failed");
    }
}
