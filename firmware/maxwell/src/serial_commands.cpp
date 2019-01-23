#include <Arduino.h>
#undef min
#undef max
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
#include "status.h"
#include "lte.h"
#include "bluetooth.h"
#include "util.h"
#include "tasks.h"

SerialCommand commands(&Output);
CANCommand canCommands;

SdFile openFile;

uint8_t testId = 0;

void console::init() {
    commands.setDefaultHandler(console::unrecognized);

    commands.addCommand("uptime", console::uptime);
    commands.addCommand("ping", console::hello);
    commands.addCommand("beep", console::beep);
    commands.addCommand("led", console::led);
    commands.addCommand("bridge_uart", console::bridgeUART);
    commands.addCommand("stats", console::printStatistics);
    commands.addCommand("task_stats", console::printTaskStatistics);

    commands.addCommand("voltage", console::voltageMeasurement);
    commands.addCommand("charging_status", console::isChargingNow);
    commands.addCommand("current", console::currentUsage);

    commands.addCommand("sleep", console::sleep);
    commands.addCommand("btcmd", console::bleCmd);
    commands.addCommand("reset", console::reset);

    commands.addCommand("flash", console::flash);
    commands.addCommand("enable_autosleep", console::enableAutosleep);
    commands.addCommand("disable_autosleep", console::disableAutosleep);
    commands.addCommand("disable_bluetooth", console::disableBluetooth);
    commands.addCommand("enable_bluetooth", console::enableBluetooth);
    commands.addCommand("delay_bt_timeout", console::setBluetoothTimeoutSeconds);

    commands.addCommand("enable_lte", console::enableLTE);
    commands.addCommand("disable_lte", console::disableLTE);
    commands.addCommand("get_lte_status", console::getLTEStatus);
    commands.addCommand("get_lte_rssi", console::getLTERSSI);
    commands.addCommand("send_text_message", console::sendTextMessage);
    commands.addCommand("lte_command", console::lteCommand);
    commands.addCommand("lte_timestamp", console::showLTETimestamp);

    commands.addCommand("send_can", console::sendCan);
    commands.addCommand("emit_can", console::emitCan);

    commands.addCommand("set_uart_register", console::setUartRegister);
    commands.addCommand("get_uart_register", console::getUartRegister);

    commands.addCommand("log_status", console::logStatus);
    commands.addCommand("list_logs", console::logList);
    commands.addCommand("delete_log", console::logDelete);
    commands.addCommand("delete_all_logs", console::logDeleteAll);
    commands.addCommand("print_log", console::logPrint);
    commands.addCommand("search_log", console::logSearch);
    commands.addCommand("sd_error_state", console::sdErrorState);

    commands.addCommand("set_time", console::setTime);
    commands.addCommand("get_time", console::getTime);

    commands.addCommand("lte_logger_emit", console::sendStatusUpdate);
    commands.addCommand("lte_logger_status", console::getLTELogStatus);
    commands.addCommand("lte_logger_connect", console::connectLTELogger);
    commands.addCommand("lte_logger_disconnect", console::disconnectLTELogger);
}

void can::init() {
    canCommands.addCommand(CAN_CMD_BEEP, can::beep);

    canCommands.addCommand(CAN_CMD_LED_CYCLE, can::setLedCycle);
    canCommands.addCommand(CAN_CMD_LED_COLOR, can::setLedColor);
    canCommands.addCommand(CAN_CMD_LED_BRIGHTNESS, can::setLedBrightness);
    canCommands.addCommand(CAN_CMD_LED_INTERVAL, can::setLedInterval);
    canCommands.addCommand(CAN_CMD_LED_ENABLE, can::ledEnable);
    canCommands.addCommand(CAN_CMD_LED_PRESET, can::ledPreset);
    canCommands.addCommand(CAN_CMD_LTE_ENABLE, can::enableLTE);

    canCommands.addCommand(CAN_CMD_MAIN_MC_RESET, can::reset);
    canCommands.addCommand(CAN_CMD_MAIN_MC_SLEEP, can::sleep);

    canCommands.addCommand(CAN_CMD_MAIN_MC_FLASH, can::flash);
    canCommands.addCommand(CAN_CMD_AUTOSLEEP_ENABLE, can::autosleepEnable);

    canCommands.addCommand(CAN_GPS_POSITION, can::receivePosition);
    canCommands.addCommand(CAN_CURRENT_TIMESTAMP, can::setTime);

    canCommands.addCommand(CAN_CMD_BT_ENABLE, can::enableBluetooth);

    #ifdef DEBUG_CAN_MESSAGES
        canCommands.setDefaultHandler(can::unrecognized);
    #endif
}

