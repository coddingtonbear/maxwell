#include <Arduino.h>
#include "main.h"
#include "pin_map.h"
#include "power.h"

long int lastUpdated = 0;

double dynamoVoltage = 0;
double batteryVoltage = 0;
double senseVoltage = 0;
double currentAmps = 0;

double lastChargingStatusSample = 0;

void updatePowerMeasurements() {
    double tempVoltage;
    double tempBattVoltage;
    double tempSenseVoltage;
    double tempAmps;

    tempVoltage = getInstantaneousVoltage(VOLTAGE_BATTERY);
    tempBattVoltage = tempVoltage;
    if(batteryVoltage == 0) {
        batteryVoltage = tempVoltage;
    } else {
        batteryVoltage = (
            batteryVoltage * (POWER_SAMPLE_COUNT - 1)
            + tempVoltage
        ) / POWER_SAMPLE_COUNT;
    }

    tempVoltage = getInstantaneousVoltage(VOLTAGE_SENSE);
    tempSenseVoltage = tempVoltage;
    if(senseVoltage == 0) {
        senseVoltage = tempVoltage;
    } else {
        senseVoltage = (
            senseVoltage * (POWER_SAMPLE_COUNT - 1)
            + tempVoltage
        ) / POWER_SAMPLE_COUNT;
    }

    tempAmps = (
        tempBattVoltage - tempSenseVoltage
    )/SENSE_RESISTOR_VALUE;
    if(currentAmps == 0) {
        currentAmps = tempAmps;
    } else {
        currentAmps = (
            currentAmps * (POWER_SAMPLE_COUNT - 1)
            + tempAmps
        ) / POWER_SAMPLE_COUNT;
    }

    Statistics.put("Battery Voltage", batteryVoltage);
    if(Statistics.valueFor("Battery Voltage (Max)") < batteryVoltage) {
        Statistics.put("Battery Voltage (Max)", batteryVoltage);
    }
    Statistics.put("Sense Voltage", senseVoltage);
    if(Statistics.valueFor("Sense Voltage (Max)") < senseVoltage) {
        Statistics.put("Sense Voltage (Max)", senseVoltage);
    }
    Statistics.put("Current (Amps)", currentAmps);
    if(Statistics.valueFor("Current (Amps) (Max)") < currentAmps) {
        Statistics.put("Current (Amps) (Max)", currentAmps);
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
        case VOLTAGE_DYNAMO:
            result = analogRead(PIN_I_DYNAMO_VOLTAGE);
            break;
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
        case VOLTAGE_DYNAMO:
            result = dynamoVoltage;
            break;
        case VOLTAGE_BATTERY:
            result = batteryVoltage;
            break;
        case VOLTAGE_SENSE:
            result = senseVoltage;
            break;
    }

    return result;
}

double getInstantaneousVoltage(uint source) {
    double adcValue = getRawVoltageAdcValue(source);
    double result = -1;

    switch(source) {
        case VOLTAGE_DYNAMO:
            result = (
                (10 * adcValue + 1.8 * adcValue)
                / 10 / 4096 * 3.3
            );
            break;
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
    return currentAmps;
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
