#include "neopixel.h"


namespace neopixel {
    WS2812B pixels = WS2812B(NUM_LEDS);

    uint32 cycle = LED_CYCLE_OFF;
    uint32 color = pixels.Color(255, 255, 255);
    uint32 secondaryColor = pixels.Color(255, 255, 255);
    uint32 interval = 100;
    uint8_t maxBrightness = 100;

    bool enabled = false;

    uint32 offset = 0;
    uint8_t phase = 0;
    uint8_t phaseCount = 0;
    uint8_t segmentSize = 1;
    float pctPerCycle = 0.01;
    unsigned long lastCycle = 0;

    unsigned long loopCount = 0;

    uint32_t colorList[16] = {};
    uint8_t colorListCount = 0;

    uint32_t colorTarget[16] = {};
    uint8_t colorTargetCount = 0;
    uint8_t currentColorTarget = 0;
    
    uint8_t startRed = 0;
    uint8_t startGreen = 0;
    uint8_t startBlue = 0;
    uint8_t targetRed = 0;
    uint8_t targetGreen = 0;
    uint8_t targetBlue = 0;
    float targetRedStep = 0;
    float targetGreenStep = 0;
    float targetBlueStep = 0;
    uint8_t targetStepCounter = 0;
}

void neopixel::init() {
    digitalWrite(PIN_ENABLE_NEOPIXEL, LOW);
    pinMode(PIN_ENABLE_NEOPIXEL, OUTPUT);
    pixels.begin();
}

void neopixel::getStatus(LedStatus& ledStatus) {
    ledStatus.red = colorRed(color);
    ledStatus.green = colorGreen(color);
    ledStatus.blue = colorBlue(color);
    ledStatus.red2 = colorRed(secondaryColor);
    ledStatus.green2 = colorGreen(secondaryColor);
    ledStatus.blue2 = colorBlue(secondaryColor);

    ledStatus.cycle = cycle;
    ledStatus.enabled = enabled;
    ledStatus.brightness = maxBrightness;
    ledStatus.interval = interval;
}

void neopixel::activatePreset(uint32 preset) {
    if(preset == LED_PRESET_OFF) {
        enable(false);
        setCycle(LED_CYCLE_OFF);
    } else if(preset == LED_PRESET_SAFETY) {
        setCycle(LED_CYCLE_MOTION);
        setMaxBrightness(32);
        setInterval(1);

        setColor(0x80, 0xff, 0x10);
        setSecondaryColor(255, 255, 255);
    } else if(preset == LED_PRESET_SAFETY_FADE) {
        setCycle(LED_CYCLE_ON);
        setMaxBrightness(32);
        setInterval(1);

        colorTargetCount = 2;
        colorTarget[0] = pixels.Color(
            0xff, 0xff, 0xff
        );
        colorTarget[1] = pixels.Color(
            0x80, 0xff, 0x10
        );
        setColor(0xff, 0xff, 0xff);
        setSecondaryColor(0xff, 0xff, 0xff);
    } else if(preset == LED_PRESET_RAINBOW) {
        setCycle(LED_CYCLE_ROTATION);
        setMaxBrightness(32);
        setSegmentSize(5);
        setInterval(25);

        colorListCount = 6;
        colorList[0] = pixels.Color(255, 0, 0);
        colorList[1] = pixels.Color(255, 168, 0);
        colorList[2] = pixels.Color(255, 255, 0);
        colorList[3] = pixels.Color(0, 255, 0);
        colorList[4] = pixels.Color(0, 0, 255);
        colorList[5] = pixels.Color(168, 0, 255);
    } else if(preset == LED_PRESET_MIDNIGHT) {
        setCycle(LED_CYCLE_ON);
        setMaxBrightness(32);
        setInterval(1);

        colorTargetCount = 4;
        colorTarget[0] = pixels.Color(
            0xff, 0, 0xff
        );
        colorTarget[2] = pixels.Color(
            0, 0xff, 0
        );
        colorTarget[1] = pixels.Color(
            0, 0xff, 0x80
        );
        colorTarget[3] = pixels.Color(
            0xff, 0xff, 0xff
        );

        setColor(
            colorRed(colorTarget[0]),
            colorGreen(colorTarget[0]),
            colorBlue(colorTarget[0])
        );
        setSecondaryColor(255, 255, 255);
    } else if(preset == LED_PRESET_PRIDE) {
        setCycle(LED_CYCLE_ON);
        setMaxBrightness(32);
        setInterval(1);

        colorTargetCount = 6;
        colorTarget[0] = pixels.Color(255, 0, 0);
        colorTarget[1] = pixels.Color(255, 168, 0);
        colorTarget[2] = pixels.Color(255, 255, 0);
        colorTarget[3] = pixels.Color(0, 255, 0);
        colorTarget[4] = pixels.Color(0, 0, 255);
        colorTarget[5] = pixels.Color(168, 0, 255);

        setColor(
            colorRed(colorTarget[0]),
            colorGreen(colorTarget[0]),
            colorBlue(colorTarget[0])
        );
        setSecondaryColor(255, 255, 255);
    } else if(preset == LED_PRESET_WHITE) {
        setCycle(LED_CYCLE_ON);
        setColor(255, 255, 255);
        colorTargetCount = 0;
    }
}

