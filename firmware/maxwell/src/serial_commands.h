#pragma once

void setupCommands();
void commandPrompt();
void commandLoop();
void handleCANCommand(CANCommand::CANMessage* command);

void unrecognized(const char *command);
void uptime();
void reset();
void flash();
void doSleep();
void hello();
void bluetooth();
void voltageMeasurement();
void isChargingNow();
void currentUsage();
void doBeep();
void doBridgeUART();
void doCanBeep();
void charge();
void led();
void setLedCycle();
void setLedColor();
void setLedBrightness();
void setLedInterval();
void emit_can();
void getGpsCoordinates();
void flashEsp32();
void enableEsp32();
void disableEsp32();
void coordinates();
