#pragma once
#include <PCA9536.h>

#define VOLTAGE_RECTIFIED 0
#define VOLTAGE_DYNAMO 1
#define VOLTAGE_BATTERY 2

#define SENSE_RESISTOR_VALUE 0.1

#define CHARGING_STATUS_CHARGING_NOW 1
#define CHARGING_STATUS_SHUTDOWN 3

#define ADC_ADDRESS B0101000
#define ADC_SAMPLES 3

#define CURRENT_SENSE_ADDRESS B1001010

#define OVERVOLTAGE_DURATION 10000
#define OVERVOLTAGE_HIGH 17
#define OVERVOLTAGE_LOW 12

#define INACTIVITY_SLEEP_DURATION 300000

namespace power {
    void init();
    void loop();
    double getVoltage(uint source);
    double getCurrentUsage();
    uint16_t getAdcValue(uint8_t pin);
    uint8_t getChargingStatus();

    bool isDynamoEnabled();
    void enableDynamoPower(bool enabled=true);

    bool isOvervoltageCheckingEnabled();
    void enableDynamoOvervoltageChecking(bool enabled=true);
    bool isOvervoltage();

    uint8_t getPowerIOComResult();
    uint8_t getPowerIOState(Pca9536::pin_t pin);
    void printPowerIOState();

    void setWake(bool);
    void enableAux(bool);

    double convertAdcToVoltage(uint32_t value, uint16_t r1, uint16_t r2);

    void updatePowerMeasurements();

    void sleep();
    void checkSleepTimeout();
    void enableAutosleep(bool);
    bool isAutosleepEnabled();
    void refreshSleepTimeout();
};
