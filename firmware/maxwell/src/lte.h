#pragma once

#include <AsyncModem.h>

#define LTE_ENABLED true
#define LTE_DISABLED false

//#define LTE_DEBUG

namespace lte {
    void loop();

    bool enable(bool _enabled=true);

    bool asyncEnable(bool enabled=true);
    void asyncManagerLoop();

    void togglePower();
    void pressPowerKey();
    void unpressPowerKey();

    bool isPoweredOn();
    bool isEnabled();

    time_t getTimestamp();
    AsyncModem::SIM7000::NETWORK_STATUS getNetworkStatus();
    bool collectStatusInformation();

    bool connectTo(char* host, uint16_t port);
    bool disconnectConnection();
    bool getConnectionStatus(char*);
}

extern AsyncModem::SIM7000 LTE;
