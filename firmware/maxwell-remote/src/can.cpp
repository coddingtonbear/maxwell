#include "can.h"

HardwareCAN canBus(CAN1_BASE);

HardwareCAN& getCanbus() {
    return canBus;
}

CAN_TX_MBX sendCanMessage(CanMsg* msg) {
    return canBus.send(msg);
}
