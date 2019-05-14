#pragma once

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

namespace neopixel {
    void init();
    void loop();

    void enable(bool);

    void getStatus(LedStatus&);

    void activatePreset(uint32 preset);

    void setCycle(uint32 _cycle);
    void setInterval(uint32 _interval);
    void setSegmentSize(uint32 _size);

    uint8_t colorRed(uint32_t);
    uint8_t colorGreen(uint32_t);
    uint8_t colorBlue(uint32_t);

    void addColorList(
        uint8_t, uint8_t, uint8_t
    );
    void addColorTarget(
        uint8_t, uint8_t, uint8_t
    );

    void setColor(uint8_t _red, uint8_t _green, uint8_t blue);
    void setSecondaryColor(uint8_t _red, uint8_t _green, uint8_t blue);
    void setMaxBrightness(uint8_t);
}
