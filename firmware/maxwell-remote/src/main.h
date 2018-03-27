#pragma once

#include <RTClock.h>

#define DISPLAY_REFRESH_INTERVAL 250

#define BT_ENABLE_ PB11
#define BT_KEY PB10

#define WAKE PA5

#define RIGHT_A PB14
#define RIGHT_B PB15
#define LEFT_B PB13
#define LEFT_A PB12

void setup();
void loop();

void taskUpdateDisplayCallback();
void handleSpeedReceived(uint);
void handleControl();

extern RTClock Clock;

#define Output Serial
