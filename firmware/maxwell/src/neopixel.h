#include <Arduino.h>
#include <WS2812B.h>
#include "main.h"
#include "pin_map.h"
#include "led_cycles.h"

#define NUM_LEDS 139

struct LedStatus {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t red2;
    uint8_t green2;
    uint8_t blue2;

    bool enabled;
    uint8_t cycle;
    uint8_t brightness;
    uint32_t interval;
};

void ledSetup();
void ledCycle();

void ledSetCycle(uint32 _cycle);
void ledActivatePreset(uint32 preset);
void ledSetInterval(uint32 _interval);
void ledSetSegmentSize(uint32 _size);
void ledSetColor(uint8_t _red, uint8_t _green, uint8_t blue);
void ledSetSecondaryColor(uint8_t _red, uint8_t _green, uint8_t blue);
void ledSetMaxBrightness(uint8_t);
void ledGetStatus(LedStatus&);

void ledEnable(bool);

uint32 lowestCommonDenominator(uint32, uint32);
uint32 adjustedColor(uint32, uint32, uint32);
