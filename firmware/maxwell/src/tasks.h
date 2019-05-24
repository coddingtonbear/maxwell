#pragma once

#define LOGGER_STATS_INTERVAL 1000
#define SPEED_REFRESH_INTERVAL 500
#define LTE_STATUS_COLLECT_INTERVAL 3200
#define LTE_STATUS_ANNOUNCE_INTERVAL 9000
#define LTE_STATUS_MANAGER_INTERVAL 1100
#define VOLTAGE_UPDATE_INTERVAL 1200
#define DISPLAY_REFRESH_INTERVAL 100

#define VOLTAGE_LEVEL_SHUTDOWN 2.75

#define LOOP_CALLBACK_INTERVAL 25

//#define TASK_DEBUG

namespace tasks {
    void init();
    void loop();
    void logTaskStatistics();
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

    void taskLoopCallback();
};
