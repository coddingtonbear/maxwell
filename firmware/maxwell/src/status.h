#pragma once

#define SPEED_WHEEL_RADIUS_INCHES 80.0
#define SPEED_PULSES_PER_ROTATION 14.0
#define SPEED_INCHES_PER_MILE 63360
#define SPEED_SECONDS_PER_HOUR 3.6e6
#define SPEED_SMOOTHING_SAMPLES 5

namespace status {
    void setGpsPosition(long, long);
    long getLatitude();
    long getLongitude();

    void intSpeedUpdate();
    void refreshSpeed();
    double getSpeed();

    bool sendStatusUpdate();
};
