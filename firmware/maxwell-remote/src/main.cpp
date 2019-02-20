#include <Arduino.h>
#undef min
#undef max
#include "main.h"
#include <SPI.h>

#include <Adafruit_GFX.h>
#include <CANCommand.h>
#include <TaskScheduler.h>
#include <JC_Button.h>
#include <RTClock.h>
#include <STM32Sleep.h>
#include <libmaple/iwdg.h>
#include <SC16IS750.h>

#include "led_cycles.h"
#include "serial_commands.h"
#include "can_message_ids.h"
#include "can.h"
#include "display.h"
#include "status.h"

bool canDebug = 0;

Task taskUpdateDisplay(
    DISPLAY_REFRESH_INTERVAL,
    TASK_FOREVER,
    &taskUpdateDisplayCallback
);
Task taskGpsRefresh(
    GPS_REFRESH_INTERVAL,
    TASK_FOREVER,
    &taskGpsRefreshCallback
);
Task taskTimestampRefresh(
    TIMESTAMP_REFRESH_INTERVAL,
    TASK_FOREVER,
    &taskTimestampRefreshCallback
);
Scheduler taskRunner;

Button buttonLeftA = Button(LEFT_A, 120, true, true);
Button buttonLeftB = Button(LEFT_B, 120, true, true);
Button buttonRightA = Button(RIGHT_A, 120, true, true);
Button buttonRightB = Button(RIGHT_B, 120, true, true);

SC16IS750 GPSUart = SC16IS750(
    SPI_CS2,
    SC16IS750_CHAN_B,
    14745600UL
);

SC16IS750 AlternateUart = SC16IS750(
    SPI_CS2,
    SC16IS750_CHAN_A,
    14745600UL
);

RTClock Clock(RTCSEL_LSE);

void setup() {
    iwdg_init(IWDG_PRE_256, 4095);

    // Disable JTAG port; we're using JNRST for
    // display control.
    afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY);

    // Remap SPI pins to the alternate set
    afio_remap(AFIO_REMAP_SPI1);
    gpio_set_mode(GPIOB, 3, GPIO_AF_OUTPUT_PP);
    gpio_set_mode(GPIOB, 4, GPIO_INPUT_FLOATING);
    gpio_set_mode(GPIOB, 5, GPIO_AF_OUTPUT_PP);

    Output.begin(230400, SERIAL_8E1);

    delay(250);

    Output.println("[Maxwell Remote 1.0]");

    digitalWrite(BT_KEY, LOW);
    pinMode(BT_KEY, OUTPUT);
    digitalWrite(BT_DISABLE_, HIGH);
    pinMode(BT_DISABLE_, OUTPUT);
    pinMode(CAN_RS, INPUT);

    pinMode(BACKLIGHT_ON_, OUTPUT);
    digitalWrite(SPI_CS2, HIGH);
    pinMode(SPI_CS2, OUTPUT);
    digitalWrite(SPI_CS3, HIGH);
    pinMode(SPI_CS3, OUTPUT);
    digitalWrite(SPI_CS4, HIGH);
    pinMode(SPI_CS4, OUTPUT);

    buttonRightA.begin();
    buttonRightB.begin();
    buttonLeftA.begin();
    buttonLeftB.begin();

    // Wake main microcontroller
    digitalWrite(WAKE, HIGH);
    pinMode(WAKE, OUTPUT);
    delay(100);
    pinMode(WAKE, INPUT);

    // Setup buttons
    pinMode(RIGHT_A, OUTPUT);
    pinMode(RIGHT_B, OUTPUT);
    pinMode(LEFT_A, OUTPUT);
    pinMode(LEFT_B, OUTPUT);

    Display.begin();
    Display.setContrast(180);

    GPSUart.begin(9600, true);
    GPSUart.GPIOSetPinState(5, HIGH);
    GPSUart.GPIOSetPinMode(5, OUTPUT);
    GPSUart.GPIOSetPinMode(6, INPUT);
    GPSUart.GPIOSetPinMode(7, INPUT);
    if(!GPSUart.ping()) {
        Output.println("Error connecting to UART over SPI; no GPS available.");
    }
    gpsWake();

    CanBus.map(CAN_GPIO_PB8_PB9);
    CanBus.begin(CAN_SPEED_1000, CAN_MODE_NORMAL);
    CanBus.filter(0, 0, 0);
    CanBus.set_poll_mode();

    taskRunner.init();
    taskRunner.addTask(taskUpdateDisplay);
    taskRunner.addTask(taskGpsRefresh);
    taskRunner.addTask(taskTimestampRefresh);
    taskRunner.enableAll();

    setupCommands();
    commandPrompt();

    // This is the button we used to turn the device on
    buttonLeftA.ignoreNextChange();
}

