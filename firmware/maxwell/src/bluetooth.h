#pragma once

#include <Arduino.h>

#define BLUETOOTH_TIMEOUT 90000

namespace ble {
    void enableBluetooth(bool enable);
    bool bluetoothIsEnabled();
    String sendCommand(String);
    void delayTimeout(uint32_t);
    void checkTimeout();
    void refreshTimeout();
};
