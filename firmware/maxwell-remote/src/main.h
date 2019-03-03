#pragma once

#include <Arduino.h>
#include <RTClock.h>
#include <SC16IS750.h>

#define UTC_OFFSET -8

#define DISPLAY_REFRESH_INTERVAL 100
#define GPS_REFRESH_INTERVAL 1720
#define TIMESTAMP_REFRESH_INTERVAL 9000

#define LONG_PRESS_TIMEOUT 2000
#define LONG_PRESS_INTERVAL 500

#define BT_DISABLE_ PA11
#define BT_KEY PA8

#define WAKE PB0

#define RIGHT_A PA5
#define RIGHT_B PA4
#define LEFT_B PA6
#define LEFT_A PA7

#define SPI_CS2 PB7
#define SPI_CS3 PB6
#define SPI_CS4 PB12

void setup();
void loop();
void enableCanDebug(bool);
void sleep();

void taskUpdateDisplayCallback();
void taskGpsRefreshCallback();
void taskTimestampRefreshCallback();

extern RTClock Clock;
extern SC16IS750 GPSUart;
extern SC16IS750 AlternateUart;

#define Output Serial
