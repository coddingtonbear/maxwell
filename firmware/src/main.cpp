#include "main.h"

SerialCommand commands;

void setup() {
    pinMode(I_CAN_INT, INPUT);
    pinMode(CAN_CS, OUTPUT);

    pinMode(POWER_ON, OUTPUT);
    pinMode(ENABLE_AUX_DEVICES, OUTPUT);
    pinMode(ENABLE_BATT_CHARGE_, OUTPUT);
    digitalWrite(POWER_ON, HIGH);
    digitalWrite(ENABLE_AUX_DEVICES, HIGH);
    digitalWrite(ENABLE_BATT_CHARGE_, LOW);

    pinMode(I_BATTERY_CHARGING_, INPUT);
    pinMode(I_DYNAMO_VOLTAGE, INPUT_ANALOG);
    pinMode(I_BATTERY_VOLTAGE, INPUT_ANALOG);
    pinMode(I_CURRENT_SENSE, INPUT_ANALOG);

    pinMode(USB_ENABLE_, OUTPUT);
    pinMode(BUZZER, OUTPUT);
    pinMode(I_SPEED, INPUT);
    pinMode(NEOPIXEL, OUTPUT);
    pinMode(BT_KEY, OUTPUT);
    digitalWrite(USB_ENABLE_, LOW);
    digitalWrite(BT_KEY, LOW);

    Serial.begin(115200);

    commands.addCommand("ping", hello);
    commands.addCommand("btcmd", bluetooth);
    commands.addCommand("uptime", uptime);
    commands.addCommand("reset", reset);
    commands.setDefaultHandler(unrecognized);

    Serial.println("Ready");
}

void unrecognized(const char *command) {
    Serial.print("Unknown command: ");
    Serial.println(command);
}

void uptime() {
    Serial.println(millis());
}

void reset() {
    nvic_sys_reset();
}

void hello() {
    Serial.println("pong");
}

void bluetooth() {
    digitalWrite(BT_KEY, HIGH);
    delay(100);

    char *arg;
    bool firstArg = true;
    while (true) {
        arg = commands.next();
        if(arg == NULL) {
            break;
        }

        if (!firstArg) {
            Serial.print(' ');
        }
        firstArg = false;
        Serial.print(*arg);
    }
    Serial.print("\r\n");

    delay(1000);
    digitalWrite(BT_KEY, LOW);

    while(Serial.available() > 0) {
        Serial.print((char)Serial.read());
    }
}

void loop() {
    commands.readSerial();
}
