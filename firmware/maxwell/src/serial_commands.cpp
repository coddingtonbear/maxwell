#include <Arduino.h>
#undef min
#undef max
#include <libmaple/iwdg.h>
#include <SerialCommand.h>
#include <ArduinoSort.h>
#include <SdFat.h>
#include <MCP79412RTC.h>
#include <time.h>

#include "main.h"
#include "serial_commands.h"
#include "pin_map.h"
#include "neopixel.h"
#include "power.h"
#include "status.h"
#include "lte.h"
#include "bluetooth.h"
#include "util.h"
#include "tasks.h"
#include "display.h"
#include "led_cycles.h"

namespace console {
    int8_t currentPreset = -1;
    uint8_t lightingPresets[] = {
        LED_PRESET_SAFETY,
        LED_PRESET_MIDNIGHT,
        LED_PRESET_RAINBOW
    };

    SerialCommand commands(&Output);

    SdFile openFile;

    uint8_t testId = 0;

    uint8_t getHexFromCommand() {
        char* byte = commands.next();
        return strtol(byte, NULL, 16);
    }
}

void console::init() {
    commands.setDefaultHandler(console::unrecognized);
    commands.addCommand("repeat", console::repeat);

    commands.addCommand("uptime", console::uptime);
    commands.addCommand("ping", console::hello);
    commands.addCommand("led", console::led);
    commands.addCommand("bridge_uart", console::bridgeUART);
    commands.addCommand("sleep", console::sleep);
    commands.addCommand("btcmd", console::bleCmd);
    commands.addCommand("reset", console::reset);
    commands.addCommand("flash", console::flash);

    commands.addCommand("autosleep_enable", console::enableAutosleep);
    commands.addCommand("autosleep_disable", console::disableAutosleep);

    commands.addCommand("general_stats", console::printStatistics);

    commands.addCommand("task_stats", console::printTaskStatistics);

    commands.addCommand("gps_status", getGpsStats);
    commands.addCommand("gps_send_command", gpsSendCommand);

    commands.addCommand("odometer_set", setOdometer);
    commands.addCommand("odometer_get", getOdometer);
    commands.addCommand("odometer_trip_get", getTripOdometer);
    commands.addCommand("odometer_trip_reset", resetTripOdometer);

    commands.addCommand("temperature_get", getTemperature);

    commands.addCommand("voltage", console::voltageMeasurement);
    commands.addCommand("charging_status", console::isChargingNow);
    commands.addCommand("current", console::currentUsage);
    commands.addCommand("power_io_state", console::getPowerIOState);
    commands.addCommand("power_io_pin_state", console::getPowerIOPinState);
    commands.addCommand("aux_disable", console::disableAuxPower);
    commands.addCommand("aux_enable", console::enableAuxPower);
    commands.addCommand("dynamo_enable", console::enableDynamoPower);
    commands.addCommand("dynamo_disable", console::disableDynamoPower);

    commands.addCommand("bluetooth_disable", console::disableBluetooth);
    commands.addCommand("bluetooth_enable", console::enableBluetooth);
    commands.addCommand("bluetooth_timeout_delay", console::setBluetoothTimeoutSeconds);

    commands.addCommand("lte_enable", console::enableLTE);
    commands.addCommand("lte_disable", console::disableLTE);
    commands.addCommand("lte_status", console::getLTEStatus);
    commands.addCommand("lte_rssi", console::getLTERSSI);
    commands.addCommand("lte_text_message", console::sendTextMessage);
    commands.addCommand("lte_command", console::lteCommand);
    commands.addCommand("lte_timestamp", console::showLTETimestamp);

    commands.addCommand("lte_uart_register_set", console::setUartRegister);
    commands.addCommand("lte_uart_register_get", console::getUartRegister);

    commands.addCommand("log_status", console::logStatus);
    commands.addCommand("log_list", console::logList);
    commands.addCommand("log_delete", console::logDelete);
    commands.addCommand("log_print", console::logPrint);
    commands.addCommand("log_search", console::logSearch);
    commands.addCommand("log_sd_error_state", console::sdErrorState);

    commands.addCommand("time_set", console::setTime);
    commands.addCommand("time_get", console::getTime);

    commands.addCommand("lte_logger_emit", console::sendStatusUpdate);
    commands.addCommand("lte_logger_status", console::getLTELogStatus);
    commands.addCommand("lte_logger_connect", console::connectLTELogger);
    commands.addCommand("lte_logger_disconnect", console::disconnectLTELogger);

    commands.addCommand("display_backlight_enable", console::enableBacklight);
    commands.addCommand("display_backlight_disable", console::disableBacklight);
    commands.addCommand("display_contrast_set", console::setContrast);

    commands.addCommand("menu_up", console::menuUp);
    commands.addCommand("menu_down", console::menuDown);
    commands.addCommand("menu_in", console::menuIn);
    commands.addCommand("menu_out", console::menuOut);
    commands.addCommand("add_alert", console::addAlert);
}

