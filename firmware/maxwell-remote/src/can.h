#pragma once

#include <HardwareCAN.h>

HardwareCAN& getCanbus();
CAN_TX_MBX sendCanMessage(CanMsg* msg);
