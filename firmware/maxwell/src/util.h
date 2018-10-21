#pragma once

#include <Arduino.h>
#include <SC16IS750.h>

namespace util {
    void beep(uint32_t, uint32_t);

    void bridgeUART(HardwareSerial*, uint32_t);
    void bridgeUART(SC16IS750*);
    HardwareSerial* uartNumberToInterface(uint32_t);

    bool syncTimestampWithLTE();
};
