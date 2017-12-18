#include "main.h"

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

    pinMode(I_BATTERY_CHARGING_, INPUT_PULLUP);
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

    setupCommands();

    Serial.println("[Maxwell 1.0]");
    commandPrompt();

    canbus.reset();
    canbus.setBitrate(CAN_10KBPS);
    canbus.setNormalMode();

    ledSetup();

    // Lower the BOOT0 pin if we previously had it high
    //sendBluetoothCommand("AT+PIO=6,0");
}

String sendBluetoothCommand(String command) {
    String result;

    Serial.flush();

    delay(250);
    digitalWrite(BT_KEY, HIGH);
    delay(250);
    Serial.println(command);
    Serial.flush();
    delay(250);
    digitalWrite(BT_KEY, LOW);
    delay(250);

    uint32 started = millis();

    Serial.flush();
    while(millis() < started + 1000) {
        while(Serial.available() > 0) {
            result += (char)Serial.read();
        }
    }
    Serial.flush();
    delay(100);

    return result;
}

void loop() {
    ledCycle();
    commandLoop();

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
