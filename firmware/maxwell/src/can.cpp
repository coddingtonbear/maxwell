#include "can.h"

MCP2515 canbus((const uint8_t)CAN_CS);

MCP2515& getCanbus() {
    return canbus;
}

MCP2515::ERROR sendCanMessage(can_frame frame) {
    return canbus.sendMessage(&frame);
}
