#pragma once

#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "serial_commands.h"
#include "can_message_ids.h"
#include "can.h"

#define DISPLAY_ADDRESS 0x3C
#define DISPLAY_ON_ PB4

#define BT_ENABLE_ PB11
#define BT_KEY PB10

#define WAKE PA5

#define RIGHT_A PB14
#define RIGHT_B PB15
#define LEFT_B PB13
#define LEFT_A PB12

void setup();
void loop();

void handleControl();
