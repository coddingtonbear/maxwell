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
void canBeep();
void charge();
void led();
void canSetLedCycle();
void canSetLedColor();
void canSetLedColor2();
void canSetLedBrightness();
void canSetLedInterval();
void canLedEnable();
void canLedPreset();
void canChargeEnable();
void setLedInterval();
void send_can();
void emit_can();
void debug_can();
void getGpsCoordinates();
void flashEsp32();
void enableEsp32();
void disableEsp32();
void coordinates();
void doSendCanMesage();
void canEnableEsp();
void canEnableBluetooth();
void canAutosleepEnable();
void printStatistics();
void logStatus();
void logList();
void logPrint();
void logDelete();
