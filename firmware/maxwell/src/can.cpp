#include <HardwareCAN.h>

#include "can.h"
#include "main.h"

void canTx(CanMsg* msg) {
    CanBus.send(msg);
    delay(50);
    Log.logCanOutgoing(msg);
}

HardwareCAN CanBus(CAN1_BASE);
