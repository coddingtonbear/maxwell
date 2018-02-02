#include "serial_commands.h"

SerialCommand commands;

void setupCommands() {
    commands.setDefaultHandler(unrecognized);
    commands.addCommand("reset", reset);
    commands.addCommand("flash", flash);
    commands.addCommand("beep", beep);
}

void commandPrompt() {
    commands.prompt();
}

void commandLoop() {
    commands.readSerial();
}

void unrecognized(const char *command) {
    Serial.print("Unknown command: ");
    Serial.println(command);
}

void beep() {
    uint32 frequency = 554;
    uint32 duration = 500;
    byte* frequencyBytes = reinterpret_cast<byte*>(&frequency);
    byte* durationBytes = reinterpret_cast<byte*>(&duration);

    CanMsg message;
    message.IDE = CAN_ID_STD;
    message.RTR = CAN_RTR_DATA;
    message.ID = CAN_CMD_BEEP;
    message.DLC = sizeof(uint32) * 2;

    for(uint8 i = 0; i < sizeof(uint32); i++) {
        message.Data[i] = frequencyBytes[i];

        Serial.print(i);
        Serial.print(" -> ");
        Serial.println(frequencyBytes[i], HEX);
    }
    for(uint8 i = sizeof(uint32); i < (2* sizeof(uint32)); i++) {
        message.Data[i] = durationBytes[i - sizeof(uint32)];

        Serial.print(i);
        Serial.print(" -> ");
        Serial.println(durationBytes[i - sizeof(uint32)], HEX);
    }
    Serial.flush();

    sendCanMessage(&message);
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

void flash() {
    Serial.println("Resetting device...");
    Serial.flush();

    delay(100);

    // Note that resetting while connected via Bluetooth will
    // cause the device to enter flash mode due to to the BT module's
    // 'connected device' line being connected to the BOOT0 net.
    nvic_sys_reset();
}
