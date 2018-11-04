#include <Arduino.h>
#undef min
#undef max
#include <ArduinoJson.h>
#include <RollingAverage.h>

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

uint32_t lastStatusUpdate = 0;

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

void appendStatusUpdateLine(char* dest, const char* field, const char* value) {
    char statusUpdateLine[128];
    sprintf(statusUpdateLine, "%s=%s\r\n", field, value);
    strcat(dest, statusUpdateLine);
}

char statusUpdate[1024] = {'\0'};

bool status::sendStatusUpdate() {
    if (!lte::isEnabled()) {
        return false;
    }

    if(!status::statusConnectionConnected()) {
        status::connectStatusConnection();
    }

    statusUpdate[0] = '\0';

    if(latitude && longitude) {
        char positionBuffer[32];
        sprintf(
            positionBuffer,
            "position=%.5f|%.5f\r\n",
            (float)latitude / 1e6,
            (float)longitude / 1e6
        );
        appendStatusUpdateLine(statusUpdate, "position", positionBuffer);
    }
    appendStatusUpdateLine(
        statusUpdate,
        "velocity",
        String(currentSpeedMph.getValue()).c_str()
    );
    appendStatusUpdateLine(
        statusUpdate,
        "timestamp",
        String((uint32_t)Clock.getTime()).c_str()
    );
    appendStatusUpdateLine(
        statusUpdate,
        "uptime",
        String(millis()).c_str()
    );
    uint32 errCode = Log.getErrorCode();
    if(errCode) {
        appendStatusUpdateLine(
            statusUpdate,
            "sd_logging",
            String("0").c_str()
        );
    } else {
        appendStatusUpdateLine(
            statusUpdate,
            "sd_logging",
            String("1").c_str()
        );
    }
    appendStatusUpdateLine(
        statusUpdate,
        "power.battery_voltage",
        String(power::getVoltage(VOLTAGE_BATTERY)).c_str()
    );
    appendStatusUpdateLine(
        statusUpdate,
        "power.current_amps",
        String(power::getCurrentUsage()).c_str()
    );

    LedStatus ledStatus;
    neopixel::getStatus(ledStatus);
    appendStatusUpdateLine(
        statusUpdate,
        "led.color.1",
        ("#" + String(ledStatus.red, HEX) + String(ledStatus.green, HEX) + String(ledStatus.blue, HEX)).c_str()
    );
    appendStatusUpdateLine(
        statusUpdate,
        "led.color.2",
        ("#" + String(ledStatus.red2, HEX) + String(ledStatus.green2, HEX) + String(ledStatus.blue2, HEX)).c_str()
    );
    appendStatusUpdateLine(
        statusUpdate,
        "led.enabled",
        String(ledStatus.enabled).c_str()
    );
    appendStatusUpdateLine(
        statusUpdate,
        "led.cycle_id",
        String(ledStatus.cycle).c_str()
    );
    appendStatusUpdateLine(
        statusUpdate,
        "led.brightness",
        String(ledStatus.brightness).c_str()
    );
    appendStatusUpdateLine(
        statusUpdate,
        "led.interval",
        String(ledStatus.interval).c_str()
    );

    char cipsend[32];
    uint16_t statusUpdateLength = strlen(statusUpdate);
    sprintf(cipsend, "AT+CIPSEND", statusUpdateLength);

    LTE.execute(
        cipsend,
        "",
        [statusUpdateLength](MatchState ms) {
            for(uint16_t pos = 0; pos < statusUpdateLength; pos++) {
                LTE.write(statusUpdate[pos]);
            }
            LTE.write(0x1a);
            lastStatusUpdate = millis();
        }
    );
}


bool status::connectStatusConnection(bool enabled) {
    if(!lte::isEnabled()) {
        return false;
    }

    if(enabled) {
        lte::connectTo(STATUS_HOST, STATUS_PORT);
    } else {
        return lte::disconnectConnection();
    }
}

bool status::statusConnectionConnected() {
    if(!lte::isEnabled()) {
        return false;
    }

    char buffer[20];
    lte::getConnectionStatus(buffer);

    if(strcmp(buffer, "CONNECT OK") == 0) {
        return true;
    }

    return false;
}

uint32_t status::getLastStatusUpdateTime() {
    return lastStatusUpdate;
}
