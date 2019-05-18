#pragma once

#include <Arduino.h>
#include <HardwareCAN.h>
#include <SdFat.h>


class Logger {
    public:
        Logger(SdFat*);
        void begin();
        void end();
        void log(String, String);
        void log(String);
        void logCanIncoming(CanMsg*);
        void logCanOutgoing(CanMsg*);

        String getLogFileName();
        uint32 getErrorCode();
        uint32 getLogCount();
        bool isLogging();

    private:
        String getNextLogFileName();
        void errorExit();

        SdFat* filesystem;
        SdFile logFile;

        String logFileName;
        uint32 messagesLogged = 0;
        int32 errorState = 0;
        bool initialized = false;
};
