#include <Arduino.h>
#include "can_message_ids.h"
#include "main.h"
#include "status.h"

double voltageBattery;
double voltageDynamo;
double voltageSense;
double current;
double velocity;
uint8_t chargingStatus;

CANStatusMainMC status;

void setChargingStatus(uint8_t value) {
    chargingStatus = value;
}

void setStatusParameter(uint32 canMsgId, double value) {
    switch (canMsgId) {
        case CAN_VOLTAGE_BATTERY:
            voltageBattery = value;
            break;
        case CAN_VOLTAGE_DYNAMO:
            voltageDynamo = value;
            break;
        case CAN_VOLTAGE_SENSE:
            voltageSense = value;
            break;
        case CAN_AMPS_CURRENT:
            current = value;
            break;
        case CAN_VELOCITY:
            velocity = value;
            break;
    }
}

void setStatusMainMc(CANStatusMainMC _status) {
    status = _status;
}

double getDoubleStatusParameter(uint32 canMsgId) {
    double returnValue = -1;

    switch (canMsgId) {
        case CAN_VOLTAGE_BATTERY:
            returnValue = voltageBattery;
            break;
        case CAN_VOLTAGE_DYNAMO:
            returnValue = voltageDynamo;
            break;
        case CAN_VOLTAGE_SENSE:
            returnValue = voltageSense;
            break;
        case CAN_AMPS_CURRENT:
            returnValue = current;
            break;
        case CAN_VELOCITY:
            returnValue = velocity;
            break;
    }

    return returnValue;
}

CANStatusMainMC getStatusMainMc() {
    return status;
}

uint8_t getChargingStatus() {
    return chargingStatus;
}
