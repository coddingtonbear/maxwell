#pragma once

#include <stdint.h>

class KeepAlive{
    public:
        KeepAlive(uint32_t);
        void refresh();
	bool isEnabled();
        void enable(bool);
        void delayUntil(uint32_t);
        bool isTimedOut();
    private:
        bool enabled = true;
        uint32_t timeoutInterval;
        uint32_t timeout;
};
