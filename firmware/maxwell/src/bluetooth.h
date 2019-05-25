#pragma once

#include <Arduino.h>

#define BLUETOOTH_TIMEOUT 180000

namespace bluetooth {
    void init();

    void loop();

    void enableBluetooth(bool enable);
    bool bluetoothIsEnabled();
    String sendCommand(String);
    void delayTimeout(uint32_t);
    void checkTimeout();
    void refreshTimeout();
};
