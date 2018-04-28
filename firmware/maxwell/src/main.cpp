#include <CANCommand.h>
#include <STM32Sleep.h>
#include <Arduino.h>
#include <TimerFreeTone.h>
#include <HardwareCAN.h>
#include <TaskScheduler.h>
#include <libmaple/iwdg.h>
#include <SdFat.h>
#include <SPI.h>

#include "multiserial.h"
#include "can_message_ids.h"
#include "power.h"
#include "neopixel.h"
#include <RollingAverage.h>
#include "serial_commands.h"
#include "power.h"
#include "can.h"
#include "pin_map.h"
#include "main.h"

uint32 speedCounter = 0;
uint32 speedCounterPrev = 0;

RollingAverage<double, 5> currentSpeedMph;
bool canDebug = 0;
uint32 lastStatisticsUpdate = 0;

uint32 lastKeepalive = 0;
uint32 lastBluetoothKeepalive = 0;
bool bluetoothEnabled = true;
bool bleEnabled = false;

bool autosleepEnabled = true;

Task taskChirp(CHIRP_INTERVAL, TASK_FOREVER, &taskChirpCallback);
Task taskVoltage(VOLTAGE_UPDATE_INTERVAL, TASK_FOREVER, &taskVoltageCallback);
Task taskStatistics(
    STATS_UPDATE_INTERVAL,
    TASK_FOREVER,
    &taskStatisticsCallback
);
Task taskVoltageWarning(
    VOLTAGE_WARNING_INTERVAL,
    TASK_FOREVER,
    &taskVoltageWarningCallback
);
Task taskCanbusVoltageBatteryAnnounce(
    CANBUS_VOLTAGE_BATTERY_ANNOUNCE_INTERVAL,
    TASK_FOREVER,
    &taskCanbusVoltageBatteryAnnounceCallback
);
Task taskCanbusCurrentAnnounce(
    CANBUS_CURRENT_ANNOUNCE_INTERVAL,
    TASK_FOREVER,
    &taskCanbusCurrentAnnounceCallback
);
Task taskCanbusChargingStatusAnnounce(
    CANBUS_CHARGING_STATUS_ANNOUNCE_INTERVAL,
    TASK_FOREVER,
    &taskCanbusChargingStatusAnnounceCallback
);
Task taskCanbusSpeedAnnounce(
    CANBUS_SPEED_ANNOUNCE_INTERVAL,
    TASK_FOREVER,
    &taskCanbusSpeedAnnounceCallback
);
Task taskCanbusLedStatusAnnounce(
    CANBUS_LED_STATUS_ANNOUNCE_INTERVAL,
    TASK_FOREVER,
    &taskCanbusLedStatusAnnounceCallback
);
Task taskLoggerStatsInterval(
    LOGGER_STATS_INTERVAL,
    TASK_FOREVER,
    &taskLoggerStatsIntervalCallback
);
Task taskCanbusStatusInterval(
    CANBUS_STATUS_ANNOUNCE_INTERVAL,
    TASK_FOREVER,
    &taskCanbusStatusIntervalCallback
);
Task taskCanbusCurrentTimestamp(
    CANBUS_CURRENT_ANNOUNCE_INTERVAL,
    TASK_FOREVER,
    &taskCanbusCurrentTimestampCallback
);
Scheduler taskRunner;

MultiSerial Output;

HashMap<String, double> Statistics;

SdFat filesystem(2);

Logger Log(&filesystem);

RTClock Clock(RTCSEL_LSE);

SPIClass SPIBus(2);

