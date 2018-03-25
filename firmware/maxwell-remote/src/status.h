#pragma once

#include <Arduino.h>


void setStatusParameter(uint32, double);
void setStatusMainMc(uint32);

double getDoubleStatusParameter(uint32);
uint32 getStatusMainMc();
