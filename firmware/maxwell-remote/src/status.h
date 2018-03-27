#pragma once

#include <Arduino.h>

#define CHARGING_STATUS_CHARGING_NOW 1
#define CHARGING_STATUS_FULLY_CHARGED 2
#define CHARGING_STATUS_SHUTDOWN 3

void setChargingStatus(uint8_t);
void setStatusParameter(uint32, double);
void setStatusMainMc(uint32);

double getDoubleStatusParameter(uint32);
uint32 getStatusMainMc();
uint8_t getChargingStatus();
