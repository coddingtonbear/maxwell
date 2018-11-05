#include <HardwareCAN.h>

#include "can.h"
#include "main.h"

//#define CAN_DEBUG

LoggedHardwareCAN::LoggedHardwareCAN(CAN_Port* port) : HardwareCAN(port) {
}

CAN_TX_MBX LoggedHardwareCAN::send(CanMsg* message) {
    CAN_TX_MBX mbx = CAN_TX_NO_MBX;
    uint32_t maxWait = millis() + 100;

    while(mbx == CAN_TX_NO_MBX && millis() < maxWait) {
        mbx = HardwareCAN::send(message);
    }

    Log.logCanOutgoing(message);
    return mbx;
}

LoggedHardwareCAN CanBus(CAN1_BASE);
