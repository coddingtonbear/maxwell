#include <Arduino.h>
#include <MicroNMEA.h>

#include "can_message_ids.h"
#include "main.h"
#include "status.h"

double voltageBattery;
double voltageDynamo;
double voltageSense;
double current;
double velocity;
uint8_t chargingStatus;

char nmeaBuffer[255];
MicroNMEA nmea(nmeaBuffer, sizeof(nmeaBuffer));

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

void gpsPMTK(uint cmd, String data) {
    GPSUart.println();
    GPSUart.print("$");

    String commandString = "PMTK" + String(cmd) + String(data);

    GPSUart.print(commandString);
    GPSUart.print("*");

    uint8_t checkSum = 0;

    for (uint8_t i = 0; i < commandString.length(); i++) {
        checkSum = checkSum ^ commandString.charAt(i);
    }

    GPSUart.print(String(checkSum, HEX));
    GPSUart.print("\r\n");

    GPSUart.flush();
    delay(100);
}


void gpsWake() {
    GPSUart.println();
    delay(100);
}


void updateGpsFix() {
    nmea.process((char)GPSUart.read());
}

MicroNMEA* getGpsFix() {
    return &nmea;
}
