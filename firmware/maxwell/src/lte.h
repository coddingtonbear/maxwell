#pragma once

#include <Adafruit_FONA.h>

#define LTE_ENABLED true
#define LTE_DISABLED false

//#define LTE_DEBUG

namespace lte {
    bool enable(bool _enabled=true);

    bool asyncEnable(bool enabled=true);
    void asyncManagerLoop();

    void togglePower();
    void pressPowerKey();
    void unpressPowerKey();

    bool isPoweredOn();
    bool isEnabled();

    time_t getTimestamp();

    bool getLteConnectionStatus(char*);
}

extern Adafruit_FONA_LTE LTE;
