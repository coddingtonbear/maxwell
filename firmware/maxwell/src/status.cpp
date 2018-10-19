#include <Arduino.h>
#include <ArduinoJson.h>

#include "main.h"
#include "power.h"
#include "neopixel.h"
#include "lte.h"

long longitude = 0;
long latitude = 0;

void setGpsPosition(long _latitude, long _longitude) {
    longitude = _longitude;
    latitude = _latitude;
}

long getLatitude() {
    return latitude;
}

long getLongitude() {
    return longitude;
}

bool sendStatusUpdate() {
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
    power["battery_voltage"] = getVoltage(VOLTAGE_BATTERY);
    power["current_amps"] = getCurrentUsage();

    LedStatus ledStatus;
    ledGetStatus(ledStatus);
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
