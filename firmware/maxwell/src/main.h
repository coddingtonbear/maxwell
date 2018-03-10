#pragma once

#include <Arduino.h>

#include "multiserial.h"

#define CHIRP_INTERVAL 900000
#define CHIRP_FREQUENCY 2500
#define CHIRP_DURATION 50
#define CHIRP_COUNT 3
#define CHIRP_INTRANOTE_INTERVAL 50

#define VOLTAGE_UPDATE_INTERVAL 100
#define VOLTAGE_WARNING_INTERVAL 600000

// These are semi-random to make sure they don't collide too often
#define CANBUS_CHARGING_STATUS_ANNOUNCE_INTERVAL 8104
#define CANBUS_VOLTAGE_BATTERY_ANNOUNCE_INTERVAL 5000
#define CANBUS_VOLTAGE_DYNAMO_ANNOUNCE_INTERVAL 6220
#define CANBUS_CURRENT_ANNOUNCE_INTERVAL 14400

void setup();
void loop();

void handleCounter();

String sendBluetoothCommand(String);
void enableEsp(bool);
void enableBatteryPower(bool);

void beep(uint, uint);

void bridgeUART(HardwareSerial*, uint);
void sleep();

void taskChirpCallback();
void taskVoltageCallback();
void taskVoltageWarningCallback();
void taskCanbusVoltageBatteryAnnounceCallback();
void taskCanbusVoltageDynamoAnnounceCallback();
void taskCanbusCurrentAnnounceCallback();
void taskCanbusChargingStatusAnnounceCallback();

extern MultiSerial Output;
