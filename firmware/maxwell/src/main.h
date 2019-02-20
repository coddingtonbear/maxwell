#pragma once

#include <Arduino.h>
#include <HashMap.h>
#include <SdFat.h>
#include <SC16IS750.h>

#include "logger.h"
#include "multiserial.h"

#define CHIRP_INTERVAL 900000
#define CHIRP_INIT_FREQUENCY 1046
#define CHIRP_INIT_DURATION 50
#define CHIRP_FREQUENCY 2500
#define CHIRP_DURATION 50
#define CHIRP_COUNT 3
#define CHIRP_INTRANOTE_INTERVAL 50

#define BLUETOOTH_TIMEOUT 120000
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