void taskUpdateDisplayCallback() {
    Display.refresh();
}

void taskGpsRefreshCallback() {
    sendUpdatedGpsPosition();
}

void taskTimestampRefreshCallback() {
    sendUpdatedTimestamp();
}

void loop() {
    iwdg_feed();

    buttonLeftA.read();
    buttonRightA.read();
    buttonLeftB.read();
    buttonRightB.read();

    while(GPSUart.available()) {
        updateGpsFix();
    }

    if(buttonLeftA.pressedFor(LONG_PRESS_INTERVAL)) {
        buttonLeftA.ignorePress();
        buttonLeftA.ignoreNextChange();
        Display.setActionTimeout();
        activateLightingPreset(
            LED_PRESET_OFF
        );
    } else if(buttonLeftA.wasReleased()) {
        Display.up();
    }
    if(buttonLeftB.pressedFor(LONG_PRESS_INTERVAL)) {
        buttonLeftB.ignorePress();
        buttonLeftB.ignoreNextChange();
        Display.setActionTimeout();
        toggleLightingPreset();
    } else if(buttonLeftB.wasReleased()) {
        Display.down();
    }
    if(buttonRightB.pressedFor(LONG_PRESS_INTERVAL)) {
        buttonRightB.ignorePress();
        buttonRightB.ignoreNextChange();

        Display.setActionTimeout();
        sleep();
    } else if(buttonRightB.wasReleased()) {
        Display.in();
    }
    if(buttonRightA.pressedFor(LONG_PRESS_INTERVAL)) {
        buttonRightA.ignorePress();
        buttonRightA.ignoreNextChange();

        Display.setActionTimeout();
        Display.toggleBacklight();
    } else if(buttonRightA.wasReleased()) {
        Display.out();
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

    CanMsg message;
    message.IDE = CAN_ID_STD;
    message.RTR = CAN_RTR_DATA;
    message.ID = CAN_CMD_MAIN_MC_SLEEP;
    message.DLC = 0;
    CanBus.send(&message);
    delay(100);
    CanBus.end();

    // Let's sleep the GPS
    gpsSleep();
    GPSUart.flush();
    GPSUart.sleep();
    // Disable Screen
    Display.sleep();
    // Float all GPIOs
    setGPIOModeToAllPins(GPIO_INPUT_FLOATING);
    // Disable the CAN Transceiver
    pinMode(CAN_RS, OUTPUT);
    digitalWrite(CAN_RS, HIGH);
    // Disable Bluetooth
    pinMode(BT_DISABLE_, OUTPUT);
    digitalWrite(BT_DISABLE_, LOW);
    // Wake for left A button
    pinMode(LEFT_A, INPUT_PULLUP);
    attachInterrupt(LEFT_A, nvic_sys_reset, FALLING);
    // Or when the microcontroller wake line rises
    pinMode(WAKE, INPUT_PULLDOWN);
    attachInterrupt(WAKE, nvic_sys_reset, RISING);
    // Disable screen backlight
    digitalWrite(BACKLIGHT_ON_, HIGH);
    pinMode(BACKLIGHT_ON_, OUTPUT);
    delay(500);
    systick_disable();
    adc_disable_all();
    disableAllPeripheralClocks();
    while(true) {
        iwdg_feed();
        sleepAndWakeUp(STOP, &Clock, 14);
    }
}
