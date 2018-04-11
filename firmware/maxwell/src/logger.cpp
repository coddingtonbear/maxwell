#include <Arduino.h>
#include <SPI.h>
#include <SdFs.h>
#include <HardwareCan.h>

#include "logger.h"


Logger::Logger(SdFs* _filesystem) {
    filesystem = _filesystem;
}

void Logger::begin() {
    sprintf(logFileName, "%05d.log", getNextLogNumber());
    if(!logFile.open(filesystem, logFileName, O_RDWR | O_CREAT)) {
        errorExit();
        return;
    }

    initialized = true;
}

uint32 Logger::getNextLogNumber() {
    for(uint32 i = 1; i < 65534; i++) {
        char possibleLogFileName[30 + 4 + 1];
        sprintf(possibleLogFileName, "%05d.log", i);

        if(!filesystem->exists(possibleLogFileName)) {
            return i;
        }
    }
}

char* Logger::getLogFileName() {
    return logFileName;
}

void Logger::errorExit() {
    errorState = filesystem->sdErrorCode();
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

    uint8_t millisLength = 8 + 2 + 1;
    char millisBytes[millisLength];
    sprintf(millisBytes, "%08d: ", millis());

    uint32_t messageLength = message.length() + 1;
    char messageBytes[messageLength];
    message.toCharArray(messageBytes, messageLength);

    logFile.write(millisBytes, millisLength - 1);
    logFile.write(messageBytes, messageLength - 1);
    logFile.write('\n');
    logFile.sync();

    messagesLogged++;
}

void Logger::logCanIncoming(CanMsg* canMsg) {
    String canLog = "CAN Rx [";
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
    String canLog = "CAN Tx [";
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
