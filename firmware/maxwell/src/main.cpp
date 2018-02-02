#include "main.h"

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

    MCP2515 canbus = getCanbus();
    canbus.begin();

    setupCommands();

    Serial.println("[Maxwell 1.0]");
    commandPrompt();

    struct can_frame reqSetWakeFrame;
    reqSetWakeFrame.can_id = CAN_MAIN_MC_WAKE;
    reqSetWakeFrame.can_dlc = 0;
    canbus.sendMessage(&reqSetWakeFrame);

    canbus.reset();
    canbus.setBitrate(CAN_1000KBPS);
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

    MCP2515 canbus = getCanbus();
    struct can_frame recvFrame;
    if(canbus.readMessage(&recvFrame) == MCP2515::ERROR_OK) {
        CANCommand::CANMessage command;
        command.ID = recvFrame.can_id;
        command.DLC = recvFrame.can_dlc;

        Serial.print("Received CAN Message: ");
        Serial.print(recvFrame.can_id, HEX);
        Serial.print(" (");
        Serial.print(recvFrame.can_dlc);
        Serial.print(")");

        for (uint8_t i = 0; i < recvFrame.can_dlc; i++) {
            Serial.print(recvFrame.data[i], HEX);
            Serial.print(" ");

            command.Data[i] = recvFrame.data[i];
        }
        Serial.println("");

        handleCANCommand(&command);
    }

    /*
    if(lastMessage == 0 || millis() > lastMessage + 1000) {
        Serial.println(millis());
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
            Serial.print("ERR: ");
            Serial.println(error, DEC);
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
            Serial.print("ERR: ");
            Serial.println(error, DEC);
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
            Serial.print("ERR: ");
            Serial.println(error, DEC);
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
            Serial.print("ERR: ");
            Serial.println(error, DEC);
        }
        delay(50);

        lastMessage = millis();
    }
    */
}
