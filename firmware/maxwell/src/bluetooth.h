#pragma once

#include <Arduino.h>

namespace ble {
    void enableBluetooth(bool enable);
    bool bluetoothIsEnabled();
    String sendCommand(String);
    void delayTimeout(uint32_t);
    void checkTimeout();
    void refreshTimeout();
};
