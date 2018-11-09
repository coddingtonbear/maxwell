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

bool gpsFixAvailable;

char nmeaBuffer[255];
MicroNMEA nmea(nmeaBuffer, sizeof(nmeaBuffer));

CANStatusMainMC mainMcStatus;

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
    mainMcStatus = _status;
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
    CANStatusMainMC copied = mainMcStatus;
    return copied;
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
    GPSUart.GPIOSetPinState(5, LOW);
}

void gpsSleep() {
    GPSUart.GPIOSetPinState(5, HIGH);
}


void updateGpsFix() {
    char readByte = GPSUart.read();

    //Output.print(readByte);

    nmea.process(readByte);

    gpsFixAvailable = nmea.isValid();
}

bool gpsFixValid() {
    return gpsFixAvailable;
}

MicroNMEA* getGpsFix() {
    return &nmea;
}
