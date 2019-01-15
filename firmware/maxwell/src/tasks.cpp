#include <Arduino.h>
#undef min
#undef max
#include <TaskScheduler.h>
#include <libmaple/iwdg.h>

#include "tasks.h"
#include "can.h"
#include "neopixel.h"
#include "can_message_ids.h"
#include "power.h"
#include "status.h"
#include "lte.h"
#include "bluetooth.h"
#include "util.h"

uint32 lastStatisticsUpdate = 0;

Scheduler taskRunner;

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
Task taskCanbusVoltageBatteryAnnounce(
    CANBUS_VOLTAGE_BATTERY_ANNOUNCE_INTERVAL,
    TASK_FOREVER,
    &tasks::taskCanbusVoltageBatteryAnnounceCallback,
    &taskRunner
);
Task taskCanbusCurrentAnnounce(
    CANBUS_CURRENT_ANNOUNCE_INTERVAL,
    TASK_FOREVER,
    &tasks::taskCanbusCurrentAnnounceCallback,
    &taskRunner
);
Task taskCanbusSpeedAnnounce(
    CANBUS_SPEED_ANNOUNCE_INTERVAL,
    TASK_FOREVER,
    &tasks::taskCanbusSpeedAnnounceCallback,
    &taskRunner
);
Task taskCanbusLedStatusAnnounce(
    CANBUS_LED_STATUS_ANNOUNCE_INTERVAL,
    TASK_FOREVER,
    &tasks::taskCanbusLedStatusAnnounceCallback,
    &taskRunner
);
Task taskLoggerStatsInterval(
    LOGGER_STATS_INTERVAL,
    TASK_FOREVER,
    &tasks::taskLoggerStatsIntervalCallback,
    &taskRunner
);
Task taskCanbusEmitStatus(
    CANBUS_STATUS_ANNOUNCE_INTERVAL,
    TASK_FOREVER,
    &tasks::taskCanbusStatusIntervalCallback,
    &taskRunner
);
Task taskCanbusCurrentTimestamp(
    CANBUS_CURRENT_TIMESTAMP_ANNOUNCE_INTERVAL,
    TASK_FOREVER,
    &tasks::taskCanbusCurrentTimestampCallback,
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

void tasks::init() {
    taskRunner.enableAll();

    // This will be automatically enabled when necessary
    taskLTEStatusManager.disable();
}

void tasks::enableLTEStatusManager(bool _enable) {
    if (_enable) {
        taskLTEStatusManager.enable();
    } else {
        taskLTEStatusManager.disable();
    }
}

void tasks::loop() {
    taskRunner.execute();
}

void tasks::taskCanbusLedStatusAnnounceCallback() {
    #ifdef TASK_DEBUG
        Output.println("<Task: LED Status Announce>");
    #endif
    LedStatus ledStatus;
    neopixel::getStatus(ledStatus);

    CANLedStatus ledStatusMsg;
    ledStatusMsg.enabled = ledStatus.enabled;
    ledStatusMsg.cycle = ledStatus.cycle;
    ledStatusMsg.brightness = ledStatus.brightness;
    ledStatusMsg.interval = ledStatus.interval;

    CanMsg status;
    status.IDE = CAN_ID_STD;
    status.RTR = CAN_RTR_DATA;
    status.ID = CAN_LED_STATUS;
    status.DLC = sizeof(ledStatusMsg);
    unsigned char *ledStatusBytes = reinterpret_cast<unsigned char*>(&ledStatusMsg);
    for(uint8 i = 0; i < sizeof(ledStatusMsg); i++) {
        status.Data[i] = ledStatusBytes[i];
    }
    CanBus.send(&status);

    CANLedStatusColor ledStatusColor;
    ledStatusColor.red = ledStatus.red;
    ledStatusColor.green = ledStatus.green;
    ledStatusColor.blue = ledStatus.blue;
    ledStatusColor.red2 = ledStatus.red2;
    ledStatusColor.green2 = ledStatus.green2;
    ledStatusColor.blue2 = ledStatus.blue2;

    CanMsg statusColor;
    statusColor.IDE = CAN_ID_STD;
    statusColor.RTR = CAN_RTR_DATA;
    statusColor.ID = CAN_LED_STATUS_COLOR;
    statusColor.DLC = sizeof(byte) * 6;
    unsigned char *ledStatusColorBytes = reinterpret_cast<unsigned char*>(&ledStatusColor);
    for(uint8 i = 0; i < sizeof(ledStatusColor); i++) {
        statusColor.Data[i] = ledStatusColorBytes[i];
    }
    CanBus.send(&statusColor);
}

void tasks::taskVoltageCallback() {
    #ifdef TASK_DEBUG
        Output.println("<Task: Voltage>");
    #endif
    power::updatePowerMeasurements();
}

void tasks::taskCanbusStatusIntervalCallback() {
    #ifdef TASK_DEBUG
        Output.println("<Task: CANBUS status emit>");
    #endif
    LedStatus ledStatus;
    neopixel::getStatus(ledStatus);
    uint32 logErrorCode = Log.getErrorCode();

    CANStatusMainMC status;
    status.is_charging = power::getChargingStatus() == CHARGING_STATUS_CHARGING_NOW;
    status.lighting_enabled = ledStatus.enabled;
    status.charging_enabled = true;
    status.bt_enabled = ble::bluetoothIsEnabled();
    status.lte_enabled = lte::isEnabled();

    status.lte_connected = false;
    AsyncModem::SIM7000::NETWORK_STATUS netStatus = lte::getNetworkStatus();
    if(
        (netStatus == AsyncModem::SIM7000::NETWORK_STATUS::REGISTERED_HOME)
        || (netStatus == AsyncModem::SIM7000::NETWORK_STATUS::REGISTERED_ROAMING)
    ) {
        status.lte_connected = true;
    }

    status.has_valid_time = (Clock.getTime() > 1000000000);
    status.logging_now = !logErrorCode;
    status.logging_lte = (
        ((millis() - status::getLastStatusUpdateTime()) < 60000)
        && status::getLastStatusUpdateTime() > 0
    );

    CanMsg output;
    output.IDE = CAN_ID_STD;
    output.RTR = CAN_RTR_DATA;
    output.ID = CAN_STATUS_MAIN_MC;
    output.DLC = sizeof(status);

    unsigned char *outputBytes = reinterpret_cast<unsigned char *>(&status);
    for(uint8_t i = 0; i < sizeof(status); i++) {
        output.Data[i] = outputBytes[i];
    }

    CanBus.send(&output);
}

void tasks::taskCanbusCurrentTimestampCallback() {
    #ifdef TASK_DEBUG
        Output.println("<Task: CANBUS current timestamp emit>");
    #endif
    time_t currentTimestamp = Clock.getTime();

    CanMsg output;
    output.IDE = CAN_ID_STD;
    output.RTR = CAN_RTR_DATA;
    output.ID = CAN_CURRENT_TIMESTAMP;
    output.DLC = sizeof(time_t);

    unsigned char *outputBytes = reinterpret_cast<unsigned char *>(&currentTimestamp);
    for(uint8_t i = 0; i < sizeof(currentTimestamp); i++) {
        output.Data[i] = outputBytes[i];
    }

    CanBus.send(&output);
}

void tasks::taskCanbusVoltageBatteryAnnounceCallback() {
    #ifdef TASK_DEBUG
        Output.println("<Task: CANBUS battery voltage emit>");
    #endif
    CanMsg message;
    message.IDE = CAN_ID_STD;
    message.RTR = CAN_RTR_DATA;
    message.ID = CAN_VOLTAGE_BATTERY;
    message.DLC = sizeof(double);

    double voltage = power::getVoltage(VOLTAGE_BATTERY);
    unsigned char *voltageBytes = reinterpret_cast<unsigned char*>(&voltage);
    for(uint8 i = 0; i < sizeof(double); i++) {
        message.Data[i] = voltageBytes[i];
    }

    CanBus.send(&message);
}

void tasks::taskCanbusCurrentAnnounceCallback() {
    #ifdef TASK_DEBUG
        Output.println("<Task: CANBUS current emit>");
    #endif
    CanMsg message;
    message.IDE = CAN_ID_STD;
    message.RTR = CAN_RTR_DATA;
    message.ID = CAN_AMPS_CURRENT;
    message.DLC = sizeof(double);

    double current = power::getCurrentUsage();
    unsigned char *currentBytes = reinterpret_cast<unsigned char*>(&current);
    for(uint8 i = 0; i < sizeof(double); i++) {
        message.Data[i] = currentBytes[i];
    }

    CanBus.send(&message);
}


void tasks::taskCanbusSpeedAnnounceCallback() {
    #ifdef TASK_DEBUG
        Output.println("<Task: CANBUS speed emit>");
    #endif
    CanMsg message;
    message.IDE = CAN_ID_STD;
    message.RTR = CAN_RTR_DATA;
    message.ID = CAN_VELOCITY;
    message.DLC = sizeof(double);

    double currentSpeedTemp = status::getSpeed();
    #ifdef TASK_DEBUG
        Output.println(currentSpeedTemp);
    #endif
    unsigned char *speedBytes = reinterpret_cast<byte*>(&currentSpeedTemp);
    for(uint8 i = 0; i < sizeof(double); i++) {
        message.Data[i] = speedBytes[i];
    }
    CanBus.send(&message);
}

void tasks::taskLoggerStatsIntervalCallback()
{
    #ifdef TASK_DEBUG
        Output.println("<Task: Logger stats interval>");
    #endif
    // Nothing for now
}

void tasks::taskLTEStatusAnnounceCallback() {
    #ifdef TASK_DEBUG
        Output.println("<Task: LTE Logger Emit>");
    #endif
    status::sendStatusUpdate();
}

void tasks::taskLTEStatusManagerCallback() {
    #ifdef TASK_DEBUG
        Output.println("<Task: LTE Status Manager Iteration>");
    #endif
    lte::asyncManagerLoop();
}

void tasks::taskSpeedRefreshCallback() {
    #ifdef TASK_DEBUG
        Output.println("<Task: Recalculate Velocity>");
    #endif
    status::refreshSpeed();
}

void tasks::taskLTEStatusCollectCallback() {
    #ifdef TASK_DEBUG
        Output.println("<Task: LTE Status Collection>");
    #endif
    if(lte::isEnabled()){
        lte::collectStatusInformation();
    }
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

    Output.print("Voltage Announce: ");
    Output.print(taskCanbusVoltageBatteryAnnounce.getAverageRuntime());
    Output.print(" (");
    Output.print(taskCanbusVoltageBatteryAnnounce.getTotalRuntime());
    Output.println(")");

    Output.print("Current Announce: ");
    Output.print(taskCanbusCurrentAnnounce.getAverageRuntime());
    Output.print(" (");
    Output.print(taskCanbusCurrentAnnounce.getTotalRuntime());
    Output.println(")");

    Output.print("Speed Announce: ");
    Output.print(taskCanbusSpeedAnnounce.getAverageRuntime());
    Output.print(" (");
    Output.print(taskCanbusSpeedAnnounce.getTotalRuntime());
    Output.println(")");

    Output.print("LED Announce: ");
    Output.print(taskCanbusLedStatusAnnounce.getAverageRuntime());
    Output.print(" (");
    Output.print(taskCanbusLedStatusAnnounce.getTotalRuntime());
    Output.println(")");

    Output.print("Logger Stats: ");
    Output.print(taskLoggerStatsInterval.getAverageRuntime());
    Output.print(" (");
    Output.print(taskLoggerStatsInterval.getTotalRuntime());
    Output.println(")");

    Output.print("General Status Announce: ");
    Output.print(taskCanbusEmitStatus.getAverageRuntime());
    Output.print(" (");
    Output.print(taskCanbusEmitStatus.getTotalRuntime());
    Output.println(")");

    Output.print("Timestamp Announce: ");
    Output.print(taskCanbusCurrentTimestamp.getAverageRuntime());
    Output.print(" (");
    Output.print(taskCanbusCurrentTimestamp.getTotalRuntime());
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
}
