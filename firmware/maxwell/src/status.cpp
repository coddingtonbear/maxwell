#include <Arduino.h>
#include <ArduinoJson.h>
#include <RollingAverage.h>

#include "main.h"
#include "power.h"
#include "neopixel.h"
#include "lte.h"
#include "status.h"

long longitude = 0;
long latitude = 0;
uint32 speedCounter = 0;
uint32 speedCounterPrev = 0;
uint32 lastSpeedRefresh = 0;
RollingAverage<double, 5> currentSpeedMph;

void status::setGpsPosition(long _latitude, long _longitude) {
    longitude = _longitude;
    latitude = _latitude;
}

long status::getLatitude() {
    return latitude;
}

long status::getLongitude() {
    return longitude;
}

void status::intSpeedUpdate() {
    speedCounter++;
}

void status::refreshSpeed() {
    uint32 pulseCount = speedCounter - speedCounterPrev;

    // There are 14 poles in the hub, and the outer tire is 80in in
    // circumference; so every pole is 5.714in of travel.
    double mph = (
        pulseCount * (SPEED_WHEEL_RADIUS_INCHES / SPEED_PULSES_PER_ROTATION)
        / (millis() - lastSpeedRefresh)
    ) / SPEED_INCHES_PER_MILE * SPEED_SECONDS_PER_HOUR;
    lastSpeedRefresh = millis();
    currentSpeedMph.addMeasurement(mph);

    if (
        pulseCount > 0 ||
        power::getChargingStatus() == CHARGING_STATUS_CHARGING_NOW
    ) {
        power::refreshSleepTimeout();
    }

    speedCounterPrev = speedCounter;
}

double status::getSpeed() {
    return currentSpeedMph.getValue();
}

bool status::sendStatusUpdate() {
    if (!lteIsEnabled()) {
        Output.println("LTE is not enabled; could not send status update.");
        return false;
    }

    StaticJsonBuffer<2048> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();

    if(latitude && longitude) {
        JsonObject& position = root.createNestedObject("position");
        position["latitude"] = String(latitude);
        position["longitude"] = String(longitude);
    }
    //root["velocity_mph"] = currentSpeedMph.getValue();
    root["timestamp"] = Clock.getTime();
    root["uptime"] = millis();

    uint32 errCode = Log.getErrorCode();
    if(errCode) {
        root["logging"] = false;
    } else {
        root["logging"] = true;
    }

    JsonObject& power = root.createNestedObject("power");
    power["battery_voltage"] = power::getVoltage(VOLTAGE_BATTERY);
    power["current_amps"] = power::getCurrentUsage();

    LedStatus ledStatus;
    neopixel::getStatus(ledStatus);
    JsonObject& leds = root.createNestedObject("leds");
    leds["color_1"] = "#" + String(ledStatus.red, HEX) + String(ledStatus.green, HEX) + String(ledStatus.blue, HEX);
    leds["color_2"] = "#" + String(ledStatus.red2, HEX) + String(ledStatus.green2, HEX) + String(ledStatus.blue2, HEX);
    leds["enabled"] = ledStatus.enabled;
    leds["cycle"] = ledStatus.cycle;
    leds["brightness"] = ledStatus.brightness;
    leds["interval"] = ledStatus.interval;

    char output[2048];
    root.printTo(output);

    uint16_t statusCode;
    uint16_t length;
    if(!LTE.HTTP_POST_start(
        "dweet.io/dweet/for/coddingtonbear-maxwell",
        F("application/json"),
        (uint8_t*)output,
        strlen(output),
        &statusCode,
        &length)
    ) {
        Output.print("Failed to post: ");
        Output.println(statusCode);
        return false;
    }
    while(length > 0) {
        while(LTE.available()) {
            LTE.read();
            length--;

            if(!length) {
                break;
            }
        }
    }
    Output.print("Status update completed: ");
    Output.println(statusCode);
    LTE.HTTP_POST_end();
}
