#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <CANCommand.h>
#include <TaskScheduler.h>
#include <Button.h>
#include <RTClock.h>
#include <STM32Sleep.h>
#include <libmaple/iwdg.h>

#include "main.h"
#include "led_cycles.h"
#include "serial_commands.h"
#include "can_message_ids.h"
#include "can.h"
#include "display.h"

bool canDebug = 0;

Task taskUpdateDisplay(
    DISPLAY_REFRESH_INTERVAL,
    TASK_FOREVER,
    &taskUpdateDisplayCallback
);
Scheduler taskRunner;

Button buttonLeftA = Button(LEFT_A, true, true, 120);
Button buttonLeftB = Button(LEFT_B, true, true, 120);
Button buttonRightA = Button(RIGHT_A, true, true, 120);
Button buttonRightB = Button(RIGHT_B, true, true, 120);

RTClock Clock(RTCSEL_LSE);

void setup() {
    iwdg_init(IWDG_PRE_256, 2400);

    // Disable JTAG port; we're using JNRST for
    // display control.
    afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY);

    Output.begin(230400, SERIAL_8E1);

    delay(250);

    Output.println("[Maxwell Remote 1.0]");

    // Disable bluetooth
    pinMode(BT_ENABLE_, OUTPUT);
    digitalWrite(BT_ENABLE_, HIGH);
    pinMode(BT_KEY, OUTPUT);
    digitalWrite(BT_KEY, LOW);
    delay(250);
    digitalWrite(BT_ENABLE_, LOW);
    pinMode(CAN_RS, INPUT);

    if(buttonRightA.read()) {
        for(uint8_t i = 20; i > 5; i--) {
            Output.print("Resetting into flash mode in ");
            Output.print(i);
            Output.println(" seconds.");
            delay(1000);
        }

        reset();
    }

    // Wake main microcontroller
    pinMode(WAKE, OUTPUT);
    digitalWrite(WAKE, HIGH);
    delay(100);
    pinMode(WAKE, INPUT);

    // Setup buttons
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

    taskRunner.init();
    taskRunner.addTask(taskUpdateDisplay);
    taskRunner.enableAll();

    setupCommands();
    commandPrompt();
}

void taskUpdateDisplayCallback() {
    Display.refresh();
}

void loop() {
    iwdg_feed();

    buttonLeftA.read();
    buttonRightA.read();
    buttonLeftB.read();
    buttonRightB.read();

    // Long-press
    if(buttonLeftB.pressedFor(LONG_PRESS_INTERVAL)) {
        activateLightingPreset(LED_PRESET_SAFETY);
    }
    if(buttonRightB.pressedFor(LONG_PRESS_INTERVAL)) {
        sleep();
    }
    if(buttonRightA.pressedFor(LONG_PRESS_INTERVAL)) {
        lowPowerMode();
    }

    // Normal motions
    if(buttonLeftA.wasPressed()) {
        Display.up();
    }
    if(buttonLeftB.wasPressed()) {
        Display.down();
    }
    if(buttonRightA.wasPressed()) {
        Display.out();
    }
    if(buttonRightB.wasPressed()) {
        Display.in();
    }

    taskRunner.execute();
    if(Output.available()) {
        refreshLocalBluetoothTimeout();
    } else {
        handleLocalBluetoothTimeout();
    }
    commandLoop();

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

void enableCanDebug(bool enable) {
    canDebug = enable;
}

void sleep() {
    Output.end();
    Wire.end();

    CanMsg message;
    message.IDE = CAN_ID_STD;
    message.RTR = CAN_RTR_DATA;
    message.ID = CAN_CMD_MAIN_MC_SLEEP;
    message.DLC = 0;
    CanBus.send(&message);
    delay(100);
    CanBus.end();

    setGPIOModeToAllPins(GPIO_INPUT_FLOATING);
    // Disable the CAN Transceiver
    pinMode(CAN_RS, OUTPUT);
    digitalWrite(CAN_RS, HIGH);
    // Disable Bluetooth
    pinMode(BT_ENABLE_, OUTPUT);
    digitalWrite(BT_ENABLE_, HIGH);
    // Disable Display
    pinMode(DISPLAY_ON_, OUTPUT);
    digitalWrite(DISPLAY_ON_, HIGH);
    // Wake for left A button
    pinMode(LEFT_A, INPUT_PULLUP);
    attachInterrupt(LEFT_A, nvic_sys_reset, FALLING);
    // Or when the microcontroller wake line rises
    pinMode(WAKE, INPUT_PULLDOWN);
    attachInterrupt(WAKE, nvic_sys_reset, RISING);
    delay(500);
    systick_disable();
    adc_disable_all();
    disableAllPeripheralClocks();
    while(true) {
        iwdg_feed();
        sleepAndWakeUp(STOP, &Clock, 14);
    }
}
