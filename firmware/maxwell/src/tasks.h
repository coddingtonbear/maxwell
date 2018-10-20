#pragma once

// These are semi-random to make sure they don't collide too often
#define STATS_UPDATE_INTERVAL 1000
#define LOGGER_STATS_INTERVAL 10000
#define CANBUS_CHARGING_STATUS_ANNOUNCE_INTERVAL 2201
#define CANBUS_VOLTAGE_BATTERY_ANNOUNCE_INTERVAL 3111
#define CANBUS_CURRENT_ANNOUNCE_INTERVAL 3313
#define CANBUS_SPEED_ANNOUNCE_INTERVAL 1017
#define CANBUS_LED_STATUS_ANNOUNCE_INTERVAL 4120
#define CANBUS_STATUS_ANNOUNCE_INTERVAL 2641
#define CANBUS_CURRENT_TIMESTAMP_ANNOUNCE_INTERVAL 9001
#define LTE_STATUS_ANNOUNCE_INTERVAL 59000
#define LTE_STATUS_MANAGER 1100
#define LTE_TIMESTAMP_SYNC 5000

namespace tasks {
    void init();
    void loop();

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
    void taskLTEStatusAnnounceCallback();
    void taskLTEStatusManagerCallback();
    void taskLTETimestampSyncCallback();
};