void console::getPowerIOPinState() {
    Pca9536::pin_t pin;

    char* subcommandBytes = commands.next();
    if(subcommandBytes == NULL) {
        Output.println("Pin number required.");
        return;
    }

    String pinId = String(subcommandBytes);
    if(pinId == "0") {
        pin = IO0;
    } else if(pinId == "1") {
        pin = IO1;
    } else if(pinId == "2") {
        pin = IO2;
    } else if(pinId == "3") {
        pin = IO3;
    } else {
        Output.println("Valid pins are 0-3.");
        return;
    }

    if(power::getPowerIOComResult()) {
        Output.print("Error code: ");
        Output.println(power::getPowerIOComResult());
    } else {
        Output.println(power::getPowerIOState(pin));
    }
}

void console::getPowerIOState() {
    power::printPowerIOState();
}

void console::prompt() {
    commands.prompt();
}

void console::loop() {
    commands.readSerial();
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
    } else if (subcommand == "enable") {
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
    } else if(source == "dynamo") {
        Output.println(power::getVoltage(VOLTAGE_DYNAMO), 6);
    } else if(source == "rectified") {
        Output.println(power::getVoltage(VOLTAGE_RECTIFIED), 6);
    } else {
        Output.println("Unknown source: " + source);
    }
}

void console::unrecognized(const char *command) {
    Output.print("Unknown command: ");
    Output.println(command);
}

void console::uptime() {
    Output.println(millis());
}

void console::flash() {
    Output.println("Please wait...");
    if(lte::isEnabled()) {
        lte::enable(false);
        LTE.wait(6000, iwdg_feed);
    }

    Output.println("Resetting device now; you may disconnect.");
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

    String result = bluetooth::sendCommand(btcommand);

    Output.print(result);
}

void console::sleep() {
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

void console::printStatistics() {
    uint8_t size = Statistics.count();
    String statistics[size];

    for(uint8_t i = 0; i < size; i++) {
        auto key = Statistics.keyAt(i);
        auto value = Statistics.valueFor(key);

        statistics[i] = String(key) + ": \t" + String(value, 4);
    }

    sortArray(statistics, size);

    for(uint8_t i = 0; i < size; i++) {
        Output.println(statistics[i]);
    }
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
    } else if(!Log.isLogging()) {
        Output.println("Status: NOT INITIALIZED");
    } else {
        Output.println("Status: OK");
    }
    Output.println("Message Count: " + String(messageCount));
    Output.println("Filename: " + String(Log.getLogFileName()));
}

