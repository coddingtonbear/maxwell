#include <Arduino.h>
#include <SPI.h>
#include <SdFat.h>
#include <HardwareCAN.h>
#include <MCP79412RTC.h>
#include <time.h>

#include "logger.h"
#include "main.h"


Logger::Logger(SdFat* _filesystem) {
    filesystem = _filesystem;
}

void Logger::begin() {
    logFileName = getNextLogFileName();
    if(!logFile.open(filesystem, logFileName.c_str(), O_RDWR | O_CREAT)) {
        errorExit();
        return;
    }

    initialized = true;
}

void Logger::end() {
    logFile.close();
}

String Logger::getNextLogFileName() {
    time_t time = Clock.get();

    char ymdDir[16];
    sprintf(
        ymdDir,
        "%02d/%02d/%02d",
        year(time),
        month(time),
        day(time)
    );
    char timeStr[16];
    sprintf(
        timeStr,
        "%02d%02d%02d.log",
        hour(time),
        minute(time),
        second(time)
    );

    if(!filesystem->exists(ymdDir)) {
        filesystem->mkdir(ymdDir, true);
    }

    return String(ymdDir) + "/" + String(timeStr);
}

String Logger::getLogFileName() {
    return logFileName;
}

void Logger::errorExit() {
    errorState = filesystem->cardErrorCode();
    initialized = false;
}

uint32 Logger::getErrorCode() {
    return errorState;
}

uint32 Logger::getLogCount() {
    return messagesLogged;
}

void Logger::log(String message) {
    if(!initialized) {
        return;
    }

    uint8_t clockLength = 10 + 2 + 1;
    char clockBytes[clockLength];
    time_t time = Clock.get();
    sprintf(
        clockBytes,
        "%02d:%02d:%02d\t",
        hour(time),
        minute(time),
        second(time)
    );

    uint8_t millisLength = 8 + 2 + 1;
    char millisBytes[millisLength];
    sprintf(millisBytes, "%08d\t", millis());

    uint32_t messageLength = message.length() + 1;
    char messageBytes[messageLength];
    message.toCharArray(messageBytes, messageLength);

    logFile.write(clockBytes, strlen(clockBytes));
    logFile.write(millisBytes, strlen(millisBytes));
    logFile.write(messageBytes, strlen(messageBytes));
    logFile.write('\n');
    logFile.sync();

    messagesLogged++;
}

void Logger::logCanIncoming(CanMsg* canMsg) {
    String canLog = "CAN Rx: [";
    canLog += String(canMsg->ID, HEX);
    canLog += "](";
    canLog += String(canMsg->DLC, HEX);
    canLog += ") ";
    for(uint8_t i = 0; i < canMsg->DLC; i++) {
        canLog += String(canMsg->Data[i], HEX);
        canLog += " ";
    }

    log(canLog);
}

void Logger::logCanOutgoing(CanMsg* canMsg) {
    String canLog = "CAN Tx: [";
    canLog += String(canMsg->ID, HEX);
    canLog += "](";
    canLog += String(canMsg->DLC, HEX);
    canLog += ") ";
    for(uint8_t i = 0; i < canMsg->DLC; i++) {
        canLog += String(canMsg->Data[i], HEX);
        canLog += " ";
    }

    log(canLog);
}
