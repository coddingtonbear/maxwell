#pragma once

#include <Arduino.h>
#include <SC16IS750.h>

namespace util {
    void beep(uint32_t, uint32_t);
    void safeDelay(uint32_t);
    void debug(String);

    void bridgeUART(HardwareSerial*, uint32_t);
    void bridgeUART(SC16IS750*);
    HardwareSerial* uartNumberToInterface(uint32_t);
};
