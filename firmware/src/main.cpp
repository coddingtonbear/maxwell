#include "main.h"

SerialCommand commands;
MCP2515 canbus((const uint8_t)CAN_CS);

unsigned int lastMessage = 0;

void setup() {
    pinMode(I_CAN_INT, INPUT);
    pinMode(CAN_CS, OUTPUT);
    digitalWrite(CAN_CS, HIGH);

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
    canbus.begin();

    commands.addCommand("uptime", uptime);
    commands.addCommand("ping", hello);
    commands.addCommand("beep", beep);

    commands.addCommand("voltage", voltageMeasurement);
    commands.addCommand("charging", isChargingNow);
    commands.addCommand("current", currentUsage);
    commands.addCommand("aux", auxDevicesEnable);

    commands.addCommand("btcmd", bluetooth);
    commands.addCommand("reset", reset);
    commands.addCommand("flash", programmingMode);

    commands.setDefaultHandler(unrecognized);

    Serial.println("[Maxwell 1.0]");
    commands.prompt();

    canbus.reset();
    canbus.setBitrate(CAN_10KBPS);
    canbus.setNormalMode();
}

void reset() {
    Serial.println(
        "Disconnect within 5 seconds to prevent booting into Flash mode..."
    );
    Serial.print("5...");
    Serial.flush();
    delay(1000);
    Serial.print("4...");
    Serial.flush();
    delay(1000);
    Serial.print("3...");
    Serial.flush();
    delay(1000);
    Serial.print("2...");
    Serial.flush();
    delay(1000);
    Serial.println("1...");
    Serial.flush();
    delay(1000);
    Serial.println("Resetting device...");
    Serial.flush();

    nvic_sys_reset();
}

void beep() {
    int frequency = 554;
    int duration = 100;
    
    char* frequencyString = commands.next();
    if(frequencyString != NULL) {
        frequency = atoi(frequencyString);
    }
    char* durationString = commands.next();
    if(durationString != NULL) {
        duration = atoi(durationString);
    }

    tone(BUZZER, frequency, duration); 
}

void auxDevicesEnable(){
    int enable = 1;
    char* state = commands.next();
    if(state != NULL) {
        enable = atoi(state);
    }

    digitalWrite(ENABLE_AUX_DEVICES, enable);
    if(enable) {
        Serial.println("Auxiliary devices enabled.");
    } else {
        Serial.println("Auxiliary devices disabled.");
    }
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

    delay(250);
    digitalWrite(BT_KEY, HIGH);
    delay(250);
    Serial.println(btcommand);
    Serial.flush();
    delay(250);
    digitalWrite(BT_KEY, LOW);
    delay(250);

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

    if(lastMessage == 0 || millis() > lastMessage + 1000) {
        struct can_frame voltage_frame;
        MCP2515::ERROR error;
        double voltage;
        unsigned char *voltageBytes;

        voltage = getVoltage(VOLTAGE_BATTERY);
        voltageBytes = reinterpret_cast<unsigned char *>(&voltage);
        voltage_frame.can_id = CAN_VOLTAGE_BATTERY;
        voltage_frame.can_dlc = sizeof(double);
        strcpy((char*)voltageBytes, (char*)voltage_frame.data);
        error = canbus.sendMessage(&voltage_frame);

        voltage = getVoltage(VOLTAGE_DYNAMO);
        voltageBytes = reinterpret_cast<unsigned char *>(&voltage);
        voltage_frame.can_id = CAN_VOLTAGE_DYNAMO;
        voltage_frame.can_dlc = sizeof(double);
        strcpy((char*)voltageBytes, (char*)voltage_frame.data);
        error = canbus.sendMessage(&voltage_frame);

        voltage = getVoltage(VOLTAGE_SENSE);
        voltageBytes = reinterpret_cast<unsigned char *>(&voltage);
        voltage_frame.can_id = CAN_VOLTAGE_SENSE;
        voltage_frame.can_dlc = sizeof(double);
        strcpy((char*)voltageBytes, (char*)voltage_frame.data);
        error = canbus.sendMessage(&voltage_frame);

        lastMessage = millis();
    }
}
