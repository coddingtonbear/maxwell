#pragma once

#include <Arduino.h>
#include <MicroNMEA.h>
#include <RTClock.h>

#define SPEED_WHEEL_RADIUS_INCHES 80.0
#define SPEED_PULSES_PER_ROTATION 14.0
#define SPEED_INCHES_PER_MILE 63360
#define SPEED_SECONDS_PER_HOUR 3.6e6
#define SPEED_SMOOTHING_SAMPLES 5
#define GPS_TIME_UPDATE_INTERVAL 300000

#define MQTT_SERVER ""
#define MQTT_SERVERPORT 0
#define MQTT_USERNAME ""
#define MQTT_KEY ""
#define MQTT_CLIENT "maxwell"

#define UTC_OFFSET -8
#define DST true

#define ODOMETER_EEPROM_ADDR 0x0
#define LATITUDE_EEPROM_ADDR 0x8
#define LONGITUDE_EEPROM_ADDR 0x10

#define SPEED_COUNTER_ADDRESS B1010001
#define TEMPERATURE_SENSOR_ADDRESS B1001110

//#define DEBUG_GPS

namespace status {
    struct Color {
        uint8_t red;
        uint8_t green;
        uint8_t blue;

        Color() {};
        Color(uint8_t r, uint8_t g, uint8_t b) {
            red = r;
            green = g;
            blue = b;
        }

        String asHex();
    };
    struct Status {
        int32_t free_memory;
        bool gps_locked;
        float gps_latitude;
        float gps_longitude;
        bool gps_altitude_valid;
        long gps_altitude;
        float velocity;
        float odometer;
        float trip_odometer;
        unsigned int timestamp;
        unsigned int uptime;
        bool sd_logging;
        float voltage_battery;
        float voltage_dynamo;
        float current_amps;
        Color led_color_1;
        Color led_color_2;
        bool led_enabled;
        uint8_t led_cycle_id;
        uint8_t led_brightness;
        uint32_t led_interval;
        float temperature;
    };

    void init();
    void loop();

    static int32_t getFreeMemory();

    bool gpsIsEnabled();
    void gpsEnable(bool enable=true);
    void gpsPMTK(String cmd);
    void gpsPMTK(uint cmd, String data);
    void updateGpsFix();
    bool gpsFixValid();
    MicroNMEA* getGpsFix();
    void savePosition();
    double getSavedLatitude();
    double getSavedLongitude();
    int getEffectiveUTCOffset();

    bool syncClockWithGps();
    time_t getGpsTime();
    time_t getTime();
    bool isLightOutside();

    float getTemperature();

    uint16_t getSpeedCounter();

    void refreshSpeed();
    double getSpeed();
    double getTripOdometer();
    void resetTripOdometer();
    double getOdometer();
    void setOdometer(double);
    void saveOdometer();
    double getSavedOdometer();

    bool connectStatusConnection(bool enabled=true);
    Status getStatus();
    bool sendStatusUpdate();
    bool statusConnectionConnected();
    void logStatusUpdate();
    uint32_t getLastStatusUpdateTime();
};
