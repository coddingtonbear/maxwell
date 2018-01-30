#include <SerialCommand.h>
#include <HardwareCAN.h>

#include "can.h"
#include "can_message_ids.h"

void setupCommands();
void commandPrompt();
void commandLoop();

void unrecognized(const char *command);
void reset();
void flash();
void beep();