void setup() {
    afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY);
    iwdg_init(IWDG_PRE_256, 2400);

    Output.addInterface(&ESPSerial);
    Output.addInterface(&BTSerial);
    Output.begin(230400, SERIAL_8E1);
    Output.println("[Maxwell 2.0]");
    Output.flush();

    if(Clock.getTime() < 100000) {
        restoreBackupTime();
    }

    SPIBus.begin();
    if(!filesystem.begin(PIN_SPI_CS_A, SD_SCK_MHZ(18))) {
        Output.println("Error initializing SD Card");
        filesystem.initErrorPrint(&Output);
    }
    Log.begin();
    Log.log(String("Device reset: ") + String(RCC_BASE->CSR, HEX));
    if(RCC_BASE->CSR & (1 << 31)) {
        Log.log("Reset reason: Low Power");
    }
    if(RCC_BASE->CSR & (1 << 30)) {
        Log.log("Reset reason: Window Watchdog");
    }
    if(RCC_BASE->CSR & (1 << 29)) {
        Log.log("Reset reason: Independent Watchdog");
    }
    if(RCC_BASE->CSR & (1 << 28)) {
        Log.log("Reset reason: Software Reset");
    }
    if(RCC_BASE->CSR & (1 << 27)) {
        Log.log("Reset reason: POR/PDR");
    }
    if(RCC_BASE->CSR & (1 << 26)) {
        Log.log("Reset reason: NRST");
    }
    if(RCC_BASE->CSR & (1 << 25)) {
        Log.log("Reset reason: BOR");
    }
    // Clear reset flags
    RCC_BASE->CSR |= RCC_CSR_RMVF;

    pinMode(PIN_BUZZER, OUTPUT);
    digitalWrite(PIN_BUZZER, LOW);

    pinMode(PIN_ESP_BOOT_FLASH_, OUTPUT);
    digitalWrite(PIN_ESP_BOOT_FLASH_, HIGH);
    pinMode(PIN_DISABLE_ESP_, OUTPUT);
    digitalWrite(PIN_DISABLE_ESP_, LOW);

    pinMode(PIN_BT_KEY, OUTPUT);
    digitalWrite(PIN_BT_KEY, LOW);
    pinMode(PIN_BT_ENABLE_, OUTPUT);
    digitalWrite(PIN_BT_ENABLE_, HIGH);
    delay(150);  // We need it to start up in LOW, and it was prev floating
    digitalWrite(PIN_BT_ENABLE_, LOW);

    pinMode(PIN_I_POWER_ON, INPUT_PULLUP);
    pinMode(PIN_I_BATT_CHARGING_, INPUT_ANALOG);
    pinMode(PIN_I_BATT_VOLTAGE, INPUT_ANALOG);
    pinMode(PIN_I_CURRENT_SENSE, INPUT_ANALOG);
    pinMode(PIN_I_DYNAMO_VOLTAGE, INPUT_ANALOG);
    pinMode(PIN_ENABLE_BATT_POWER, OUTPUT);
    digitalWrite(PIN_ENABLE_BATT_POWER, LOW);
    pinMode(PIN_ENABLE_BATT_CHARGE_, OUTPUT);
    digitalWrite(PIN_ENABLE_BATT_CHARGE_, LOW);

    pinMode(PIN_I_SPEED, INPUT_PULLDOWN);
    attachInterrupt(PIN_I_SPEED, intSpeedUpdate, RISING);

    enableBatteryCharging(true);

    TimerFreeTone(PIN_BUZZER, CHIRP_INIT_FREQUENCY, CHIRP_INIT_DURATION);

    //GPSSerial.begin(9600);
    //gpsWake();
    delay(100);
    //gpsPMTK(161, ",0");  // Disable the GPS

    CanBus.map(CAN_GPIO_PB8_PB9);
    CanBus.begin(CAN_SPEED_1000, CAN_MODE_NORMAL);
    CanBus.filter(0, 0, 0);
    CanBus.set_poll_mode();

    CanMsg wakeMessage;
    wakeMessage.IDE = CAN_ID_STD;
    wakeMessage.RTR = CAN_RTR_DATA;
    wakeMessage.ID = CAN_MAIN_MC_WAKE;
    wakeMessage.DLC = 0;
    canTx(&wakeMessage);

    ledSetup();
    enableEsp(false);

    taskRunner.init();
    taskRunner.addTask(taskChirp);
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
    taskRunner.enableAll();

    Output.println("Ready.");
    setupCommands();
    commandPrompt();

    Log.log("Ready");
}

String sendBluetoothCommand(String command) {
    String result;

    Output.flush();

    delay(250);
    digitalWrite(PIN_BT_KEY, HIGH);
    delay(250);
    Output.println(command);
    Output.flush();
    delay(250);
    digitalWrite(PIN_BT_KEY, LOW);
    delay(250);

    uint32 started = millis();

    Output.flush();
    while(millis() < started + 1000) {
        while(Output.available() > 0) {
            result += (char)Output.read();
        }
    }
    Output.flush();
    delay(100);

    return result;
}

void bridgeUART(HardwareSerial* bridged, uint32_t baud) {
    bridged->begin(baud);

    while(true) {
        iwdg_feed();
        if (Output.available()) {
            uint8_t value = Output.read();

            if (value == 4) {
                break;
            }
            bridged->write(value);
        }
        if (bridged->available()) {
            Output.write(bridged->read());
        }
    }

    Output.begin();
}

HardwareSerial* uartNumberToInterface(uint32_t uartNumber) {
    HardwareSerial* uart;
    if(uartNumber == 1) {
        uart = &BTSerial;
    } else if (uartNumber == 2) {
        uart = &ESPSerial;
    } else if (uartNumber == 3) {
        uart = &GPSSerial;
    } else if (uartNumber == 4) {
        uart = &UART4;
    } else if (uartNumber == 5) {
        uart = &UART5;
    }

    return uart;
}

