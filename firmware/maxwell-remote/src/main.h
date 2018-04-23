#pragma once

#include <RTClock.h>

#define DISPLAY_REFRESH_INTERVAL 100

#define BT_ENABLE_ PB11
#define BT_KEY PB10

#define WAKE PA5

#define CAN_RS PA1

#define RIGHT_A PB14
#define RIGHT_B PB15
#define LEFT_B PB13
#define LEFT_A PB12

void setup();
void loop();
void enableCanDebug(bool);
void sleep();

void taskUpdateDisplayCallback();

extern RTClock Clock;

#define Output Serial
