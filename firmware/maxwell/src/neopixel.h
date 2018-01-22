#include <Arduino.h>
#include <Adafruit_NeoPixel-ANDnXOR.h>

#define NEOPIXEL PC8

#define NUM_LEDS 225

#define LED_CYCLE_OFF 1
#define LED_CYCLE_RANDOM 2
#define LED_CYCLE_MOTION 3
#define LED_CYCLE_BLINK 4


void ledSetup();
void ledCycle();

void ledSetCycle(uint32 _cycle);
void ledSetInterval(uint32 _interval);
void ledSetColor(uint8_t _red, uint8_t _green, uint8_t blue);
void ledSetMaxBrightness(uint8_t);
