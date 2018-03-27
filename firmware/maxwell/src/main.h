#pragma once

#include <RTClock.h>
#include <Arduino.h>
#include <HashMap.h>

#include "multiserial.h"

#define CHIRP_INTERVAL 900000
#define CHIRP_INIT_FREQUENCY 2500
#define CHIRP_INIT_DURATION 50
#define CHIRP_FREQUENCY 2500
#define CHIRP_DURATION 50
#define CHIRP_COUNT 3
#define CHIRP_INTRANOTE_INTERVAL 50

#define BOOT_FLASH_DELAY 15000

#define VOLTAGE_LEVEL_WARNING 3.1
#define VOLTAGE_LEVEL_SHUTDOWN 3.0

#define VOLTAGE_UPDATE_INTERVAL 100
#define VOLTAGE_WARNING_INTERVAL 600000

#define STATS_UPDATE_INTERVAL 1000

// These are semi-random to make sure they don't collide too often
#define CANBUS_CHARGING_STATUS_ANNOUNCE_INTERVAL 2201
#define CANBUS_VOLTAGE_BATTERY_ANNOUNCE_INTERVAL 3111
#define CANBUS_CURRENT_ANNOUNCE_INTERVAL 3313
#define CANBUS_SPEED_ANNOUNCE_INTERVAL 1017
#define CANBUS_LED_STATUS_ANNOUNCE_INTERVAL 4120

#define SPEED_WHEEL_RADIUS_INCHES 80.0
#define SPEED_PULSES_PER_ROTATION 14.0
#define SPEED_INCHES_PER_MILE 63360
#define SPEED_SECONDS_PER_HOUR 3.6e6
#define SPEED_SMOOTHING_SAMPLES 5

#define INACTIVITY_SLEEP_DURATION 300000

void setup();
void loop();

void handleCounter();

String sendBluetoothCommand(String);
void enableEsp(bool);
void enableBatteryPower(bool);

void enableCanDebug(bool);

void beep(uint, uint);

void bridgeUART(HardwareSerial*, uint);
HardwareSerial* uartNumberToInterface(uint);
void sleep(bool allowMovementWake=true);

void intSpeedUpdate();

void taskChirpCallback();
void taskVoltageCallback();
void taskVoltageWarningCallback();
void taskCanbusVoltageBatteryAnnounceCallback();
void taskCanbusVoltageDynamoAnnounceCallback();
void taskCanbusCurrentAnnounceCallback();
void taskCanbusChargingStatusAnnounceCallback();
void taskCanbusSpeedAnnounceCallback();
void taskStatisticsCallback();
void taskCanbusLedStatusAnnounceCallback();
void renewKeepalive();

extern MultiSerial Output;
extern HashMap<String, double> Statistics;
extern RTClock Clock;
