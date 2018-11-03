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

bool status::sendStatusUpdateLine(String key, String value) {
    String finalMessage = key + "=" + value;

    LTE.sendCommand(
        (char*)(
            String("AT+CIPSEND=")
            + String(finalMessage.length() + 2)
        ).c_str(),
        25
    );
    LTE.sendCommand(
        (char*)finalMessage.c_str(),
        25
    );
}

bool status::sendStatusUpdate() {
    if (!lte::isEnabled()) {
        Output.println("LTE is not enabled; could not send status update.");
        return false;
    }

    if(!status::statusConnectionConnected()) {
        status::connectStatusConnection();
    }

    if(latitude && longitude) {
        status::sendStatusUpdateLine(
            "position",
            String((double)latitude / 1e6)
            + "|"
            + String((double)longitude / 1e5)
        );
    }
    status::sendStatusUpdateLine(
        "velocity",
        String(currentSpeedMph.getValue())
    );
    status::sendStatusUpdateLine(
        "timestamp",
        String((uint32_t)Clock.getTime())
    );
    status::sendStatusUpdateLine(
        "uptime",
        String(millis())
    );
    uint32 errCode = Log.getErrorCode();
    if(errCode) {
        status::sendStatusUpdateLine(
            "sd_logging",
            String("0")
        );
    } else {
        status::sendStatusUpdateLine(
            "sd_logging",
            String("1")
        );
    }
    status::sendStatusUpdateLine(
        "power.battery_voltage",
        String(power::getVoltage(VOLTAGE_BATTERY))
    );
    status::sendStatusUpdateLine(
        "power.current_amps",
        String(power::getCurrentUsage())
    );

    LedStatus ledStatus;
    neopixel::getStatus(ledStatus);
    status::sendStatusUpdateLine(
        "led.color.1",
        ("#" + String(ledStatus.red, HEX) + String(ledStatus.green, HEX) + String(ledStatus.blue, HEX))
    );
    status::sendStatusUpdateLine(
        "led.color.2",
        ("#" + String(ledStatus.red2, HEX) + String(ledStatus.green2, HEX) + String(ledStatus.blue2, HEX))
    );
    status::sendStatusUpdateLine(
        "led.enabled",
        String(ledStatus.enabled)
    );
    status::sendStatusUpdateLine(
        "led.cycle_id",
        String(ledStatus.cycle)
    );
    status::sendStatusUpdateLine(
        "led.brightness",
        String(ledStatus.brightness)
    );
    status::sendStatusUpdateLine(
        "led.interval",
        String(ledStatus.interval)
    );
}


bool status::connectStatusConnection(bool enabled) {
    if(!lte::isEnabled()) {
        return false;
    }

    if(enabled) {
        LTE.sendCommand("AT+CIPSHUT");
        LTE.sendCommand("AT+CIPMUX=0");
        LTE.sendCommand("AT+CIPRXGET=1");
        LTE.sendCommand(
            (char*)(
                String("AT+CIPSTART=\"TCP\",\"")
                + String(STATUS_HOST)
                + String("\",\"")
                + String(STATUS_PORT)
                + String("\"")
            ).c_str()
        );
    } else {
        LTE.sendCommand("AT+CIPCLOSE");
    }

    return true;
}

bool status::statusConnectionConnected() {
    if(!lte::isEnabled()) {
        return false;
    }

    char buffer[20];
    lte::getLteConnectionStatus(buffer);

    if(strcmp(buffer, "CONNECT OK") == 0) {
        return true;
    }

    return false;
}
