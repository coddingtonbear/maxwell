#include "main.h"
#include <HardwareCAN.h>

Adafruit_SSD1306 display(-1);

void setup() {
    // Disable JTAG port; we're using JNRST for
    // display control.
    afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY);

    pinMode(DISPLAY_ON_, OUTPUT);
    digitalWrite(DISPLAY_ON_, LOW);

    Serial1.begin(230400, SERIAL_8E1);

    delay(1000);

    Serial1.println("[Maxwell Remote 1.0]");

    pinMode(BT_KEY, OUTPUT);
    digitalWrite(BT_KEY, LOW);
    pinMode(BT_ENABLE_, OUTPUT);
    digitalWrite(BT_ENABLE_, LOW);

    pinMode(RIGHT_A, INPUT_PULLUP);
    pinMode(RIGHT_B, INPUT_PULLUP);
    pinMode(LEFT_A, INPUT_PULLUP);
    pinMode(LEFT_B, INPUT_PULLUP);
    //attachInterrupt(RIGHT_A, handleControl, CHANGE);
    //attachInterrupt(RIGHT_B, handleControl, CHANGE);
    //attachInterrupt(LEFT_A, handleControl, CHANGE);
    //attachInterrupt(LEFT_B, handleControl, CHANGE);

    Wire.setClock(400000);
    Wire.begin();

    display.begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADDRESS);
    display.clearDisplay();
    display.display();

    display.setTextSize(1);
    display.setCursor(0, 0);
    display.setTextColor(WHITE);
    display.setTextWrap(true);
    display.println("[Maxwell Remote 1.0]");
    display.display();

    HardwareCAN& canBus = getCanbus();
    canBus.map(CAN_GPIO_PB8_PB9);
    canBus.begin(CAN_SPEED_1000, CAN_MODE_NORMAL);
    canBus.filter(0, 0, 0);
    canBus.set_poll_mode();

    setupCommands();

    //beep();

    commandPrompt();
}

uint8_t pinChanged = 0;
uint32 lastShown = 0;

void handleControl() {
    pinChanged = 1;
}

void loop() {
    HardwareCAN& canBus = getCanbus();
    commandLoop();

    if (lastShown == 0 || (lastShown + 1000 < millis())) {
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println(String(millis()));
        lastShown = millis();
        display.display();
        //Serial1.println(millis());
    }

    if (pinChanged != 0) {
        pinChanged = 0;

        Serial1.println("Control event occurred.");
    }

    if(canBus.available()) {
        CanMsg *can_message;
        if((can_message = canBus.recv()) != NULL) {
            /*
            display.setCursor(0, 20);
            display.println(String(can_message->ID, HEX));
            display.setCursor(0, 40);
            for(int i = 0; i < can_message->DLC; i++) {
                display.print(String(can_message->Data[i], HEX));
            }
            display.display();
            */

            Serial1.print("RECEIVED CAN MESSAGE: [");
            Serial1.flush();
            Serial1.print(String(can_message->ID, HEX));
            Serial1.print("]");
            for(int i = 0; i < can_message->DLC; i++) {
                Serial1.print(String(can_message->Data[i], HEX));
            }
            Serial1.println();

            canBus.free();

            beep();
        }
    }
}
