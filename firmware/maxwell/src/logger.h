#pragma once

#include <Arduino.h>
#include <HardwareCan.h>


class Logger {
    public:
        Logger();
        void begin();
        void log(String);
        void logCanIncoming(CanMsg*);
        void logCanOutgoing(CanMsg*);

        uint32 getErrorCode();
        uint32 getLogCount();

    private:
        uint32 getNextLogNumber();
        void errorExit();

        uint32 messagesLogged = 0;
        uint32 errorState = 0;
        bool initialized = false;
};
