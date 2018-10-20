#include <HardwareCAN.h>

#include "can.h"
#include "main.h"

//#define CAN_DEBUG

LoggedHardwareCAN::LoggedHardwareCAN(CAN_Port* port) : HardwareCAN(port) {
}

CAN_TX_MBX LoggedHardwareCAN::send(CanMsg* message) {
    HardwareCAN::send(message);
    delay(50);
    Log.logCanOutgoing(message);
}

LoggedHardwareCAN CanBus(CAN1_BASE);
