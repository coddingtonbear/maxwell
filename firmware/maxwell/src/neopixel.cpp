#include "neopixel.h"

WS2812B pixels = WS2812B(NUM_LEDS);

uint32 cycle = LED_CYCLE_OFF;
uint32 colorRed = 255;
uint32 colorGreen = 255;
uint32 colorBlue = 255;
uint32 color = pixels.Color(colorRed, colorGreen, colorBlue);
uint32 interval = 500;
uint8_t maxBrightness = 20;

bool enabled = false;

uint32 offset = 0;
uint8_t phase = 0;
uint8_t phaseCount = 0;
uint8_t segmentSize = 1;
unsigned long lastCycle = 0;

void ledSetup() {
    pixels.begin();
}

void ledSetCycle(uint32 _cycle) {
    cycle = _cycle;

    if(cycle == LED_CYCLE_MOTION) {
        phaseCount = 2;
        interval = 1;
        segmentSize = 100;
    } else if(cycle == LED_CYCLE_TWINKLE) {
        phaseCount = 2;
    } else if(cycle == LED_CYCLE_BLINK) {
        segmentSize = 2;
    } else if(cycle == LED_CYCLE_RAINBOW) {
        segmentSize = 5;
        interval = 25;
    }

    ledEnable(true);
}

void ledSetSegmentSize(uint32 _size) {
    segmentSize = _size;
}

void ledSetInterval(uint32 _interval) {
    interval = _interval;
}

void ledSetColor(uint8_t _red, uint8_t _green, uint8_t _blue) {
    colorRed = _red;
    colorGreen = _green;
    colorBlue = _blue;
    color = pixels.Color(_red, _green, _blue);
}

void ledSetMaxBrightness(uint8_t _brightness) {
    maxBrightness = _brightness;
}

void ledCycle() {
    if(! enabled) {
        return;
    }

    if(millis() < lastCycle + interval) {
        return;
    }

    if(cycle == LED_CYCLE_OFF) {
        uint32 black = pixels.Color(0, 0, 0);
        for(int i = 0; i < NUM_LEDS; i++) {
            pixels.setPixelColor(i, black);
        }
    } else if(cycle == LED_CYCLE_ON) {
        for(int i = 0; i < NUM_LEDS; i++) {
            pixels.setPixelColor(i, color);
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
        int colors[6] = {
            adjustedColor(colorRed, colorGreen, colorBlue),
            adjustedColor(0, 0, 0)
        };
        for(int i = 0; i < NUM_LEDS; i++) {
            int effectiveI = i + offset;
            if (effectiveI > NUM_LEDS) {
                effectiveI -= NUM_LEDS;
            }

            pixels.setPixelColor(i, colors[(effectiveI / segmentSize) % 6]);
        }
    } else if(cycle == LED_CYCLE_BLINK) {
        for(int i = 0; i < NUM_LEDS; i++) {
            uint32 black = pixels.Color(0, 0, 0);
            if(phase == 0) {
                pixels.setPixelColor(i, color);
            } else {
                pixels.setPixelColor(i, black);
            }
        }
    } else if(cycle == LED_CYCLE_TWINKLE) {
        for(int i = 0; i < NUM_LEDS; i++) {
            if(
                (phase == 0 && i % 2 == 0) ||
                (phase == 1 && i % 2 == 1)
            ) {
                pixels.setPixelColor(i, color);
            } else {
                float value = random(50, maxBrightness);
                pixels.setPixelColor(
                    i,
                    pixels.Color(
                        random(0, (int)(((float)colorRed/(float)255)*value)),
                        random(0, (int)(((float)colorGreen/(float)255)*value)),
                        random(0, (int)(((float)colorBlue/(float)255)*value))
                    )
                );
            }
        }
    } else if(cycle == LED_CYCLE_RAINBOW) {
        int colors[6] = {
            adjustedColor(255, 0, 0),
            adjustedColor(255, 168, 0),
            adjustedColor(255, 255, 0),
            adjustedColor(0, 255, 0),
            adjustedColor(0, 0, 255),
            adjustedColor(168, 0, 255)
        };
        for(int i = 0; i < NUM_LEDS; i++) {
            int effectiveI = i + offset;
            if (effectiveI > NUM_LEDS) {
                effectiveI -= NUM_LEDS;
            }

            pixels.setPixelColor(i, colors[(effectiveI / segmentSize) % 6]);
        }
    }

    offset++;
    if(offset >= NUM_LEDS) {
        offset = 0;
    }
    phase++;
    if(phase >= phaseCount) {
        phase = 0;
    }
    pixels.show();
    lastCycle = millis();

    delay(20);
}


uint32 adjustedColor(uint32 r, uint32 g, uint32 b) {
    return pixels.Color(
        ((float)r/(float)255) * (float)maxBrightness,
        ((float)g/(float)255) * (float)maxBrightness,
        ((float)b/(float)255) * (float)maxBrightness
    );
}


void ledEnable(bool enable) {
    enabled = enable;
    digitalWrite(PIN_ENABLE_BATT_POWER, enabled);
}
