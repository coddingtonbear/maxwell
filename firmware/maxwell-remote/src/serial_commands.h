#pragma once

#include <Arduino.h>
#include <CANCommand.h>

void setupCommands();
void commandPrompt();
void commandLoop();
void handleCANCommand(CANCommand::CANMessage* command);

void unrecognized(const char *command);
void reset();
void flash();
void beep();
void wake();
void uptime();
void bluetooth();

void receiveSpeed();

String sendBluetoothCommand(String);