void console::logList() {
    filesystem.ls(&Output, LS_R);
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

void console::logPrint() {
    char* filenameBytes = commands.next();
    char* afterByteBytes = commands.next();
    char* lengthBytes = commands.next();

    char filename[255];

    if(strcmp(filenameBytes, "_") == 0) {
        strcpy(filename, Log.getLogFileName().c_str());
    } else {
        strcpy(filename, filenameBytes);
    }

    if(!openFile.open(&filesystem, filename, O_READ)) {
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

    uint16_t maxLineLength = 512;

    char findBuffer[maxLineLength] = {'\0'};
    char currentLine[maxLineLength] =  {'\0'};
    char currentLineLower[maxLineLength] = {'\0'};

    char filename[255];
    if(strcmp(filenameBytes, "_") == 0) {
        strcpy(filename, Log.getLogFileName().c_str());
    } else {
        strcpy(filename, filenameBytes);
    }

    for(uint16_t i = 0; i < maxLineLength; i++) {
        currentLineLower[i] = '\0';
        currentLine[i] = '\0';
    }
    if(!openFile.open(&filesystem, filename, O_READ)) {
        Output.println("Error opening file " + String(filenameBytes));
        return;
    }
    uint16_t bufferIndex = 0;
    for(uint16_t j = 0; j < 100; j++) {
        findBytes = commands.next();
        if(findBytes == NULL) {
            findBuffer[bufferIndex] = '\0';
            break;
        }
        if(strlen(findBuffer) > 0) {
            findBuffer[bufferIndex] = ' ';
            bufferIndex++;
        }
        for(uint8_t i = 0; i < maxLineLength; i++) {
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
    uint16_t currentIndex = 0;
    while(openFile.available()) {
        iwdg_feed();
        currentLine[currentIndex] = (char)openFile.read();
        if (currentLine[currentIndex] == '\n') {
            for(uint16_t i = 0; i < maxLineLength; i++) {
                currentLineLower[i] = tolower(currentLine[i]);
            }
            if(strstr(currentLineLower, findBuffer) != NULL) {
                Output.print(currentLine);
                match_count++;
            }

            for(uint16_t i = 0; i < maxLineLength; i++) {
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
    bluetooth::enableBluetooth(true);
}

void console::disableBluetooth() {
    bluetooth::enableBluetooth(false);
}

void console::setBluetoothTimeoutSeconds() {
    char* seconds_str = commands.next();
    uint32_t seconds = 60 * 60;
    if(seconds_str != NULL) {
        seconds = atoi(seconds_str);
    }

    bluetooth::delayTimeout(millis() + (seconds * 1000));
}

void console::sdErrorState() {
    filesystem.initErrorPrint(&Output);
}

void console::setTime() {
    char* timestampBytes = commands.next();
    uint32_t timestamp = atoi(timestampBytes);

    Clock.set(timestamp);
}

void console::getTime() {
    time_t time = Clock.get();
    Output.print("Current timestamp: ");
    Output.print(String((uint32)time));
    Output.print(" (");

    char timeBuffer[24];
    sprintf(
        timeBuffer,
        "%02d-%02d-%02d %02d:%02d:%02d",
        year(time),
        month(time),
        day(time),
        hour(time),
        minute(time),
        second(time)
    );
    Output.print(timeBuffer);
    Output.println(")");
    if(! Clock.isRunning()) {
        Output.println("Warning: Oscillator is not running!");
    }
    Clock.sramWrite(24, 0x24);
    if(Clock.sramRead(24) != 0x24) {
        Output.print("Error: Could not reliably ");
        Output.print("read/write to RTC SRAM. Is it ");
        Output.println("actually connected?");
    }
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

void console::repeat() {
    uint16_t milliseconds = 1000;
    char* tmpCommandStr = commands.next();
    char commandStr[32];
    if(!tmpCommandStr) {
        Output.println("Must provide command");
        return;
    } else {
        strcpy(commandStr, tmpCommandStr);
    }
    char* millisecondsStr = commands.next();
    if(millisecondsStr) {
        milliseconds = atoi(millisecondsStr);
    }
    unsigned long nextLoop = 0;
    while(! Output.available()) {
        loopModules();
        power::refreshSleepTimeout();
        bluetooth::refreshTimeout();
        if(millis() > nextLoop) {
            Output.print("[Repeated ");
            Output.print(milliseconds);
            Output.print("ms run of ");
            Output.print(commandStr);
            Output.print(" at ");
            Output.print(millis());
            Output.println("]");

            for(uint8_t i = 0; i < strlen(commandStr); i++) {
                //Output.println(i);
                //Output.println(strlen(commandStr));
                commands.readChar(commandStr[i]);
                //Output.println();
            }
            commands.readChar('\n');

            nextLoop = millis() + milliseconds;
        }
    }
    Output.println("[Repeated run ended]");
}


void console::enableBacklight() {
    Display.enableBacklight(true);
}

void console::disableBacklight() {
    Display.enableBacklight(false);
}

void console::enableAuxPower() {
    power::enableAux(true);
}

void console::disableAuxPower() {
    power::enableAux(false);
}

void console::setContrast() {
    char* contrastValue = commands.next();
    if(contrastValue) {
        Display.setContrast(atoi(contrastValue));
        Output.print("Contrast set to ");
        Output.println(atoi(contrastValue));
    } else {
        Output.println("Value required");
    }
}

void console::menuUp() {
    Display.up();
}

void console::menuDown() {
    Display.down();
}

void console::menuIn() {
    Display.in();
}

void console::menuOut() {
    Display.out();
}

void console::toggleLightingPreset() {
    currentPreset++;
    if(currentPreset >= sizeof(lightingPresets) / sizeof(currentPreset)) {
        currentPreset = 0;
    }

    neopixel::activatePreset(currentPreset);
}

void console::getGpsStats() {
    MicroNMEA* fix = status::getGpsFix();

    Output.print("Locked: ");
    Output.println(fix->isValid() ? "Yes" : "No");
    Output.print("Latitude: ");
    Output.println(fix->getLatitude() / 1e6);
    Output.print("Longitude: ");
    Output.println(fix->getLongitude() / 1e6);
    long altitude;
    bool gotAltitude = fix->getAltitude(altitude);
    Output.print("Altitude: ");
    if(!gotAltitude) {
        Output.print("(invalid) ");
    }
    Output.print((float)altitude / 1e3);
    Output.println("m");
    Output.print("Timestamp: ");
    Output.println(status::getGpsTime());
    Output.print("Positioning System: ");
    Output.println(fix->getNavSystem());
    Output.print("Num Satellites: ");
    Output.println(fix->getNumSatellites());
    Output.print("Message Id: ");
    Output.println(fix->getMessageID());
    Output.print("Current sentence: ");
    Output.println(fix->getSentence());
}

void console::gpsSendCommand() {
    char* gpsCommand = commands.next();

    status::gpsPMTK(String(gpsCommand));
}

void console::enableDynamoPower() {
    power::enableDynamoPower(true);
}

void console::disableDynamoPower() {
    power::enableDynamoPower(false);
}

void console::getTemperature() {
    float celsius = status::getTemperature();

    Output.print(celsius, 2);
    Output.println(" C");
    Output.print((1.8 * celsius) + 32, 2);
    Output.println(" F");
}

void console::setOdometer() {
    char* value = commands.next();
    if(value) {
        status::setOdometer(atof(value));
    } else {
        Output.println("Value required");
    }
}

void console::getOdometer() {
    Output.print(status::getOdometer(), 2);
    Output.println(" mi");
}

void console::getTripOdometer() {
    Output.print(status::getTripOdometer(), 2);
    Output.println(" mi");
}

void console::resetTripOdometer() {
    status::resetTripOdometer();
}

void console::addAlert() {
    String message = "";

    char* value = commands.next();
    while(value) {
        message = message + " " + String(value);

        value = commands.next();
    }

    if(message.length() > 0) {
        Display.addAlert(message);
    } else {
        Output.println("Message required");
    }
}
