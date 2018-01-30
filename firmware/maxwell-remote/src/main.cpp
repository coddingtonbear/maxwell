#include "main.h"
#include <HardwareCAN.h>

Adafruit_SSD1306 display(-1);

void setup() {
    nvic_irq_disable(NVIC_USB_LP_CAN_RX0);	// Disable interrupts
    nvic_irq_disable(NVIC_CAN_RX1);
    nvic_irq_disable(NVIC_USB_HP_CAN_TX);

    delay(1000);

    pinMode(DISPLAY_ON, OUTPUT);
    digitalWrite(DISPLAY_ON, LOW);

    pinMode(BT_KEY, OUTPUT);
    digitalWrite(BT_KEY, LOW);

    pinMode(WAKE, OUTPUT);
    digitalWrite(WAKE, LOW);

    pinMode(BT_ENABLE_, OUTPUT);
    digitalWrite(BT_ENABLE_, LOW);

    HardwareCAN canBus = getCanbus();
    canBus.map(CAN_GPIO_PB8_PB9);
    canBus.begin(CAN_SPEED_1000, CAN_MODE_NORMAL);
    canBus.filter(0, 0, 0);
    canBus.set_poll_mode();

    Serial.begin(230400, SERIAL_8E1);

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

    Serial.println("[Maxwell Remote 1.0]");
    delay(1000);

    setupCommands();
    commandPrompt();
}

uint32 lastShown = 0;

void loop() {
    commandLoop();

    if (lastShown == 0 || (lastShown + 1000 < millis())) {
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println(String(millis()));
        lastShown = millis();
        display.display();
    }

    HardwareCAN canBus = getCanbus();
    if(canBus.available()) {
        CanMsg *can_message;
        if((can_message = canBus.recv()) != NULL) {
            display.setCursor(0, 20);
            display.println(String(can_message->ID, HEX));
            display.setCursor(0, 40);
            for(int i = 0; i < can_message->DLC; i++) {
                display.print(String(can_message->Data[i], HEX));
            }
            display.display();

            canBus.free();

            Serial.print("RECEIVED CAN MESSAGE: [");
            Serial.print(String(can_message->ID, HEX));
            Serial.print("]");
            for(int i = 0; i < can_message->DLC; i++) {
                Serial.print(String(can_message->Data[i], HEX));
            }
            Serial.println();
        }
    }
}
