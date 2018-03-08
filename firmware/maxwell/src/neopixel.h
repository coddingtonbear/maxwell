#include <Arduino.h>
#include <WS2812B.h>
#include "main.h"
#include "pin_map.h"

#define NUM_LEDS 139

#define LED_CYCLE_ON 0
#define LED_CYCLE_OFF 1
#define LED_CYCLE_RANDOM 2
#define LED_CYCLE_MOTION 3
#define LED_CYCLE_BLINK 4
#define LED_CYCLE_TWINKLE 5
#define LED_CYCLE_RAINBOW 6


void ledSetup();
void ledCycle();

void ledSetCycle(uint32 _cycle);
void ledSetInterval(uint32 _interval);
void ledSetSegmentSize(uint32 _size);
void ledSetColor(uint8_t _red, uint8_t _green, uint8_t blue);
void ledSetSecondaryColor(uint8_t _red, uint8_t _green, uint8_t blue);
void ledSetMaxBrightness(uint8_t);

void ledEnable(bool);

uint32 lowestCommonDenominator(uint32, uint32);
uint32 adjustedColor(uint32, uint32, uint32);
