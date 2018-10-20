#pragma once

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
