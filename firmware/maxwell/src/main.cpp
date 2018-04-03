
#include <CANCommand.h>
#include <STM32Sleep.h>
#include <Arduino.h>
#include <TimerFreeTone.h>
#include <HardwareCAN.h>
#include <TaskScheduler.h>
#include <libmaple/iwdg.h>

#include "multiserial.h"
#include "can_message_ids.h"
#include "power.h"
#include "neopixel.h"
#include "serial_commands.h"
#include "power.h"
#include "can.h"
#include "pin_map.h"
#include "main.h"

uint32 speedCounter = 0;
uint32 speedCounterPrev = 0;
double currentSpeedMph = 0;
bool canDebug = 0;
uint32 lastStatisticsUpdate = 0;

uint32 lastKeepalive = 0;
uint32 lastBluetoothKeepalive = 0;
bool bluetoothEnabled = true;

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
Scheduler taskRunner;

MultiSerial Output;

HashMap<String, double> Statistics;

RTClock Clock(RTCSEL_LSE);

void setup() {
    afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY);
    iwdg_init(IWDG_PRE_256, 2400);

    pinMode(PIN_BUZZER, OUTPUT);
    digitalWrite(PIN_BUZZER, LOW);

    pinMode(PIN_ESP_BOOT_FLASH_, OUTPUT);
    digitalWrite(PIN_ESP_BOOT_FLASH_, HIGH);
    pinMode(PIN_DISABLE_ESP_, OUTPUT);
    digitalWrite(PIN_DISABLE_ESP_, LOW);

    pinMode(PIN_BT_ENABLE_, OUTPUT);
    digitalWrite(PIN_BT_ENABLE_, LOW);
    pinMode(PIN_BT_KEY, OUTPUT);
    digitalWrite(PIN_BT_KEY, LOW);

    pinMode(PIN_I_WAKE, INPUT_PULLUP);
    pinMode(PIN_I_POWER_ON, INPUT_PULLDOWN);
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

    Output.addInterface(&ESPSerial);
    Output.addInterface(&BTSerial);
    Output.begin(230400, SERIAL_8E1);
    Output.println("[Maxwell 2.0]");
    Output.flush();
    //failsafeReset();

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
    CanBus.send(&wakeMessage);

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
    taskRunner.enableAll();

    Output.println("Ready.");
    setupCommands();
    commandPrompt();
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
    CanBus.send(&status);
    delay(50);

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
    CanBus.send(&message);
    delay(50);
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

    CanBus.send(&message);

    delay(50);
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

    CanBus.send(&message);

    delay(50);
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

    CanBus.send(&message);

    delay(50);
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

    if(currentSpeedMph == 0) {
        currentSpeedMph = mph;
    } else {
        currentSpeedMph = (
            currentSpeedMph * (SPEED_SMOOTHING_SAMPLES - 1)
            + mph
        ) / SPEED_SMOOTHING_SAMPLES;
    }

    unsigned char *speedBytes = reinterpret_cast<byte*>(&currentSpeedMph);
    for(uint8 i = 0; i < sizeof(double); i++) {
        message.Data[i] = speedBytes[i];
    }

    if (pulseCount > 0) {
        renewKeepalive();
    }

    speedCounterPrev = speedCounter;
    CanBus.send(&message);

    delay(50);
}

void loop() {
    iwdg_feed();

    // If we're past the keepalive duration; go to sleep
    if(millis() > lastKeepalive + INACTIVITY_SLEEP_DURATION) {
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

            handleCANCommand(&command);

            CanBus.free();
        }
    }
}

void enableEsp(bool enabled) {
    if(enabled) {
        digitalWrite(PIN_ESP_BOOT_FLASH_, HIGH);
        digitalWrite(PIN_DISABLE_ESP_, LOW);
        delay(500);
        digitalWrite(PIN_DISABLE_ESP_, HIGH);
        delay(500);
        while(ESPSerial.available()) {
            ESPSerial.read();
        }
    } else {
        digitalWrite(PIN_DISABLE_ESP_, LOW);
    }
}

void sleep(bool allowMovementWake) {
    TimerFreeTone(PIN_BUZZER, CHIRP_INIT_FREQUENCY, CHIRP_INIT_DURATION);

    CanMsg sleepMsg;
    sleepMsg.IDE = CAN_ID_STD;
    sleepMsg.RTR = CAN_RTR_DATA;
    sleepMsg.ID = CAN_MAIN_MC_SLEEP;
    sleepMsg.DLC = 0;
    CanBus.send(&sleepMsg);
    delay(20);

    enableEsp(false);
    ledEnable(false);
    enableBluetooth(false);
    //gpsWake();
    //gpsPMTK(161, ",0");

    pinMode(PIN_I_WAKE, INPUT_PULLDOWN);
    attachInterrupt(PIN_I_WAKE, nvic_sys_reset, RISING);
    if (allowMovementWake) {
        pinMode(PIN_I_SPEED, INPUT_PULLDOWN);
        attachInterrupt(PIN_I_SPEED, nvic_sys_reset, RISING);
    }

    systick_disable();
    disableAllPeripheralClocks();
    while(true) {
        iwdg_feed();
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

void enableBluetooth(bool enable) {
    if(enable) {
        digitalWrite(PIN_BT_ENABLE_, LOW);
        bluetoothEnabled = true;
    } else {
        digitalWrite(PIN_BT_ENABLE_, HIGH);
        bluetoothEnabled = false;
    }
}

void renewBluetoothKeepalive() {
    lastBluetoothKeepalive = millis();
}
