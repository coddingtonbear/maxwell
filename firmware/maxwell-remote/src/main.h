#include <Arduino.h>

//#include <Wire.h>
//#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>

#include "serial_commands.h"
#include "can_message_ids.h"
#include "can.h"

#define DISPLAY_ADDRESS 0x3C
#define DISPLAY_ON PB4

#define BT_ENABLE_ PB11
#define BT_KEY PB10

#define WAKE PA5

void setup();
void loop();