uint8_t getHexFromCommand() {
    char* byte = commands.next();
    return strtol(byte, NULL, 16);
}

void console::prompt() {
    commands.prompt();
}

void console::loop() {
    commands.readSerial();
}

void can::handle(CANCommand::CANMessage* command) {
    canCommands.processCANMessage(command);
}

void can::setLedCycle() {
    uint8_t data[8];
    canCommands.getData(data);
    byte cycleType = data[0];

    neopixel::setCycle(cycleType);
}

void can::setLedColor() {
    uint8_t data[8];
    canCommands.getData(data);

    CANLedStatusColor color = *(reinterpret_cast<CANLedStatusColor*>(data));

    neopixel::setColor(color.red, color.green, color.blue);
    neopixel::setSecondaryColor(color.red2, color.green2, color.blue2);
}

void can::setLedBrightness() {
    uint8_t data[8];
    canCommands.getData(data);

    neopixel::setMaxBrightness(data[0]);
}

void can::setLedInterval() {
    uint8_t data[8];
    canCommands.getData(data);

    uint32_t interval = *(reinterpret_cast<uint32_t*>(data));

    neopixel::setInterval(interval);
}

void can::ledEnable() {
    uint8_t data[8];
    canCommands.getData(data);

    uint8_t enabled = *(reinterpret_cast<uint8_t*>(data));

    neopixel::enable(enabled);
}

void can::ledPreset() {
    uint8_t data[8];
    canCommands.getData(data);

    uint8_t preset = *(reinterpret_cast<uint8_t*>(data));

    neopixel::activatePreset(preset);
}

void console::led() {
    char* subcommandBytes = commands.next();
    if(subcommandBytes == NULL) {
        Output.println(
            "Subcommand required: cycle, color, color2, addColorList, addColorTarget, segment, interval, brightness, preset, disable, enable."
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
            neopixel::setCycle(LED_CYCLE_OFF);
        } else if (cycleName == "on") {
            neopixel::setCycle(LED_CYCLE_ON);
        } else if(cycleName == "random") {
            neopixel::setCycle(LED_CYCLE_RANDOM);
        } else if(cycleName == "motion") {
            neopixel::setCycle(LED_CYCLE_MOTION);
        } else if(cycleName == "blink") {
            neopixel::setCycle(LED_CYCLE_BLINK);
        } else if(cycleName == "rotation") {
            neopixel::setCycle(LED_CYCLE_ROTATION);
        } else {
            Output.println("Unkonwn cycle name");
        }
    } else if (subcommand == "color") {
        neopixel::setColor(
            getHexFromCommand(),
            getHexFromCommand(),
            getHexFromCommand()
        );
    } else if (subcommand == "color2") {
        neopixel::setSecondaryColor(
            getHexFromCommand(),
            getHexFromCommand(),
            getHexFromCommand()
        );
    } else if (subcommand == "addColorList") {
        neopixel::addColorList(
            getHexFromCommand(),
            getHexFromCommand(),
            getHexFromCommand()
        );
    } else if (subcommand == "addColorTarget") {
        neopixel::addColorTarget(
            getHexFromCommand(),
            getHexFromCommand(),
            getHexFromCommand()
        );
    } else if (subcommand == "segment") {
        char* segmentBytes = commands.next();

        neopixel::setSegmentSize(atoi(segmentBytes));
    } else if (subcommand == "interval") {
        char* intervalBytes = commands.next();
        if(intervalBytes == NULL) {
            Output.println(
                "Required interval in milliseconds"
            );
            return;
        }

        neopixel::setInterval(atoi(intervalBytes));
    } else if (subcommand == "brightness") {
        char* brightnessBytes = commands.next();
        if(brightnessBytes == NULL) {
            Output.println(
                "Required 8-bit brightness value."
            );
            return;
        }

        neopixel::setMaxBrightness(atoi(brightnessBytes));
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
            neopixel::activatePreset(LED_PRESET_SAFETY);
        } else if(presetName == "rainbow") {
            neopixel::activatePreset(LED_PRESET_RAINBOW);
        } else if(presetName == "midnight") {
            neopixel::activatePreset(LED_PRESET_MIDNIGHT);
        } else {
            Output.println("Unknown preset.");
        }
    } else if (subcommand == "disable") {
        neopixel::enable(false);
    } else if (subcommand == "ensable") {
        neopixel::enable(true);
    }
}