void beep(uint32_t frequency, uint32_t duration) {
    TimerFreeTone(PIN_BUZZER, frequency, duration);
}

void taskChirpCallback() {
    for(uint8_t i = 0; i < CHIRP_COUNT; i++) {
        beep(CHIRP_FREQUENCY, CHIRP_DURATION);
        delay(CHIRP_INTRANOTE_INTERVAL);
    }
}

void taskCanbusLedStatusAnnounceCallback() {
    LedStatus ledStatus;
    ledGetStatus(ledStatus);

    CanMsg status;
    status.IDE = CAN_ID_STD;
    status.RTR = CAN_RTR_DATA;
    status.ID = CAN_LED_STATUS_COLOR;
    status.DLC = sizeof(byte) * 3 + sizeof(uint32);
    status.Data[0] = ledStatus.enabled;
    status.Data[1] = ledStatus.cycle;
    status.Data[2] = ledStatus.brightness;
    unsigned char *intervalBytes = reinterpret_cast<unsigned char*>(&ledStatus.interval);
    for(uint8 i = 3; i < sizeof(double); i++) {
        status.Data[i] = intervalBytes[i - 3];
    }
    canTx(&status);

    CanMsg message;
    message.IDE = CAN_ID_STD;
    message.RTR = CAN_RTR_DATA;
    message.ID = CAN_LED_STATUS_COLOR;
    message.DLC = sizeof(byte) * 6;
    message.Data[0] = ledStatus.red;
    message.Data[1] = ledStatus.green;
    message.Data[2] = ledStatus.blue;
    message.Data[3] = ledStatus.red2;
    message.Data[4] = ledStatus.green2;
    message.Data[5] = ledStatus.blue2;
    canTx(&message);
}

void taskVoltageCallback() {
    updatePowerMeasurements();

    double voltage = getVoltage(VOLTAGE_BATTERY);
    if(voltage < VOLTAGE_LEVEL_SHUTDOWN) {
        Output.println("Low voltage; Shutdown initiated!");
        sleep(false);
    }
}

void taskStatisticsCallback() {
    Statistics.put("Uptime (minutes)", (double)millis() / 60000);

    lastStatisticsUpdate = millis();
}

void taskVoltageWarningCallback() {
    double voltage = getVoltage(VOLTAGE_BATTERY);
    if(voltage < VOLTAGE_LEVEL_WARNING) {
        Output.print("Warning: low voltage (");
        Output.print(voltage, 2);
        Output.println(")");
    }
}
void taskCanbusStatusIntervalCallback() {
    LedStatus ledStatus;
    ledGetStatus(ledStatus);
    uint32 logErrorCode = Log.getErrorCode();

    CANStatusMainMC status;
    status.is_charging = getChargingStatus() == CHARGING_STATUS_CHARGING_NOW;
    status.lighting_enabled = ledStatus.enabled;
    status.charging_enabled = batteryChargingIsEnabled();
    status.ble_enabled = bleEnabled;
    status.bt_enabled = bluetoothEnabled;
    status.has_valid_time = (Clock.getTime() > 1000000000);
    status.logging_now = !logErrorCode;

    CanMsg output;
    output.IDE = CAN_ID_STD;
    output.RTR = CAN_RTR_DATA;
    output.ID = CAN_STATUS_MAIN_MC;
    output.DLC = sizeof(status);

    unsigned char *outputBytes = reinterpret_cast<unsigned char *>(&status);
    for(uint8_t i = 0; i < sizeof(status); i++) {
        output.Data[i] = outputBytes[i];
    }

    canTx(&output);
}

void taskCanbusCurrentTimestampCallback() {
    time_t currentTimestamp = Clock.getTime();

    CanMsg output;
    output.IDE = CAN_ID_STD;
    output.RTR = CAN_RTR_DATA;
    output.ID = CAN_STATUS_MAIN_MC;
    output.DLC = sizeof(time_t);

    unsigned char *outputBytes = reinterpret_cast<unsigned char *>(&currentTimestamp);
    for(uint8_t i = 0; i < sizeof(currentTimestamp); i++) {
        output.Data[i] = outputBytes[i];
    }

    canTx(&output);
}

