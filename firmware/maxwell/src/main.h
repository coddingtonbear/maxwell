#pragma once

#include <Arduino.h>
#include <HashMap.h>
#include <SdFat.h>
#include <SC16IS750.h>

#include "logger.h"
#include "multiserial.h"

#define BLUETOOTH_TIMEOUT 90000
#define INACTIVITY_SLEEP_DURATION 300000

//#define DEBUG_VIA_UART

void setup();
void loop();
void loopModules();

extern MultiSerial Output;
extern HashMap<String, double> Statistics;
extern Logger Log;
extern SdFat filesystem;
extern SC16IS750 LTEUart;
extern HardwareSerial GPSUart;
