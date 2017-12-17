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

    Serial.begin(230400, SERIAL_8E1);

    commands.addCommand("ping", hello);
    commands.addCommand("btcmd", bluetooth);
    commands.addCommand("uptime", uptime);
    commands.addCommand("flash", programmingMode);
    commands.addCommand("charging", isChargingNow);
    commands.addCommand("current", currentUsage);
    commands.addCommand("voltage", voltageMeasurement);
    commands.setDefaultHandler(unrecognized);

    Serial.println("[Maxwell 1.0]");
    commands.prompt();
}

void isChargingNow() {
    if(!digitalRead(I_BATTERY_CHARGING_)) {
        Serial.println("Yes");
    } else {
        Serial.println("No");
    }
}

void currentUsage() {
    Serial.println(getCurrentUsage());
}

void voltageMeasurement() {
    String source = String((char*)commands.next());

    if(source == "dynamo") {
        Serial.println(getVoltage(VOLTAGE_DYNAMO));
    } else if(source == "battery") {
        Serial.println(getVoltage(VOLTAGE_BATTERY));
    } else if(source == "sense") {
        Serial.println(getVoltage(VOLTAGE_SENSE));
    } else {
        Serial.println("Unknown source: " + source);
    }
}

void unrecognized(const char *command) {
    Serial.print("Unknown command: ");
    Serial.println(command);
}

void uptime() {
    Serial.println(millis());
}

void programmingMode() {
    Serial.println("Resetting device...");
    Serial.flush();
    delay(100);

    // Note that resetting while connected via Bluetooth will
    // cause the device to enter flash mode due to to the BT module's
    // 'connected device' line being connected to the BOOT0 net.
    nvic_sys_reset();
}

void hello() {
    char *arg;
    arg = commands.next();

    Serial.print("pong");
    if (arg != NULL) {
        Serial.print(' ');
        Serial.print(String(arg));
    }
    Serial.println();
}

void bluetooth() {

    String btcommand;

    char *arg;
    bool firstArg = true;
    while (true) {
        arg = commands.next();
        if(arg == NULL) {
            break;
        }

        if (!firstArg) {
            btcommand += " ";
        }
        firstArg = false;
        btcommand += String(arg);
    }
    Serial.flush();

    delay(100);
    digitalWrite(BT_KEY, HIGH);
    delay(100);
    Serial.println(btcommand);
    Serial.flush();
    delay(100);
    digitalWrite(BT_KEY, LOW);
    delay(100);

    uint32 started = millis();

    Serial.flush();
    while(millis() < started + 1000) {
        while(Serial.available() > 0) {
            Serial.print((char)Serial.read());
            Serial.flush();
        }
    }
    Serial.flush();
    delay(100);
}

void loop() {
    commands.readSerial();
}
