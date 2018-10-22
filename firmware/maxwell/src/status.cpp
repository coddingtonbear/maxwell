#include <Arduino.h>
#include <ArduinoJson.h>
#include <RollingAverage.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_FONA.h>

#include "main.h"
#include "power.h"
#include "neopixel.h"
#include "lte.h"
#include "status.h"

#include "private.h"

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
    if (!lte::isEnabled()) {
        Output.println("LTE is not enabled; could not send status update.");
        return false;
    }

    if(!LTE.TCPconnect(MQTT_SERVER, MQTT_SERVERPORT)) {
        Output.println("Could not establish TCP connection to MQTT server.");
        return false;
    }
    if(!LTE.MQTTconnect("MQIsdp", MQTT_CLIENT, MQTT_USERNAME, MQTT_KEY)) {
        Output.println("Could not establish MQTT connection to broker.");
        return false;
    }

    uint8_t published = 0;
    if(latitude && longitude) {
        published += LTE.MQTTpublish(
            "/position/latitude",
            String((double)latitude / 1e6).c_str()
        );
        published += LTE.MQTTpublish(
            "/position/longitude",
            String((double)longitude / 1e6).c_str()
        );
    }
    published += LTE.MQTTpublish(
        "/position/velocity_mph",
        String(currentSpeedMph.getValue()).c_str()
    );
    published += LTE.MQTTpublish(
        "/timestamp",
        String((uint32_t)Clock.getTime()).c_str()
    );
    published += LTE.MQTTpublish("/uptime", String(millis()).c_str());

    uint32 errCode = Log.getErrorCode();
    if(errCode) {
        published += LTE.MQTTpublish("/logging", "false");
    } else {
        published += LTE.MQTTpublish("/logging", "true");
    }

    published += LTE.MQTTpublish(
        "/power/battery_voltage",
        String(power::getVoltage(VOLTAGE_BATTERY)).c_str()
    );
    published += LTE.MQTTpublish(
        "/power/current_amps",
        String(power::getCurrentUsage()).c_str()
    );

    LedStatus ledStatus;
    neopixel::getStatus(ledStatus);

    published += LTE.MQTTpublish(
        "/leds/color_1",
        ("#" + String(ledStatus.red, HEX) + String(ledStatus.green, HEX) + String(ledStatus.blue, HEX)).c_str()
    );
    published += LTE.MQTTpublish(
        "/leds/color_2",
        ("#" + String(ledStatus.red2, HEX) + String(ledStatus.green2, HEX) + String(ledStatus.blue2, HEX)).c_str()
    );
    published += LTE.MQTTpublish(
        "/leds/enabled",
        String(ledStatus.enabled).c_str()
    );
    published += LTE.MQTTpublish(
        "/leds/cycle_id",
        String(ledStatus.cycle).c_str()
    );
    published += LTE.MQTTpublish(
        "/leds/brightness",
        String(ledStatus.brightness).c_str()
    );
    published += LTE.MQTTpublish(
        "/leds/interval_ms",
        String(ledStatus.interval).c_str()
    );

    #ifdef STATUS_DEBUG
        Output.print("Published ");
        Output.print(published);
        Output.println(" statistics.");
    #endif

    if(!LTE.TCPclose()) {
        Output.println("Could not close TCP connection to MQTT server.");
        return false;
    }

    return true;
}
