#pragma once

#include <Arduino.h>

#include "multiserial.h"

#define CHIRP_INTERVAL 300000
#define CHIRP_FREQUENCY 2500
#define CHIRP_DURATION 50
#define CHIRP_COUNT 3
#define CHIRP_INTRANOTE_INTERVAL 50

void setup();
void loop();

void handleCounter();

String sendBluetoothCommand(String);
void enableEsp(bool);
void enableBatteryPower(bool);

void beep(uint, uint);

void bridgeUART(HardwareSerial*, uint);
void sleep();

extern MultiSerial Output;
