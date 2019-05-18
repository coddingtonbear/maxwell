#include <Arduino.h>
#undef min
#undef max
#include <TaskScheduler.h>
#include <libmaple/iwdg.h>
#include <MCP79412RTC.h>

#include "tasks.h"
#include "neopixel.h"
#include "power.h"
#include "status.h"
#include "lte.h"
#include "bluetooth.h"
#include "util.h"
#include "display.h"

namespace tasks {
    uint32 lastStatisticsUpdate = 0;

    uint8_t logRotation = 0;

    Scheduler taskRunner;

    Task taskDisplay(
        DISPLAY_REFRESH_INTERVAL,
        TASK_FOREVER,
        &tasks::taskDisplayRefreshCallback,
        &taskRunner
    );
    Task taskVoltage(
        VOLTAGE_UPDATE_INTERVAL,
        TASK_FOREVER,
        &tasks::taskVoltageCallback,
        &taskRunner
    );
    Task taskSpeedRefresh(
        SPEED_REFRESH_INTERVAL,
        TASK_FOREVER,
        &tasks::taskSpeedRefreshCallback,
        &taskRunner
    );
    Task taskLoggerStatsInterval(
        LOGGER_STATS_INTERVAL,
        TASK_FOREVER,
        &tasks::taskLoggerStatsIntervalCallback,
        &taskRunner
    );
    Task taskLTEStatusCollect(
        LTE_STATUS_COLLECT_INTERVAL,
        TASK_FOREVER,
        &tasks::taskLTEStatusCollectCallback,
        &taskRunner
    );
    Task taskLTEStatusEmit(
        LTE_STATUS_ANNOUNCE_INTERVAL,
        TASK_FOREVER,
        &tasks::taskLTEStatusAnnounceCallback,
        &taskRunner
    );
    Task taskLTEStatusManager(
        LTE_STATUS_MANAGER,
        TASK_FOREVER,
        &tasks::taskLTEStatusManagerCallback,
        &taskRunner
    );
}

void tasks::init() {
    taskRunner.enableAll();

    // This will be automatically enabled when necessary
    taskLTEStatusManager.disable();

    #ifdef TASK_DEBUG
        UART4.begin(115200);
    #endif
}

void tasks::loop() {
    taskRunner.execute();
}

void tasks::start(String message) {
    #ifdef TASK_DEBUG
        UART4.print("<Task: ");
        UART4.print(message);
        UART4.println(">");
        UART4.flush();
        
        delay(50);
    #endif
}

void tasks::enableLTEStatusManager(bool _enable) {
    if (_enable) {
        taskLTEStatusManager.enable();
    } else {
        taskLTEStatusManager.disable();
    }
}

void tasks::taskVoltageCallback() {
    tasks::start("Voltage");

    power::updatePowerMeasurements();
}

void tasks::taskLoggerStatsIntervalCallback() {
    tasks::start("Logger stats interval");

    // Nothing for now
    status::logStatusUpdate();
    logTaskStatistics();
}

void tasks::taskLTEStatusAnnounceCallback() {
    tasks::start("LTE logger emit");

    status::sendStatusUpdate();
}

void tasks::taskLTEStatusManagerCallback() {
    tasks::start("LTE status manager iteration");

    lte::asyncManagerLoop();
}

void tasks::taskSpeedRefreshCallback() {
    tasks::start("Recalculate velocity");

    status::refreshSpeed();
}

void tasks::taskLTEStatusCollectCallback() {
    tasks::start("LTE status collection");

    if(lte::isEnabled()){
        lte::collectStatusInformation();
    }
}

void tasks::logTaskStatistics() {
    // Don't log everything every cycle since logging
    // takes enough time that you might see LED stuttering
    if(logRotation == 0) {
        Log.log("tasks", "voltage: average: " + String(taskVoltage.getAverageRuntime()));
    } else if(logRotation == 1) {
        Log.log("tasks", "voltage: total: " + String(taskVoltage.getTotalRuntime()));
    } else if(logRotation == 2) {
        Log.log("tasks", "speed: average: " + String(taskSpeedRefresh.getAverageRuntime()));
    } else if(logRotation == 3) {
        Log.log("tasks", "speed: total: " + String(taskSpeedRefresh.getTotalRuntime()));
    } else if(logRotation == 4) {
        Log.log("tasks", "log stats: average: " + String(taskLoggerStatsInterval.getAverageRuntime()));
    } else if(logRotation == 5) {
        Log.log("tasks", "log stats: total: " + String(taskLoggerStatsInterval.getTotalRuntime()));
    } else if(logRotation == 6) {
        Log.log("tasks", "lte status update: average: " + String(taskLTEStatusCollect.getAverageRuntime()));
    } else if(logRotation == 7) {
        Log.log("tasks", "lte status update: total: " + String(taskLTEStatusCollect.getTotalRuntime()));
    } else if (logRotation == 8) {
        Log.log("tasks", "lte status mgr: average: " + String(taskLTEStatusManager.getAverageRuntime()));
    } else if(logRotation == 9) {
        Log.log("tasks", "lte status mgr: total: " + String(taskLTEStatusManager.getTotalRuntime()));
    } else if (logRotation == 10) {
        Log.log("tasks", "display refresh: average: " + String(taskDisplay.getAverageRuntime()));
    } else if(logRotation == 11) {
        Log.log("tasks", "display refresh: total: " + String(taskDisplay.getTotalRuntime()));
    } else {
        logRotation = 0;
        logTaskStatistics();
        return;
    }

    logRotation++;
}

void tasks::printTaskStatistics() {
    Output.print("Voltage: ");
    Output.print(taskVoltage.getAverageRuntime());
    Output.print(" (");
    Output.print(taskVoltage.getTotalRuntime());
    Output.println(")");

    Output.print("Speed: ");
    Output.print(taskSpeedRefresh.getAverageRuntime());
    Output.print(" (");
    Output.print(taskSpeedRefresh.getTotalRuntime());
    Output.println(")");

    Output.print("Logger Stats: ");
    Output.print(taskLoggerStatsInterval.getAverageRuntime());
    Output.print(" (");
    Output.print(taskLoggerStatsInterval.getTotalRuntime());
    Output.println(")");

    Output.print("LTE Status Update: ");
    Output.print(taskLTEStatusCollect.getAverageRuntime());
    Output.print(" (");
    Output.print(taskLTEStatusCollect.getTotalRuntime());
    Output.println(")");

    Output.print("LTE Status Announce: ");
    Output.print(taskLTEStatusEmit.getAverageRuntime());
    Output.print(" (");
    Output.print(taskLTEStatusEmit.getTotalRuntime());
    Output.println(")");

    Output.print("LTE Status Manager: ");
    Output.print(taskLTEStatusManager.getAverageRuntime());
    Output.print(" (");
    Output.print(taskLTEStatusManager.getTotalRuntime());
    Output.println(")");

    Output.print("Display Refresh: ");
    Output.print(taskDisplay.getAverageRuntime());
    Output.print(" (");
    Output.print(taskDisplay.getTotalRuntime());
    Output.println(")");
}

void tasks::taskDisplayRefreshCallback() {
    tasks::start("Display refresh");
    Display.refresh();
}
