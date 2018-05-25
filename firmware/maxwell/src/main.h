#pragma once

#include <RTClock.h>
#include <Arduino.h>
#include <HashMap.h>
#include <SdFat.h>

#include "logger.h"
#include "multiserial.h"

#define CHIRP_INTERVAL 900000
#define CHIRP_INIT_FREQUENCY 2500
#define CHIRP_INIT_DURATION 50
#define CHIRP_FREQUENCY 2500
#define CHIRP_DURATION 50
#define CHIRP_COUNT 3
#define CHIRP_INTRANOTE_INTERVAL 50

#define VOLTAGE_LEVEL_WARNING 3.0
#define VOLTAGE_LEVEL_SHUTDOWN 2.75

#define VOLTAGE_UPDATE_INTERVAL 100
#define VOLTAGE_WARNING_INTERVAL 600000

#define STATS_UPDATE_INTERVAL 1000

#define LOGGER_STATS_INTERVAL 10000

// These are semi-random to make sure they don't collide too often
#define CANBUS_CHARGING_STATUS_ANNOUNCE_INTERVAL 2201
#define CANBUS_VOLTAGE_BATTERY_ANNOUNCE_INTERVAL 3111
#define CANBUS_CURRENT_ANNOUNCE_INTERVAL 3313
#define CANBUS_SPEED_ANNOUNCE_INTERVAL 1017
#define CANBUS_LED_STATUS_ANNOUNCE_INTERVAL 4120
#define CANBUS_STATUS_ANNOUNCE_INTERVAL 2641
#define CANBUS_CURRENT_TIMESTAMP_ANNOUNCE_INTERVAL 9001

#define SPEED_WHEEL_RADIUS_INCHES 80.0
#define SPEED_PULSES_PER_ROTATION 14.0
#define SPEED_INCHES_PER_MILE 63360
#define SPEED_SECONDS_PER_HOUR 3.6e6
#define SPEED_SMOOTHING_SAMPLES 5

#define BLUETOOTH_TIMEOUT 120000
#define INACTIVITY_SLEEP_DURATION 300000

#define MOVEMENT_WAKE_ENABLED false

void setup();
void loop();

void handleEspStatus();
void handleCounter();
void sendEspCommand(String);

String sendBluetoothCommand(String);
void enableEsp(bool);
void enableBluetooth(bool);
void enableBatteryPower(bool);
void enableAutosleep(bool);
bool espIsEnabled();

void enableCanDebug(bool);
void renewKeepalive();
void renewBluetoothKeepalive();

void restoreBackupTime();
void saveBackupTime();

void beep(uint32_t, uint32_t);

void bridgeUART(HardwareSerial*, uint32_t);
HardwareSerial* uartNumberToInterface(uint32_t);
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
void taskCanbusStatusIntervalCallback();
void taskLoggerStatsIntervalCallback();
void taskCanbusCurrentTimestampCallback();

struct ESPStatus {
    uint32_t lastUpdated;
    bool cameraConnected;

    bool wifiEnabled;
    bool bleEnabled;
    bool recordingNow;

    bool cameraStatusValid;
    uint32_t batteryLevel;
    uint32_t bytesAvailable;
};

extern MultiSerial Output;
extern HashMap<String, double> Statistics;
extern RTClock Clock;
extern Logger Log;
extern SdFat filesystem;
extern ESPStatus espStatus;
