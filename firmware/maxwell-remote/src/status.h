#pragma once

#include <Arduino.h>
#include <MicroNMEA.h>

#include "can_message_ids.h"

#define CHARGING_STATUS_CHARGING_NOW 1
#define CHARGING_STATUS_FULLY_CHARGED 2
#define CHARGING_STATUS_SHUTDOWN 3

void setChargingStatus(uint8_t);
void setStatusParameter(uint32, double);
void setStatusMainMc(CANStatusMainMC);
void updateGpsFix();
bool gpsFixValid();
void gpsPMTK(uint cmd, String data);
void gpsWake();
MicroNMEA* getGpsFix();

double getDoubleStatusParameter(uint32);
CANStatusMainMC getStatusMainMc();
uint8_t getChargingStatus();
