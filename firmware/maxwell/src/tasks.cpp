#include <TaskScheduler.h>

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

Task taskVoltage(VOLTAGE_UPDATE_INTERVAL, TASK_FOREVER, &tasks::taskVoltageCallback);
Task taskStatistics(
    STATS_UPDATE_INTERVAL,
    TASK_FOREVER,
    &tasks::taskStatisticsCallback
);
Task taskVoltageWarning(
    VOLTAGE_WARNING_INTERVAL,
    TASK_FOREVER,
    &tasks::taskVoltageWarningCallback
);
Task taskCanbusVoltageBatteryAnnounce(
    CANBUS_VOLTAGE_BATTERY_ANNOUNCE_INTERVAL,
    TASK_FOREVER,
    &tasks::taskCanbusVoltageBatteryAnnounceCallback
);
Task taskCanbusCurrentAnnounce(
    CANBUS_CURRENT_ANNOUNCE_INTERVAL,
    TASK_FOREVER,
    &tasks::taskCanbusCurrentAnnounceCallback
);
Task taskCanbusChargingStatusAnnounce(
    CANBUS_CHARGING_STATUS_ANNOUNCE_INTERVAL,
    TASK_FOREVER,
    &tasks::taskCanbusChargingStatusAnnounceCallback
);
Task taskCanbusSpeedAnnounce(
    CANBUS_SPEED_ANNOUNCE_INTERVAL,
    TASK_FOREVER,
    &tasks::taskCanbusSpeedAnnounceCallback
);
Task taskCanbusLedStatusAnnounce(
    CANBUS_LED_STATUS_ANNOUNCE_INTERVAL,
    TASK_FOREVER,
    &tasks::taskCanbusLedStatusAnnounceCallback
);
Task taskLoggerStatsInterval(
    LOGGER_STATS_INTERVAL,
    TASK_FOREVER,
    &tasks::taskLoggerStatsIntervalCallback
);
Task taskCanbusStatusInterval(
    CANBUS_STATUS_ANNOUNCE_INTERVAL,
    TASK_FOREVER,
    &tasks::taskCanbusStatusIntervalCallback
);
Task taskCanbusCurrentTimestamp(
    CANBUS_CURRENT_TIMESTAMP_ANNOUNCE_INTERVAL,
    TASK_FOREVER,
    &tasks::taskCanbusCurrentTimestampCallback
);
Task taskLTEStatusAnnounce(
    LTE_STATUS_ANNOUNCE_INTERVAL,
    TASK_FOREVER,
    &tasks::taskLTEStatusAnnounceCallback
);
Task taskLTEStatusManager(
    LTE_STATUS_MANAGER,
    TASK_FOREVER,
    &tasks::taskLTEStatusManagerCallback
);
Task taskLTETimestampSync(
    LTE_TIMESTAMP_SYNC,
    TASK_FOREVER,
    &tasks::taskLTETimestampSyncCallback
);

Scheduler taskRunner;

void tasks::init() {
    taskRunner.init();
    taskRunner.addTask(taskVoltage);
    taskRunner.addTask(taskVoltageWarning);
    taskRunner.addTask(taskCanbusVoltageBatteryAnnounce);
    taskRunner.addTask(taskCanbusCurrentAnnounce);
    taskRunner.addTask(taskCanbusChargingStatusAnnounce);
    taskRunner.addTask(taskCanbusSpeedAnnounce);
    taskRunner.addTask(taskStatistics);
    taskRunner.addTask(taskCanbusLedStatusAnnounce);
    taskRunner.addTask(taskLoggerStatsInterval);
    taskRunner.addTask(taskCanbusStatusInterval);
    taskRunner.addTask(taskCanbusCurrentTimestamp);
    taskRunner.addTask(taskLTEStatusAnnounce);
    taskRunner.addTask(taskLTEStatusManager);
    taskRunner.enableAll();
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
    power::updatePowerMeasurements();

    double voltage = power::getVoltage(VOLTAGE_BATTERY);
    if(voltage < VOLTAGE_LEVEL_SHUTDOWN) {
        Output.println("Low voltage; Shutdown initiated!");
        power::sleep();
    }
}

void tasks::taskStatisticsCallback() {
    Statistics.put("Uptime (minutes)", (double)millis() / 60000);

    lastStatisticsUpdate = millis();
}

void tasks::taskVoltageWarningCallback() {
    double voltage = power::getVoltage(VOLTAGE_BATTERY);
    if(voltage < VOLTAGE_LEVEL_WARNING) {
        Output.print("Warning: low voltage (");
        Output.print(voltage, 2);
        Output.println(")");
    }
}
void tasks::taskCanbusStatusIntervalCallback() {
    LedStatus ledStatus;
    neopixel::getStatus(ledStatus);
    uint32 logErrorCode = Log.getErrorCode();

    CANStatusMainMC status;
    status.is_charging = power::getChargingStatus() == CHARGING_STATUS_CHARGING_NOW;
    status.lighting_enabled = ledStatus.enabled;
    status.charging_enabled = power::batteryChargingIsEnabled();
    status.bt_enabled = ble::bluetoothIsEnabled();
    status.has_valid_time = (Clock.getTime() > 1000000000);
    status.logging_now = !logErrorCode;
    // ESP32 Status
    status.wifi_enabled = false;
    status.ble_enabled = false;
    status.camera_connected = false;
    status.recording_now = false;

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

void tasks::taskCanbusChargingStatusAnnounceCallback() {
    CanMsg message;
    message.IDE = CAN_ID_STD;
    message.RTR = CAN_RTR_DATA;
    message.ID = CAN_CHARGING_STATUS;
    message.DLC = sizeof(uint8_t);

    uint8_t status = power::getChargingStatus();
    unsigned char *statusBytes = reinterpret_cast<byte*>(&status);
    for(uint8 i = 0; i < sizeof(uint8_t); i++) {
        message.Data[i] = statusBytes[i];
    }

    CanBus.send(&message);
}

void tasks::taskCanbusSpeedAnnounceCallback() {
    CanMsg message;
    message.IDE = CAN_ID_STD;
    message.RTR = CAN_RTR_DATA;
    message.ID = CAN_VELOCITY;
    message.DLC = sizeof(double);

    double currentSpeedTemp = status::getSpeed();
    unsigned char *speedBytes = reinterpret_cast<byte*>(&currentSpeedTemp);
    for(uint8 i = 0; i < sizeof(double); i++) {
        message.Data[i] = speedBytes[i];
    }

    CanBus.send(&message);
}

void tasks::taskLoggerStatsIntervalCallback() {

    for(uint8_t i = 0; i < Statistics.count(); i++) {
        auto key = Statistics.keyAt(i);
        auto value = Statistics.valueFor(key);

        String message = "Stats: ";
        message += key;
        message += ": ";
        message += String(value, 4);
        Log.log(message);
    }
}

void tasks::taskLTEStatusAnnounceCallback() {
    status::sendStatusUpdate();
}

void tasks::taskLTEStatusManagerCallback() {
    lte::asyncManagerLoop();
}

void tasks::taskLTETimestampSyncCallback() {
    if(util::syncTimestampWithLTE()) {
        // We've synced successfuly; we can disable now
        taskLTETimestampSync.disable();
    }
}

