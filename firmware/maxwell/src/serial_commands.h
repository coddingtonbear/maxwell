#pragma once

#include <Arduino.h>
#include <SerialCommand.h>
#include <CANCommand.h>
#include <mcp2515.h>

#include "can.h"
#include "main.h"

void setupCommands();
void commandPrompt();
void commandLoop();
void handleCANCommand(CANCommand::CANMessage* command);

void unrecognized(const char *command);
void uptime();
void reset();
void flash();
void hello();
void bluetooth();
void voltageMeasurement();
void isChargingNow();
void currentUsage();
void beep();
void doBeep();
void auxDevicesEnable();
void charge();
void led();
void setLedCycle();
void setLedColor();
void setLedBrightness();
void setLedInterval();
void emit_can();
