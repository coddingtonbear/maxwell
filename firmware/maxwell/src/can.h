#pragma once

#include <HardwareCAN.h>

class LoggedHardwareCAN : public HardwareCAN {
    public:
        LoggedHardwareCAN(CAN_Port*);
        CAN_TX_MBX send(CanMsg* message);
};

extern LoggedHardwareCAN CanBus;
