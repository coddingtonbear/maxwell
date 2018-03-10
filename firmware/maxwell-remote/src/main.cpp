#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <CANCommand.h>
#include <TaskScheduler.h>

#include "serial_commands.h"
#include "can_message_ids.h"
#include "can.h"
#include "display.h"
#include "main.h"

Task taskUpdateDisplay(
    DISPLAY_REFRESH_INTERVAL,
    TASK_FOREVER,
    &taskUpdateDisplayCallback
);
Scheduler taskRunner;

void setup() {
    // Disable JTAG port; we're using JNRST for
    // display control.
    afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY);

    pinMode(DISPLAY_ON_, OUTPUT);
    digitalWrite(DISPLAY_ON_, LOW);

    Serial.begin(230400, SERIAL_8E1);

    delay(1000);

    Serial.println("[Maxwell Remote 1.0]");

    pinMode(BT_KEY, OUTPUT);
    digitalWrite(BT_KEY, LOW);
    pinMode(BT_ENABLE_, OUTPUT);
    digitalWrite(BT_ENABLE_, LOW);

    pinMode(RIGHT_A, INPUT_PULLUP);
    pinMode(RIGHT_B, INPUT_PULLUP);
    pinMode(LEFT_A, INPUT_PULLUP);
    pinMode(LEFT_B, INPUT_PULLUP);

    Wire.setClock(400000);
    Wire.begin();

    Display.begin();

    CanBus.map(CAN_GPIO_PB8_PB9);
    CanBus.begin(CAN_SPEED_1000, CAN_MODE_NORMAL);
    CanBus.filter(0, 0, 0);
    CanBus.set_poll_mode();

    setupCommands();
    commandPrompt();
}

void taskUpdateDisplayCallback() {
    Display.refresh();
}

uint8_t pinChanged = 0;
uint32 lastShown = 0;
uint32 speedCounter = 0;

void handleControl() {
    pinChanged = 1;
}

void handleSpeedReceived(uint count) {
    speedCounter = count;
}

void loop() {
    commandLoop();

    if (pinChanged != 0) {
        pinChanged = 0;

        Serial.println("Control event occurred.");
    }

    /*
    if(CanBus.available()) {
        CanMsg *can_message;
        if((can_message = CanBus.recv()) != NULL) {
            display.clearDisplay();
            display.setCursor(0, 20);
            display.println(String(can_message->ID, HEX));
            for(int i = 0; i < can_message->DLC; i++) {
                display.print(String(can_message->Data[i], HEX));
                display.print(" ");
            }
            display.display();

            CANCommand::CANMessage command;
            command.ID = can_message->ID;
            command.DLC = can_message->DLC;
            for (uint8_t i = 0; i < can_message->DLC; i++) {
                command.Data[i] = can_message->Data[i];
            }
            handleCANCommand(&command);

            CanBus.free();
        }
    }
    */
}
