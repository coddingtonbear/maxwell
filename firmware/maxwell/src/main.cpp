
#include <CANCommand.h>
#include <STM32Sleep.h>
#include <Arduino.h>
#include <TimerFreeTone.h>
//#include <HardwareCAN.h>

#include "multiserial.h"
#include "can_message_ids.h"
#include "power.h"
#include "neopixel.h"
#include "serial_commands.h"
#include "can.h"
#include "gps.h"
#include "pin_map.h"
#include "main.h"

uint32 lastMessage = 0;
uint32 speedCounter = 0;
uint32 lastChirp = 0;

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

    pinMode(PIN_I_POWER_ON, INPUT_PULLDOWN);
    pinMode(PIN_I_BATT_CHARGING_, INPUT);
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

    /*
    HardwareCAN& canBus = getCanbus();
    canBus.map(CAN_GPIO_PB8_PB9);
    canBus.begin(CAN_SPEED_1000, CAN_MODE_NORMAL);
    canBus.filter(0, 0, 0);
    canBus.set_poll_mode();
    */

    setupCommands();

    commandPrompt();

    /*
    CanMsg wakeMessage;
    wakeMessage.IDE = CAN_ID_STD;
    wakeMessage.RTR = CAN_RTR_DATA;
    wakeMessage.ID = CAN_MAIN_MC_WAKE;
    wakeMessage.DLC = 0;
    sendCanMessage(&wakeMessage);
    */

    ledSetup();

    enableEsp(true);
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

void loop() {
    ledCycle();
    commandLoop();
    voltageLoop();
    /*
    HardwareCAN& canBus = getCanbus();
    if(canBus.available()) {
        CanMsg* canMsg;
        if((canMsg = canBus.recv()) != NULL) {
            CANCommand::CANMessage command;
            command.ID = canMsg->ID;
            command.DLC = canMsg->DLC;

            Output.print("Received CAN Message: ");
            Output.print(canMsg->ID, HEX);
            Output.print(" (");
            Output.print(canMsg->DLC);
            Output.print(")");

            for (uint8_t i = 0; i < canMsg->DLC; i++) {
                Output.print(canMsg->Data[i], HEX);
                Output.print(" ");

                command.Data[i] = canMsg->Data[i];
            }
            Output.println("");

            handleCANCommand(&command);
        }
    }
    */

    gps.available(GPSSerial);

    if (lastChirp == 0 || millis() > lastChirp + CHIRP_INTERVAL) {
        for(uint8_t i = 0; i < CHIRP_COUNT; i++) {
            beep(CHIRP_FREQUENCY, CHIRP_DURATION);
            delay(CHIRP_INTRANOTE_INTERVAL);
        }

        lastChirp = millis();
    }

    if(lastMessage == 0 || millis() > lastMessage + 1000) {
        //Output.println(millis());
        /*
        MCP2515::ERROR error;
        struct can_frame speedFrame;
        unsigned char *speedBytes = reinterpret_cast<unsigned char*>(&speedCounter);
        speedFrame.can_id = CAN_VELOCITY;
        speedFrame.can_dlc = sizeof(uint32);
        strcpy((char*)speedBytes, (char*)speedFrame.data);
        error = canbus.sendMessage(&speedFrame);
        if(error != MCP2515::ERROR_OK) {
            Output.print("ERR: ");
            Output.println(error, DEC);
        }
        */

        /*
        Output.println(millis());
        MCP2515::ERROR error;
        double voltage;
        unsigned char *voltageBytes;

        struct can_frame batteryVoltageFrame;
        voltage = getVoltage(VOLTAGE_BATTERY);
        voltageBytes = reinterpret_cast<unsigned char *>(&voltage);
        batteryVoltageFrame.can_id = CAN_VOLTAGE_BATTERY;
        batteryVoltageFrame.can_dlc = sizeof(double);
        strcpy((char*)voltageBytes, (char*)batteryVoltageFrame.data);
        error = canbus.sendMessage(&batteryVoltageFrame);
        if(error != MCP2515::ERROR_OK) {
            Output.print("ERR: ");
            Output.println(error, DEC);
        }
        delay(50);

        struct can_frame dynamoVoltageFrame;
        voltage = getVoltage(VOLTAGE_DYNAMO);
        voltageBytes = reinterpret_cast<unsigned char *>(&voltage);
        dynamoVoltageFrame.can_id = CAN_VOLTAGE_DYNAMO;
        dynamoVoltageFrame.can_dlc = sizeof(double);
        strcpy((char*)voltageBytes, (char*)dynamoVoltageFrame.data);
        error = canbus.sendMessage(&dynamoVoltageFrame);
        if(error != MCP2515::ERROR_OK) {
            Output.print("ERR: ");
            Output.println(error, DEC);
        }
        delay(50);

        struct can_frame senseVoltageFrame;
        voltage = getVoltage(VOLTAGE_SENSE);
        voltageBytes = reinterpret_cast<unsigned char *>(&voltage);
        senseVoltageFrame.can_id = CAN_VOLTAGE_SENSE;
        senseVoltageFrame.can_dlc = sizeof(double);
        strcpy((char*)voltageBytes, (char*)senseVoltageFrame.data);
        error = canbus.sendMessage(&senseVoltageFrame);
        if(error != MCP2515::ERROR_OK) {
            Output.print("ERR: ");
            Output.println(error, DEC);
        }

        delay(50);

        struct can_frame millisFrame;
        double millisValue = millis();
        unsigned char *millisBytes = (
            reinterpret_cast<unsigned char *>(&millisValue)
        );
        millisFrame.can_id = CAN_MC_MILLIS;
        millisFrame.can_dlc = sizeof(double);
        strcpy((char*)millisBytes, (char*)millisFrame.data);
        error = canbus.sendMessage(&millisFrame);
        if(error != MCP2515::ERROR_OK) {
            Output.print("ERR: ");
            Output.println(error, DEC);
        }
        delay(50);
        */

        lastMessage = millis();
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
    enableEsp(false);
    ledEnable(false);
    gpsPMTK(161, ",0");
    systick_disable();

    attachInterrupt(PIN_I_WAKE, nvic_sys_reset, RISING);

    goToSleep(STANDBY);
}
