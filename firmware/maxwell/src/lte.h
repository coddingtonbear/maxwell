#pragma once

#include <Adafruit_FONA.h>

#define LTE_ENABLED true
#define LTE_DISABLED false

//#define LTE_DEBUG

#ifdef LTE_DEBUG
#define ADAFRUIT_FONA_DEBUG
#endif

bool asyncEnableLte(bool enabled=true);
void asyncLteManager();

void toggleLTEPower();
void pressLTEPowerKey();
void unpressLTEPowerKey();

bool lteIsPoweredOn();
void enableLTE();
bool lteIsEnabled();
void disableLTE();

time_t getLTETimestamp();

extern Adafruit_FONA_LTE LTE;
