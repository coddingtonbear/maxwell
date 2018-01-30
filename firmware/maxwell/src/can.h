#pragma once

#include "main.h"

MCP2515& getCanbus();
MCP2515::ERROR sendCanMessage(can_frame);
