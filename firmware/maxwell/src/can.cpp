#include "can.h"
#include <HardwareCAN.h>


HardwareCAN canBus(CAN1_BASE);

CAN_TX_MBX sendCanMessage(CanMsg* msg) {
    return canBus.send(msg);
}
