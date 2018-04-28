#pragma once

#include <Arduino.h>
#include <CANCommand.h>

#define BT_TIMEOUT_START 60000
#define BT_TIMEOUT_ACTIVITY 300000

void setupCommands();
void commandPrompt();
void commandLoop();
void handleCANCommand(CANCommand::CANMessage* command);

void unrecognized(const char *command);
void reset();
void flash();
void beep();
void wake();
void cmdSleep();
void uptime();
void bluetooth();
void refreshLocalBluetoothTimeout();
void handleLocalBluetoothTimeout();
bool getBluetoothEnabled();
void enableLocalBluetooth();
void enableLocalBluetoothUntil(uint32_t);
void disableLocalBluetooth();
void enableEsp();
void disableEsp();
void enableLighting();
void disableLighting();
void activateLightingPreset(uint8_t);
void setLightingCycle(uint8_t);
void setLightingBrightness(uint8_t);
void setLedColor(int32, int32, int32, bool primary=true);
void enableBatteryCharging();
void disableBatteryCharging();
void enableBluetooth();
void disableBluetooth();
void lowPowerMode();
void disableLowPowerMode();
void enableAutosleep();
void disableAutosleep();
void debugCan();
void getTime();
void canSetTime();
void canReceiveStatus();

void menuUp();
void menuDown();
void menuIn();
void menuOut();

void menuDebug();

void receiveSpeed();
void receiveCanChargingStatus();
void receiveCanDouble();
void receiveLedStatus();
void receiveLedStatusColor();

String sendBluetoothCommand(String);
