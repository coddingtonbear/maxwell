
#include <CANCommand.h>
#include <STM32Sleep.h>
#include <Arduino.h>
#include <TimerFreeTone.h>
#include <HardwareCAN.h>
#include <TaskScheduler.h>

#include "multiserial.h"
#include "can_message_ids.h"
#include "power.h"
#include "neopixel.h"
#include "serial_commands.h"
#include "can.h"
#include "gps.h"
#include "pin_map.h"
#include "main.h"

uint32 speedCounter = 0;

Task taskChirp(CHIRP_INTERVAL, TASK_FOREVER, &taskChirpCallback);
Task taskVoltage(VOLTAGE_UPDATE_INTERVAL, TASK_FOREVER, &taskVoltageCallback);
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
Task taskCanbusVoltageDynamoAnnounce(
    CANBUS_VOLTAGE_DYNAMO_ANNOUNCE_INTERVAL,
    TASK_FOREVER,
    &taskCanbusVoltageDynamoAnnounceCallback
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
Scheduler taskRunner;

MultiSerial Output;

void setup() {
    afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY);

    pinMode(PIN_BUZZER, OUTPUT);
    digitalWrite(PIN_BUZZER, LOW);

    pinMode(PIN_ESP_BOOT_FLASH_, OUTPUT);
    digitalWrite(PIN_ESP_BOOT_FLASH_, HIGH);
    pinMode(PIN_DISABLE_ESP_, OUTPUT);
    digitalWrite(PIN_DISABLE_ESP_, LOW);

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
    digitalWrite(PIN_ENABLE_BATT_CHARGE_, HIGH);

    pinMode(PIN_I_SPEED, INPUT);

    Output.addInterface(&ESPSerial);
    Output.addInterface(&BTSerial);
    Output.begin(230400, SERIAL_8E1);
    Output.println("[Maxwell 2.0]");
    Output.flush();

    GPSSerial.begin(9600);
    gpsWake();

    CanBus.map(CAN_GPIO_PB8_PB9);
    CanBus.begin(CAN_SPEED_1000, CAN_MODE_NORMAL);
    CanBus.filter(0, 0, 0);
    CanBus.set_poll_mode();

    setupCommands();

    commandPrompt();

    CanMsg wakeMessage;
    wakeMessage.IDE = CAN_ID_STD;
    wakeMessage.RTR = CAN_RTR_DATA;
    wakeMessage.ID = CAN_MAIN_MC_WAKE;
    wakeMessage.DLC = 0;
    CanBus.send(&wakeMessage);

    ledSetup();
    enableEsp(true);

    taskRunner.init();
    taskRunner.addTask(taskChirp);
    taskRunner.addTask(taskVoltage);
    taskRunner.addTask(taskVoltageWarning);
    taskRunner.addTask(taskCanbusVoltageBatteryAnnounce);
    taskRunner.addTask(taskCanbusVoltageDynamoAnnounce);
    taskRunner.addTask(taskCanbusCurrentAnnounce);
    taskRunner.addTask(taskCanbusChargingStatusAnnounce);
    taskRunner.enableAll();
}

void handleCounter() {
    if(digitalRead(PIN_I_SPEED)) {
        speedCounter++;
    }
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

void bridgeUART(HardwareSerial* bridged, uint baud) {
    bridged->begin(baud);

    while(true) {
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

void beep(uint frequency, uint duration) {
    TimerFreeTone(PIN_BUZZER, frequency, duration);
}

void taskChirpCallback() {
    for(uint8_t i = 0; i < CHIRP_COUNT; i++) {
        beep(CHIRP_FREQUENCY, CHIRP_DURATION);
        delay(CHIRP_INTRANOTE_INTERVAL);
    }
}

void taskVoltageCallback() {
    updateVoltages();

    double voltage = getVoltage(VOLTAGE_BATTERY);
    if(voltage < 2.9) {
        Output.println("Low voltage; Shutdown initiated!");
        sleep();
    }
}

void taskVoltageWarningCallback() {
    double voltage = getVoltage(VOLTAGE_BATTERY);
    if(voltage < 3.2) {
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
    unsigned char *voltageBytes = reinterpret_cast<byte*>(&voltage);
    for(uint8 i = 0; i < sizeof(double); i++) {
        message.Data[i] = voltageBytes[i];
    }

    CanBus.send(&message);

    delay(50);
}

void taskCanbusVoltageDynamoAnnounceCallback() {
    CanMsg message;
    message.IDE = CAN_ID_STD;
    message.RTR = CAN_RTR_DATA;
    message.ID = CAN_VOLTAGE_DYNAMO;
    message.DLC = sizeof(double);

    double voltage = getVoltage(VOLTAGE_DYNAMO);
    unsigned char *voltageBytes = reinterpret_cast<byte*>(&voltage);
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
    unsigned char *currentBytes = reinterpret_cast<byte*>(&current);
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

void loop() {
    commandLoop();

    ledCycle();
    gps.available(GPSSerial);  // Update GPS with serial data

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
            Output.println("");

            handleCANCommand(&command);
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

void sleep() {
    CanMsg sleepMsg;
    sleepMsg.IDE = CAN_ID_STD;
    sleepMsg.RTR = CAN_RTR_DATA;
    sleepMsg.ID = CAN_MAIN_MC_SLEEP;
    sleepMsg.DLC = 0;
    CanBus.send(&sleepMsg);
    delay(20);

    enableEsp(false);
    ledEnable(false);
    gpsPMTK(161, ",0");
    systick_disable();

    pinMode(PIN_I_WAKE, INPUT_PULLDOWN);
    attachInterrupt(PIN_I_WAKE, nvic_sys_reset, RISING);
    pinMode(PIN_I_SPEED, INPUT);
    attachInterrupt(PIN_I_SPEED, nvic_sys_reset, RISING);

    goToSleep(STANDBY);
}
