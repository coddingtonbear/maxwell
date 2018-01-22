#include "neopixel.h"

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_LEDS, NEOPIXEL, NEO_GRB + NEO_KHZ800);

uint32 cycle = LED_CYCLE_OFF;
uint32 color = pixels.Color(255, 255, 255);
uint32 interval = 500;
uint8_t maxBrightness = 20;

uint8_t phase = 0;
unsigned long lastCycle = 0;

void ledSetup() {
    pixels.begin();
}

void ledSetCycle(uint32 _cycle) {
    cycle = _cycle;
}

void ledSetInterval(uint32 _interval) {
    interval = _interval;
}

void ledSetColor(uint8_t _red, uint8_t _green, uint8_t _blue) {
    color = pixels.Color(_red, _green, _blue);
}

void ledSetMaxBrightness(uint8_t _brightness) {
    maxBrightness = _brightness;
}

void ledCycle() {
    if(millis() < lastCycle + interval) {
        return;
    }

    if(cycle == LED_CYCLE_OFF) {
        uint32 black = pixels.Color(0, 0, 0);
        for(int i = 0; i < NUM_LEDS; i++) {
            pixels.setPixelColor(i, black);
        }
    } else if(cycle == LED_CYCLE_RANDOM) {
        for(int i = 0; i < NUM_LEDS; i++) {
            pixels.setPixelColor(
                i,
                pixels.Color(
                    random(0, maxBrightness),
                    random(0, maxBrightness),
                    random(0, maxBrightness)
                )
            );
        }
    } else if(cycle == LED_CYCLE_MOTION) {
        for(int i = 0; i < NUM_LEDS; i++) {
            uint32 black = pixels.Color(0, 0, 0);
            if(
                (phase == 0 && i % 2 == 0) ||
                (phase == 1 && i % 2 == 1)
            ) {
                pixels.setPixelColor(i, color);
            } else {
                pixels.setPixelColor(i, black);
            }
        }
        phase = !phase;
    } else if(cycle == LED_CYCLE_BLINK) {
        for(int i = 0; i < NUM_LEDS; i++) {
            uint32 black = pixels.Color(0, 0, 0);
            if(phase == 0) {
                pixels.setPixelColor(i, color);
            } else {
                pixels.setPixelColor(i, black);
            }
        }
        phase = !phase;
    }
    pixels.show();
    lastCycle = millis();
}
