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
    initialized = true;

    logFileName = getNextLogFileName();
    if(logFileName.length() == 0) {
        errorExit();
    }
    if(!logFile.open(filesystem, logFileName.c_str(), O_RDWR | O_CREAT | O_APPEND | O_AT_END)) {
        errorExit();
    }
}

void Logger::end() {
    if(initialized) {
        logFile.close();
    }
}

String Logger::getNextLogFileName() {
    time_t time = Clock.get();

    char year_ch[5];
    char month_ch[3];
    char day_ch[3];
    char hour_ch[3];
    char minute_ch[3];
    char second_ch[3];

    sprintf(year_ch, "%02d", year(time));
    sprintf(month_ch, "%02d", month(time));
    sprintf(day_ch, "%02d", day(time));
    sprintf(hour_ch, "%02d", hour(time));
    sprintf(minute_ch, "%02d", minute(time));
    sprintf(second_ch, "%02d", second(time));

    if(!filesystem->exists(year_ch)) {
        if(! filesystem->mkdir(year_ch)) {
            return "";
        }
    }
    if(!filesystem->chdir(year_ch)) {
        return "";
    }

    if(!filesystem->exists(month_ch)) {
        if(! filesystem->mkdir(month_ch)) {
            return "";
        }
    }
    if(! filesystem->chdir(month_ch)) {
        return "";
    }

    if(!filesystem->exists(day_ch)) {
        if(! filesystem->mkdir(day_ch)) {
            return "";
        }
    }
    if(! filesystem->chdir("/")) {
        return "";
    }

    char fullFilename[32];
    sprintf(
        fullFilename,
        "%s/%s/%s/%s%s%s.log",
        year_ch,
        month_ch,
        day_ch,
        hour_ch,
        minute_ch,
        second_ch
    );

    return String(fullFilename);
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

boolean Logger::isLogging() {
    return initialized && !errorState;
}

void Logger::log(String message) {
    log("general", message);
}

void Logger::log(String logger, String message) {
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

    uint32_t loggerLength = logger.length() + 1;
    char loggerBytes[loggerLength];
    logger.toCharArray(loggerBytes, loggerLength);

    uint32_t messageLength = message.length() + 1;
    char messageBytes[messageLength];
    message.toCharArray(messageBytes, messageLength);

    logFile.write(clockBytes, strlen(clockBytes));
    logFile.write(millisBytes, strlen(millisBytes));
    logFile.write(loggerBytes, strlen(loggerBytes));
    logFile.write('\t');
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
