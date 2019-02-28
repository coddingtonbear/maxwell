#pragma once

// These are semi-random to make sure they don't collide too often
#define LOGGER_STATS_INTERVAL 10000
#define SPEED_REFRESH_INTERVAL 500
#define CANBUS_TIMESTAMP_ANNOUNCE_INTERVAL 2224
#define CANBUS_VOLTAGE_BATTERY_ANNOUNCE_INTERVAL 3111
#define CANBUS_VOLTAGE_DYNAMO_ANNOUNCE_INTERVAL 3204
#define CANBUS_CURRENT_ANNOUNCE_INTERVAL 3313
#define CANBUS_SPEED_ANNOUNCE_INTERVAL 600
#define CANBUS_LED_STATUS_ANNOUNCE_INTERVAL 4120
#define CANBUS_STATUS_ANNOUNCE_INTERVAL 724
#define CANBUS_CURRENT_TIMESTAMP_ANNOUNCE_INTERVAL 9001
#define LTE_STATUS_COLLECT_INTERVAL 3200
#define LTE_STATUS_ANNOUNCE_INTERVAL 9000
#define LTE_STATUS_MANAGER 1100
#define VOLTAGE_UPDATE_INTERVAL 1011

#define VOLTAGE_LEVEL_SHUTDOWN 2.75

//#define TASK_DEBUG

namespace tasks {
    void init();
    void loop();
    void printTaskStatistics();

    void enableLTEStatusManager(bool _enable=true);

    void start(String);

    void taskVoltageCallback();
    void taskCanbusVoltageBatteryAnnounceCallback();
    void taskCanbusVoltageDynamoAnnounceCallback();
    void taskCanbusTimestampAnnounceCallback();
    void taskCanbusCurrentAnnounceCallback();
    void taskCanbusSpeedAnnounceCallback();
    void taskCanbusLedStatusAnnounceCallback();
    void taskCanbusStatusIntervalCallback();
    void taskLoggerStatsIntervalCallback();
    void taskCanbusCurrentTimestampCallback();
    void taskLTEStatusCollectCallback();
    void taskLTEStatusAnnounceCallback();
    void taskLTEStatusManagerCallback();
    void taskSpeedRefreshCallback();
};
