#pragma once

#include <Adafruit_FONA.h>

void toggleLTEPower();
void pressLTEPowerKey();
void unpressLTEPowerKey();

bool lteIsPoweredOn();
void enableLTE();
bool lteIsEnabled();
void disableLTE();

time_t getLTETimestamp();

extern Adafruit_FONA_LTE LTE;