void console::reset() {
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

void can::reset() {
    nvic_sys_reset();
}

void console::beep() {
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

    util::beep(frequency, duration);
}

void can::beep() {
    uint8_t data[8];
    canCommands.getData(data);

    uint32 frequency = *(reinterpret_cast<uint32*>(&data));
    uint32 duration = *(
        reinterpret_cast<uint32*>(&data[4])
    );

    tone(PIN_BUZZER, frequency, duration);
}

void console::isChargingNow() {
    uint8_t chargingStatus = power::getChargingStatus();

    switch (chargingStatus) {
        case CHARGING_STATUS_CHARGING_NOW:
            Output.println("Charging");
            break;
        case CHARGING_STATUS_SHUTDOWN:
            Output.println("Shutdown");
            break;
    }
}

void console::currentUsage() {
    Output.println(power::getCurrentUsage(), 6);
}

void console::voltageMeasurement() {
    String source = String((char*)commands.next());

    if(source == "battery") {
        Output.println(power::getVoltage(VOLTAGE_BATTERY), 6);
    } else if(source == "sense") {
        Output.println(power::getVoltage(VOLTAGE_SENSE), 6);
    } else {
        Output.println("Unknown source: " + source);
    }
}

void console::unrecognized(const char *command) {
    Output.print("Unknown command: ");
    Output.println(command);
}

void can::unrecognized(CANCommand::CANMessage* msg) {
    Output.print("Unknown CAN message: ");
    Output.println(msg->ID, HEX);
    Output.print("\tData: ");
    for(uint8_t i = 0; i < msg->DLC; i++) {
        Output.print(msg->Data[i], HEX);
        Output.print(' ');
    }
    Output.println();
}

void console::uptime() {
    Output.println(millis());
}

void can::flash() {
    ble::sendCommand("flash");
}

void console::flash() {
    if(lte::isEnabled()) {
        lte::enable(false);
        LTE.wait(6000, iwdg_feed);
    }

    CanMsg flashNoticeMsg;
    flashNoticeMsg.IDE = CAN_ID_STD;
    flashNoticeMsg.RTR = CAN_RTR_DATA;
    flashNoticeMsg.ID = CAN_MAIN_MC_FLASH_BEGIN;
    flashNoticeMsg.DLC = 0;
    CanBus.send(&flashNoticeMsg);

    Output.println("Resetting device...");
    Output.flush();

    delay(250);

    // Note that resetting while connected via Bluetooth will
    // cause the device to enter flash mode due to to the BT module's
    // 'connected device' line being connected to the BOOT0 net.
    nvic_sys_reset();
}

void console::hello() {
    char *arg;
    arg = commands.next();

    Output.print("pong");
    if (arg != NULL) {
        Output.print(' ');
        Output.print(String(arg));
    }
    Output.println();
}

void console::bleCmd() {
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

    String result = ble::sendCommand(btcommand);

    Output.print(result);
}

void console::emitCan() {
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
    CanBus.send(&testMsg);
}

void console::sendCan() {
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

    CanBus.send(&testMsg);
}

void console::sleep() {
    power::sleep();
}

void can::sleep() {
    power::sleep();
}

void console::bridgeUART() {
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
        util::bridgeUART(&uart);
        Output.println();
        Output.println("==========");
        Output.println("Bridge teardown completed");
    } else {
        HardwareSerial* uart = util::uartNumberToInterface(uartNumber);

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
        util::bridgeUART(uart, baud);
        Output.println();
        Output.println("==========");
        Output.println("Bridge teardown completed");
    }
}

void can::enableBluetooth() {
    uint8_t data[8];
    canCommands.getData(data);

    uint8_t enabled = *(reinterpret_cast<uint8_t*>(data));

    ble::enableBluetooth(enabled);
}

void can::enableLTE() {
    uint8_t data[8];
    canCommands.getData(data);

    uint8_t enabled = *(reinterpret_cast<uint8_t*>(data));

    lte::enable(enabled);
}

