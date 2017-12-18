#include "power.h"

int getRawVoltageAdcValue(uint source) {
    int result = -1;

    switch(source) {
        case VOLTAGE_DYNAMO:
            result = analogRead(I_DYNAMO_VOLTAGE);
            break;
        case VOLTAGE_BATTERY:
            result = analogRead(I_BATTERY_VOLTAGE);
            break;
        case VOLTAGE_SENSE:
            result = analogRead(I_CURRENT_SENSE);
            break;
    }

    return result;
}

double getVoltage(uint source) {
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
                (10 * adcValue + 4.7 * adcValue)
                / 10 / 4096 * 3.3
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
        digitalWrite(ENABLE_BATT_CHARGE_, HIGH);
    } else {
        digitalWrite(ENABLE_BATT_CHARGE_, LOW);
    }
}


void enableAuxDevices(bool enable) {
    if(enable) {
        digitalWrite(ENABLE_AUX_DEVICES, HIGH);
    } else {
        digitalWrite(ENABLE_AUX_DEVICES, LOW);
    }
}
