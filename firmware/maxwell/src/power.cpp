#include <Arduino.h>
#include "main.h"
#include "pin_map.h"
#include "power.h"

long int lastUpdated = 0;

double dynamoVoltage = 0;
double batteryVoltage = 0;
double senseVoltage = 0;

void updateVoltages() {
    double tempVoltage = getInstantaneousVoltage(VOLTAGE_DYNAMO);
    if(dynamoVoltage == 0) {
        dynamoVoltage = tempVoltage;
    } else {
        dynamoVoltage = (
            dynamoVoltage * (VOLTAGE_SAMPLE_COUNT - 1)
            + tempVoltage
        ) / VOLTAGE_SAMPLE_COUNT;
    }

    tempVoltage = getInstantaneousVoltage(VOLTAGE_BATTERY);
    if(batteryVoltage == 0) {
        batteryVoltage = tempVoltage;
    } else {
        batteryVoltage = (
            batteryVoltage * (VOLTAGE_SAMPLE_COUNT - 1)
            + tempVoltage
        ) / VOLTAGE_SAMPLE_COUNT;
    }

    tempVoltage = getInstantaneousVoltage(VOLTAGE_SENSE);
    if(senseVoltage == 0) {
        senseVoltage = tempVoltage;
    } else {
        senseVoltage = (
            senseVoltage * (VOLTAGE_SAMPLE_COUNT - 1)
            + tempVoltage
        ) / VOLTAGE_SAMPLE_COUNT;
    }


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
    double battery = getVoltage(VOLTAGE_BATTERY);
    double sense = getVoltage(VOLTAGE_SENSE);

    return (battery - sense)/SENSE_RESISTOR_VALUE;
}


void enableBatteryCharging(bool enable) {
    if(enable) {
        digitalWrite(PIN_ENABLE_BATT_CHARGE_, HIGH);
    } else {
        digitalWrite(PIN_ENABLE_BATT_CHARGE_, LOW);
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
