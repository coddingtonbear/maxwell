#pragma once

#include <Arduino.h>
#include <HardwareCan.h>
#include <SdFat.h>


class Logger {
    public:
        Logger(SdFat*);
        void begin();
        void end();
        void log(String);
        void logCanIncoming(CanMsg*);
        void logCanOutgoing(CanMsg*);

        char* getLogFileName();
        uint32 getErrorCode();
        uint32 getLogCount();

    private:
        uint32 getNextLogNumber();
        void errorExit();

        SdFat* filesystem;
        SdFile logFile;

        char logFileName[30 + 4 + 1];
        uint32 messagesLogged = 0;
        uint32 errorState = 0;
        bool initialized = false;
};
