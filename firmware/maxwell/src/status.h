#pragma once

#include <Arduino.h>

#define SPEED_WHEEL_RADIUS_INCHES 80.0
#define SPEED_PULSES_PER_ROTATION 14.0
#define SPEED_INCHES_PER_MILE 63360
#define SPEED_SECONDS_PER_HOUR 3.6e6
#define SPEED_SMOOTHING_SAMPLES 5

#define MQTT_SERVER ""
#define MQTT_SERVERPORT 0
#define MQTT_USERNAME ""
#define MQTT_KEY ""
#define MQTT_CLIENT "maxwell"

#define STATUS_DEBUG

namespace status {
    static int32_t getFreeMemory();

    void setGpsPosition(long, long);
    long getLatitude();
    long getLongitude();

    void intSpeedUpdate();
    void refreshSpeed();
    double getSpeed();

    bool connectStatusConnection(bool enabled=true);
    bool sendStatusUpdate();
    bool statusConnectionConnected();
    uint32_t getLastStatusUpdateTime();
};