void console::printStatistics() {
    for(uint8_t i = 0; i < Statistics.count(); i++) {
        auto key = Statistics.keyAt(i);
        auto value = Statistics.valueFor(key);
        Output.print(key);
        Output.print(": ");
        Output.println(value, 4);
    }
}

void can::autosleepEnable() {
    uint8_t data[8];
    canCommands.getData(data);

    uint8_t enabled = *(reinterpret_cast<uint8_t*>(data));

    power::enableAutosleep(enabled);
}

void console::enableAutosleep() {
    power::enableAutosleep(true);
}

void console::disableAutosleep() {
    power::enableAutosleep(false);
}

void console::logStatus() {
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

void console::logList() {
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

void console::logDelete() {
    char* filenameBytes = commands.next();

    if(!openFile.open(&filesystem, filenameBytes, O_READ | O_WRITE)) {
        Output.println("Error opening file " + String(filenameBytes));
        return;
    }
    openFile.remove();
    Output.println("Deleted");
}

void console::logDeleteAll() {
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

void console::logPrint() {
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

void console::logSearch() {
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

void console::enableBluetooth() {
    ble::enableBluetooth(true);
}

void console::disableBluetooth() {
    ble::enableBluetooth(false);
}

void console::setBluetoothTimeoutSeconds() {
    char* seconds_str = commands.next();
    uint32_t seconds = 60 * 60;
    if(seconds_str != NULL) {
        seconds = atoi(seconds_str);
    }

    ble::delayTimeout(millis() + (seconds * 1000));
}

void console::sdErrorState() {
    filesystem.initErrorPrint(&Output);
}

void console::setTime() {
    char* timestampBytes = commands.next();
    uint32_t timestamp = atoi(timestampBytes);

    Clock.setTime(timestamp);
}

void console::getTime() {
    time_t time = Clock.getTime();

    Output.print("Current time: ");
    Output.println(String((uint32)time));
}

void console::getUartRegister() {
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

    for(int8_t i = 7; i >=0; i--) {
        if(i == 3) {
            Output.print(' ');
        }
        bitRead(value, i);
        if(value & (1 << i)) {
            Output.print('1');
        } else {
            Output.print('0');
        }
    }
}

void console::setUartRegister() {
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

void console::enableLTE() {
    if(lte::asyncEnable(true)) {
        Output.println("Enabling LTE...");
    } else {
        Output.println("ERROR");
    }
}

void console::disableLTE() {
    if(lte::asyncEnable(false)) {
        Output.println("Disabling LTE...");
    } else {
        Output.println("ERROR");
    }
}

void console::getLTEStatus() {
    if (!lte::isEnabled()) {
        Output.println("LTE is not enabled");
        Output.flush();
        return;
    }

    AsyncModem::SIM7000::NETWORK_STATUS status= LTE.getNetworkStatus();
    switch(status) {
        case AsyncModem::SIM7000::NETWORK_STATUS::NOT_REGISTERED:
            Output.println(F("Not registered"));
            break;
        case AsyncModem::SIM7000::NETWORK_STATUS::REGISTERED_HOME:
            Output.println(F("Registered (home)"));
            break;
        case AsyncModem::SIM7000::NETWORK_STATUS::REGISTRATION_DENIED:
            Output.println(F("Registration Denied"));
            break;
        case AsyncModem::SIM7000::NETWORK_STATUS::UNKNOWN:
            Output.println(F("Unknown"));
            break;
        case AsyncModem::SIM7000::NETWORK_STATUS::REGISTERED_ROAMING:
            Output.println(F("Registered (roaming)"));
            break;
        case AsyncModem::SIM7000::NETWORK_STATUS::SEARCHING:
            Output.println(F("Searching"));
            break;
        case AsyncModem::SIM7000::NETWORK_STATUS::NOT_YET_READY:
            Output.println(F("Network status not yet available; please wait."));
            break;
        case AsyncModem::SIM7000::NETWORK_STATUS::UNEXPECTED_RESULT:
            Output.println(F("Unexpected result from network status."));
            break;
        default:
            Output.println(F("Unexpected result from LTE manager module."));
            break;
    }
}

void console::getLTERSSI() {
    if (!lte::isEnabled()) {
        Output.println("LTE is not enabled");
        return;
    }
    // read the RSSI
    int8_t rssi;
    if(LTE.getRSSI(&rssi)) {
        LTE.wait(1000, iwdg_feed);

        if(rssi == -1) {
            Output.println("RSSI not yet available; please wait.");
        }

        uint8_t r;
        Output.print(F("RSSI = "));
        Output.print(rssi);
        Output.print(": ");
        if (rssi == 0) r = -115;
        if (rssi == 1) r = -111;
        if (rssi == 31) r = -52;
        if ((rssi >= 2) && (rssi <= 30)) {
            r = map(rssi, 2, 30, -110, -54);
        }
        Output.print(r);
        Output.println(F(" dBm"));
    } else {
        Output.println("Error: LTE queue full.");
    }
}

void console::sendTextMessage() {
    if (!lte::isEnabled()) {
        Output.println("LTE is not enabled");
        return;
    }
    char* msisdn = commands.next();
    if(!msisdn) {
        Output.println("Must supply MSISDN");
        return;
    }

    char messageFinal[140] = {'\0'};
    uint8_t length = 0;
    char* message;
    while(message = commands.next()) {
        if (strlen(messageFinal) > 0) {
            messageFinal[length] = ' ';
            length++;
        }
        strcpy(&messageFinal[length], message);
        length += strlen(message);
    }
    if(strlen(messageFinal) < 1) {
        Output.println("Must supply a message.");
        return;
    }

    if(
        LTE.sendSMS(
            msisdn,
            messageFinal,
            [](MatchState ms) {
                Output.println("SMS sent successfully.");
            },
            [](ManagedSerialDevice::Command* cmd) {
                Output.println("Error: SMS send failed.");
            }
        )
    ) {
        Output.println("SMS queued.");
    } else {
        Output.println("Error: LTE queue full.");
    }
}

void console::lteCommand() {
    if (!lte::isEnabled()) {
        Output.println("LTE is not enabled");
        return;
    }
    char* command = commands.next();
    if(!command) {
        Output.println("Must supply command");
        return;
    }

    char reply[4096];

    LTE.wait(5000, iwdg_feed);
    if(LTE.getQueueLength()) {
        Output.println("Error: LTE modem busy; please try again later.");
        return;
    }

    if(
        LTE.execute(
            command,
            "",
            ManagedSerialDevice::Timing::NEXT,
            [](MatchState ms) {
                // We don't know what they're looking for, so let's
                // just wait 5s until we can be sure we've probably
                // received the output.
                uint32_t started = millis();
                while(started + 5000 > millis()) {
                    iwdg_feed();
                    delay(500);
                }
                char buffer[256];
                LTE.getResponse(buffer, 256);
                Output.println(buffer);
            }
        )
    ) {
    } else {
        Output.println("Error: LTE queue full.");
    }
}

void console::showLTETimestamp() {
    if (!lte::isEnabled()) {
        Output.println("LTE is not enabled");
        return;
    }
    time_t timestamp = lte::getTimestamp();

    Output.println(timestamp);
}

void can::receivePosition() {
    uint8_t data[8];
    canCommands.getData(data);

    CANGpsPosition pos = *(reinterpret_cast<CANGpsPosition*>(data));

    status::setGpsPosition(pos.latitude, pos.longitude);
}

void console::sendStatusUpdate() {
    status::sendStatusUpdate();
}

void console::getLTELogStatus() {
    if (!lte::isEnabled()) {
        Output.println("LTE is not enabled");
        return;
    }

    char buffer[20];

    if(lte::getConnectionStatus(buffer)) {
        Output.println(buffer);
    } else {
        Output.println("Error");
    }
}


void console::connectLTELogger() {
    if (!lte::isEnabled()) {
        Output.println("LTE is not enabled");
        return;
    }

    if(status::statusConnectionConnected()) {
        Output.println("Already connected");
        return;
    }

    status::connectStatusConnection(true);
}

void console::disconnectLTELogger() {
    if(!status::statusConnectionConnected()) {
        Output.println("Already disconnected");
        return;
    }

    status::connectStatusConnection(false);
}

void console::printTaskStatistics() {
    tasks::printTaskStatistics();
}

void can::setTime() {
    static uint8_t data[8];
    canCommands.getData(data);

    time_t timestamp = *(reinterpret_cast<time_t*>(data));

    Clock.setTime(timestamp);
}