void taskCanbusVoltageBatteryAnnounceCallback() {
    CanMsg message;
    message.IDE = CAN_ID_STD;
    message.RTR = CAN_RTR_DATA;
    message.ID = CAN_VOLTAGE_BATTERY;
    message.DLC = sizeof(double);

    double voltage = getVoltage(VOLTAGE_BATTERY);
    unsigned char *voltageBytes = reinterpret_cast<unsigned char*>(&voltage);
    for(uint8 i = 0; i < sizeof(double); i++) {
        message.Data[i] = voltageBytes[i];
    }

    canTx(&message);
}

void taskCanbusCurrentAnnounceCallback() {
    CanMsg message;
    message.IDE = CAN_ID_STD;
    message.RTR = CAN_RTR_DATA;
    message.ID = CAN_AMPS_CURRENT;
    message.DLC = sizeof(double);

    double current = getCurrentUsage();
    unsigned char *currentBytes = reinterpret_cast<unsigned char*>(&current);
    for(uint8 i = 0; i < sizeof(double); i++) {
        message.Data[i] = currentBytes[i];
    }

    canTx(&message);
}

void taskCanbusChargingStatusAnnounceCallback() {
    CanMsg message;
    message.IDE = CAN_ID_STD;
    message.RTR = CAN_RTR_DATA;
    message.ID = CAN_CHARGING_STATUS;
    message.DLC = sizeof(uint8_t);

    uint8_t status = getChargingStatus();
    unsigned char *statusBytes = reinterpret_cast<byte*>(&status);
    for(uint8 i = 0; i < sizeof(uint8_t); i++) {
        message.Data[i] = statusBytes[i];
    }

    canTx(&message);
}

void taskCanbusSpeedAnnounceCallback() {
    CanMsg message;
    message.IDE = CAN_ID_STD;
    message.RTR = CAN_RTR_DATA;
    message.ID = CAN_VELOCITY;
    message.DLC = sizeof(double);

    // There are 14 poles in the hub, and the outer tire is 80in in
    // circumference; so every pole is 5.714in of travel.

    uint32 pulseCount = speedCounter - speedCounterPrev;
    double mph = (
        pulseCount * (SPEED_WHEEL_RADIUS_INCHES / SPEED_PULSES_PER_ROTATION)
        / CANBUS_SPEED_ANNOUNCE_INTERVAL
    ) / SPEED_INCHES_PER_MILE * SPEED_SECONDS_PER_HOUR;
    currentSpeedMph.addMeasurement(mph);

    double currentSpeedTemp = currentSpeedMph.getValue();
    unsigned char *speedBytes = reinterpret_cast<byte*>(&currentSpeedTemp);
    for(uint8 i = 0; i < sizeof(double); i++) {
        message.Data[i] = speedBytes[i];
    }

    if (
        pulseCount > 0 ||
        getChargingStatus() == CHARGING_STATUS_CHARGING_NOW
    ) {
        renewKeepalive();
    }

    speedCounterPrev = speedCounter;
    canTx(&message);
}

void loop() {
    iwdg_feed();

    // If we're past the keepalive duration; go to sleep
    if(millis() > lastKeepalive + INACTIVITY_SLEEP_DURATION && autosleepEnabled) {
        sleep();
    }
    // If we're past the keepalive for bluetooth, deactivate bluetooth, too.
    if(millis() > lastBluetoothKeepalive + BLUETOOTH_TIMEOUT) {
        enableBluetooth(false);
    }
    // If there are bytes on the serial buffer; keep the device alive
    if(Output.available()) {
        renewKeepalive();
        renewBluetoothKeepalive();
    }
    commandLoop();

    ledCycle();
    //gps.available(GPSSerial);  // Update GPS with serial data

    // Misc. periodic tasks
    taskRunner.execute();

    if(CanBus.available()) {
        CanMsg* canMsg;
        if((canMsg = CanBus.recv()) != NULL) {
            CANCommand::CANMessage command;
            command.ID = canMsg->ID;
            command.DLC = canMsg->DLC;

            for (uint8_t i = 0; i < canMsg->DLC; i++) {
                command.Data[i] = canMsg->Data[i];
            }

            if(canDebug) {
                Output.print("Can Message: [");
                Output.print(canMsg->ID, HEX);
                Output.print("](");
                Output.print(canMsg->DLC, HEX);
                Output.print(") ");
                for(uint8_t i = 0; i < canMsg->DLC; i++) {
                    Output.print(canMsg->Data[i], HEX);
                }
                Output.println();
            }
            Log.logCanIncoming(canMsg);

            handleCANCommand(&command);

            CanBus.free();
        }
    }
}

