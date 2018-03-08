#pragma once

#include <HardwareCAN.h>

CAN_TX_MBX sendCanMessage(CanMsg* msg);

extern HardwareCAN canBus;
