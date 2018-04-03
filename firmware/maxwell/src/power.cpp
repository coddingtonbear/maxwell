#include <Arduino.h>
#include <RollingAverage.h>
#include "main.h"
#include "pin_map.h"
#include "power.h"

long int lastUpdated = 0;

RollingAverage<double, 5> currentAmps;
RollingAverage<double, 10> senseVoltage;
RollingAverage<double, 10> batteryVoltage;

double lastChargingStatusSample = 0;

void updatePowerMeasurements() {
    double tempVoltage;
    double tempBattVoltage;
    double tempSenseVoltage;
    double tempAmps;

    tempVoltage = getInstantaneousVoltage(VOLTAGE_BATTERY);
    batteryVoltage.addMeasurement(tempVoltage);
    tempBattVoltage = tempVoltage;

    tempVoltage = getInstantaneousVoltage(VOLTAGE_SENSE);
    senseVoltage.addMeasurement(tempVoltage);
    tempSenseVoltage = tempVoltage;

    tempAmps = (
        tempBattVoltage - tempSenseVoltage
    )/SENSE_RESISTOR_VALUE;
    currentAmps.addMeasurement(tempAmps);

    Statistics.put("Battery Voltage", batteryVoltage.getValue());
    if(Statistics.valueFor("Battery Voltage (Max)") < batteryVoltage.getValue()) {
        Statistics.put("Battery Voltage (Max)", batteryVoltage.getValue());
    }
    Statistics.put("Sense Voltage", senseVoltage.getValue());
    if(Statistics.valueFor("Sense Voltage (Max)") < senseVoltage.getValue()) {
        Statistics.put("Sense Voltage (Max)", senseVoltage.getValue());
    }
    Statistics.put("Current (Amps)", currentAmps.getValue());
    if(Statistics.valueFor("Current (Amps) (Max)") < currentAmps.getValue()) {
        Statistics.put("Current (Amps) (Max)", currentAmps.getValue());
    }

    uint8_t status = getChargingStatus();
    String minutesName = "Charging Status " + String(status) + " (minutes)";
    Statistics.put("Charging Status (now)", status);
    double value = Statistics.valueFor(minutesName) + (
        (millis() - lastChargingStatusSample) / 60000
    );
    Statistics.put(minutesName, value);

    lastChargingStatusSample = millis();
}

int getRawVoltageAdcValue(uint source) {
    int result = -1;

    switch(source) {
        case VOLTAGE_BATTERY:
            result = analogRead(PIN_I_BATT_VOLTAGE);
            break;
        case VOLTAGE_SENSE:
            result = analogRead(PIN_I_CURRENT_SENSE);
            break;
    }

    return result;
}

double getVoltage(uint source) {
    double result = 0;

    switch(source) {
        case VOLTAGE_BATTERY:
            result = batteryVoltage.getValue();
            break;
        case VOLTAGE_SENSE:
            result = senseVoltage.getValue();
            break;
    }

    return result;
}

double getInstantaneousVoltage(uint source) {
    double adcValue = getRawVoltageAdcValue(source);
    double result = -1;

    switch(source) {
        case VOLTAGE_BATTERY:
        case VOLTAGE_SENSE:
            result = (
                adcValue * 2.5 * 2 / 4096
            );
            break;
    }

    return result;
}

double getCurrentUsage() {
    return currentAmps.getValue();
}

void enableBatteryCharging(bool enable) {
    if(enable) {
        digitalWrite(PIN_ENABLE_BATT_CHARGE_, LOW);
    } else {
        digitalWrite(PIN_ENABLE_BATT_CHARGE_, HIGH);
    }
}

uint8_t getChargingStatus() {
    int value = analogRead(PIN_I_BATT_CHARGING_);

    if(value < 500) {
        return CHARGING_STATUS_CHARGING_NOW;
    } else if(value > 3500) {
        return CHARGING_STATUS_FULLY_CHARGED;
    } else {
        return CHARGING_STATUS_SHUTDOWN;
    }
}