void enableEsp(bool enabled) {
    Log.log("ESP32 enabled: " + String(enabled));
    if(enabled) {
        bleEnabled = true;
        digitalWrite(PIN_ESP_BOOT_FLASH_, HIGH);
        digitalWrite(PIN_DISABLE_ESP_, LOW);
        delay(500);
        digitalWrite(PIN_DISABLE_ESP_, HIGH);
        delay(500);
        while(ESPSerial.available()) {
            ESPSerial.read();
        }
    } else {
        bleEnabled = false;
        digitalWrite(PIN_DISABLE_ESP_, LOW);
    }
}

void sleep(bool allowMovementWake) {
    Log.log("Sleep requested");
    if(allowMovementWake) {
        Log.log("Movement wake enabled");
    }
    Log.end();
    Output.end();
    filesystem.card()->spiStop();
    TimerFreeTone(PIN_BUZZER, CHIRP_INIT_FREQUENCY, CHIRP_INIT_DURATION);

    // Disable canbus
    CanMsg sleepMsg;
    sleepMsg.IDE = CAN_ID_STD;
    sleepMsg.RTR = CAN_RTR_DATA;
    sleepMsg.ID = CAN_MAIN_MC_SLEEP;
    sleepMsg.DLC = 0;
    canTx(&sleepMsg);
    CanBus.end();

    setGPIOModeToAllPins(GPIO_INPUT_FLOATING);
    // Turn of CAN transceiver
    pinMode(PIN_CAN_RS, OUTPUT);
    digitalWrite(PIN_CAN_RS, HIGH);
    // Disable buzzer
    pinMode(PIN_BUZZER, OUTPUT);
    digitalWrite(PIN_BUZZER, LOW);
    // Disable ESP32
    pinMode(PIN_DISABLE_ESP_, OUTPUT);
    digitalWrite(PIN_DISABLE_ESP_, LOW);
    //pinMode(PIN_ESP_BOOT_FLASH_, OUTPUT);
    //digitalWrite(PIN_ESP_BOOT_FLASH_, LOW);
    // Disable Bluetooth
    pinMode(PIN_BT_ENABLE_, OUTPUT);
    digitalWrite(PIN_BT_ENABLE_, HIGH);
    // Disable neopixel battery drain
    pinMode(PIN_ENABLE_BATT_POWER, OUTPUT);
    digitalWrite(PIN_ENABLE_BATT_POWER, LOW);
    // Configure wake conditions
    pinMode(PIN_I_POWER_ON, INPUT_PULLDOWN);
    attachInterrupt(PIN_I_POWER_ON, nvic_sys_reset, RISING);
    if (allowMovementWake) {
        pinMode(PIN_I_SPEED, INPUT_PULLDOWN);
        attachInterrupt(PIN_I_SPEED, nvic_sys_reset, RISING);
    }

    systick_disable();
    adc_disable_all();
    disableAllPeripheralClocks();
    bkp_init();
    bkp_enable_writes();
    while(true) {
        iwdg_feed();
        saveBackupTime();
        sleepAndWakeUp(STOP, &Clock, 14);
    }
}

void intSpeedUpdate() {
    speedCounter++;
}

void enableCanDebug(bool enable) {
    canDebug = enable;
}

void renewKeepalive() {
    lastKeepalive = millis();
}

void enableAutosleep(bool enable) {
    Log.log("Autosleep enabled: " + String(enable));
    autosleepEnabled = enable;
}

void enableBluetooth(bool enable) {
    if(enable && !bluetoothEnabled) {
        Log.log("Local bluetooth enabled");
        Output.disableInterface(&BTSerial);
        BTSerial.end();
        digitalWrite(PIN_BT_ENABLE_, LOW);
        bluetoothEnabled = true;
    } else if(!enable && bluetoothEnabled) {
        Log.log("Local bluetooth disabled");
        digitalWrite(PIN_BT_ENABLE_, HIGH);
        Output.enableInterface(&BTSerial);
        Output.begin();
        bluetoothEnabled = false;
    }
}

void renewBluetoothKeepalive() {
    lastBluetoothKeepalive = millis();
}

void taskLoggerStatsIntervalCallback() {

    for(uint8_t i = 0; i < Statistics.count(); i++) {
        auto key = Statistics.keyAt(i);
        auto value = Statistics.valueFor(key);

        String message = "Stats: ";
        message += key;
        message += ": ";
        message += String(value, 4);
        Log.log(message);
    }

    Log.log("Stats: Speed Pulse Count: " + String(speedCounter));
}

void restoreBackupTime() {
    uint16_t backedUp = bkp_read(0);
    uint16_t uptime = millis() / 1000;

    Clock.setTime(backedUp + uptime);
}

void saveBackupTime() {
    time_t currentTime = Clock.getTime();
    bkp_write(0, currentTime);
}
