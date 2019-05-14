#pragma once

// These are semi-random to make sure they don't collide too often
#define LOGGER_STATS_INTERVAL 10000
#define SPEED_REFRESH_INTERVAL 500
#define LTE_STATUS_COLLECT_INTERVAL 3200
#define LTE_STATUS_ANNOUNCE_INTERVAL 9000
#define LTE_STATUS_MANAGER 1100
#define VOLTAGE_UPDATE_INTERVAL 1011
#define DISPLAY_REFRESH_INTERVAL 100

#define VOLTAGE_LEVEL_SHUTDOWN 2.75

//#define TASK_DEBUG

namespace tasks {
    void init();
    void loop();
    void printTaskStatistics();

    void enableLTEStatusManager(bool _enable=true);

    void start(String);

    void taskVoltageCallback();
    void taskLoggerStatsIntervalCallback();
    void taskCanbusCurrentTimestampCallback();
    void taskLTEStatusCollectCallback();
    void taskLTEStatusAnnounceCallback();
    void taskLTEStatusManagerCallback();
    void taskSpeedRefreshCallback();
    void taskDisplayRefreshCallback();
};