void neopixel::setCycle(uint32 _cycle) {
    cycle = _cycle;
    currentColorTarget = 0;
    colorTargetCount = 0;
    colorListCount = 0;

    if(cycle == LED_CYCLE_MOTION) {
        phaseCount = 2;
        interval = 1;
        segmentSize = 125;
    } else if(cycle == LED_CYCLE_BLINK) {
        segmentSize = 2;
    } else if(cycle == LED_CYCLE_ROTATION) {
        segmentSize = 5;
        interval = 25;
    }

    if(cycle != LED_CYCLE_OFF) {
        enable(true);
    }

    loopCount = 0;
}

void neopixel::setPctPerCycle(float _pctPerCycle) {
    pctPerCycle = _pctPerCycle;
}

void neopixel::setSegmentSize(uint32 _size) {
    segmentSize = _size;
}

void neopixel::setInterval(uint32 _interval) {
    interval = _interval;
}

uint8_t neopixel::colorRed(uint32_t color) {
    return (color >> 16) & 0xff;
}

uint8_t neopixel::colorGreen(uint32_t color) {
    return (color >> 8) & 0xff;
}

uint8_t neopixel::colorBlue(uint32_t color) {
    return color & 0xff;
}

void neopixel::addColorList(
    uint8_t _red, uint8_t _green, uint8_t _blue
) {
    colorList[colorListCount] = pixels.Color(
        _red,
        _green,
        _blue
    );
    colorListCount++;
}

void neopixel::clearColorList() {
    colorListCount = 0;
}

void neopixel::addColorTarget(
    uint8_t _red, uint8_t _green, uint8_t _blue
) {
    colorTarget[colorTargetCount] = pixels.Color(
        _red,
        _green,
        _blue
    );
    colorTargetCount++;
}

void neopixel::clearColorTargets() {
    colorTargetCount = 0;
}

void neopixel::setColor(uint8_t _red, uint8_t _green, uint8_t _blue) {
    color = pixels.Color(_red, _green, _blue);
}

void neopixel::setSecondaryColor(uint8_t _red, uint8_t _green, uint8_t _blue) {
    secondaryColor = pixels.Color(_red, _green, _blue);
}

void neopixel::setMaxBrightness(uint8_t _brightness) {
    pixels.setBrightness(_brightness);
}

void neopixel::loop() {
    if(! neopixel::enabled) {
        return;
    }

    if(millis() < (lastCycle + interval)) {
        return;
    }

    if(cycle == LED_CYCLE_OFF) {
        uint32 black = pixels.Color(0, 0, 0);
        for(int i = 0; i < NUM_LEDS; i++) {
            pixels.setPixelColor(i, black);
        }
    } else if(cycle == LED_CYCLE_STATIC) {
        // Do nothing
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
            color,
            secondaryColor
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
    } else if(cycle == LED_CYCLE_ROTATION) {
        for(int i = 0; i < NUM_LEDS; i++) {
            int effectiveI = i + offset;
            if (effectiveI > NUM_LEDS) {
                effectiveI -= NUM_LEDS;
            }

            pixels.setPixelColor(
                i,
                colorList[
                    (effectiveI / segmentSize) %
                    colorListCount
                ]
            );
        }
    }

    if(colorTargetCount > 0) {
        uint8_t currRed = colorRed(color);
        uint8_t currGreen = colorGreen(color);
        uint8_t currBlue = colorBlue(color);

        if(color == colorTarget[currentColorTarget] || loopCount == 0 || targetStepCounter >= (100 / pctPerCycle)) {
            if(loopCount == 0) {
                currentColorTarget = 0;
            } else {
                currentColorTarget++;
            }
            if(currentColorTarget >= colorTargetCount) {
                currentColorTarget = 0;
            }

            uint32_t target = colorTarget[currentColorTarget];

            startRed = currRed;
            startGreen = currGreen;
            startBlue = currBlue;

            targetRed = colorRed(target);
            targetGreen = colorGreen(target);
            targetBlue = colorBlue(target);

            targetRedStep = abs(int(currRed) - int(targetRed)) * (pctPerCycle / 100);
            targetGreenStep = abs(int(currGreen) - int(targetGreen)) * (pctPerCycle / 100);
            targetBlueStep = abs(int(currBlue) - int(targetBlue)) * (pctPerCycle / 100);

            targetStepCounter = 0;
        }


        if (startRed > targetRed) {
            currRed = startRed - (targetRedStep * targetStepCounter);
        } else if (startRed < targetRed) {
            currRed = startRed + (targetRedStep * targetStepCounter);
        }
        if (startGreen > targetGreen) {
            currGreen = startGreen - (targetGreenStep * targetStepCounter);
        } else if (startGreen < targetGreen) {
            currGreen = startGreen + (targetGreenStep * targetStepCounter);
        }
        if (startBlue > targetBlue) {
            currBlue = startBlue - (targetBlueStep * targetStepCounter);
        } else if (startBlue < targetBlue) {
            currBlue = startBlue + (targetBlueStep * targetStepCounter);
        }
        color = pixels.Color(
            currRed,
            currGreen,
            currBlue
        );

        targetStepCounter++;
    }

    pixels.show();
    lastCycle = millis();

    offset++;
    if(offset >= NUM_LEDS) {
        offset = 0;
    }
    phase++;
    if(phase >= phaseCount) {
        phase = 0;
    }
    loopCount++;
}

bool neopixel::isEnabled() {
    return neopixel::enabled;
}

void neopixel::enable(bool enable) {
    neopixel::enabled = enable;
    digitalWrite(PIN_ENABLE_NEOPIXEL, neopixel::enabled);
}
