#include "serial_commands.h"

SerialCommand commands(&Serial1);

void setupCommands() {
    commands.setDefaultHandler(unrecognized);
    commands.addCommand("reset", reset);
    commands.addCommand("flash", flash);
    commands.addCommand("beep", beep);
    commands.addCommand("wake", wake);
    commands.addCommand("unWake", wake);
    commands.addCommand("uptime", uptime);
}

void commandPrompt() {
    commands.prompt();
}

void commandLoop() {
    commands.readSerial();
}

void unrecognized(const char *command) {
    Serial1.print("Unknown command: ");
    Serial1.println(command);
}

void uptime() {
    Serial1.println(millis());
}

void wake() {
    pinMode(WAKE, OUTPUT);
    digitalWrite(WAKE, HIGH);
}

void unWake() {
    pinMode(WAKE, INPUT);
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

        Serial1.print(i);
        Serial1.print(" -> ");
        Serial1.println(frequencyBytes[i], HEX);
    }
    for(uint8 i = sizeof(uint32); i < (2* sizeof(uint32)); i++) {
        message.Data[i] = durationBytes[i - sizeof(uint32)];

        Serial1.print(i);
        Serial1.print(" -> ");
        Serial1.println(durationBytes[i - sizeof(uint32)], HEX);
    }
    Serial1.flush();

    sendCanMessage(&message);
}

void reset() {
    Serial1.println(
        "Disconnect within 5 seconds to prevent booting into Flash mode..."
    );
    Serial1.print("5...");
    Serial1.flush();
    delay(1000);
    Serial1.print("4...");
    Serial1.flush();
    delay(1000);
    Serial1.print("3...");
    Serial1.flush();
    delay(1000);
    Serial1.print("2...");
    Serial1.flush();
    delay(1000);
    Serial1.println("1...");
    Serial1.flush();
    delay(1000);
    Serial1.println("Resetting device...");
    Serial1.flush();

    nvic_sys_reset();
}

void flash() {
    Serial1.println("Resetting device...");
    Serial1.flush();

    delay(100);

    // Note that resetting while connected via Bluetooth will
    // cause the device to enter flash mode due to to the BT module's
    // 'connected device' line being connected to the BOOT0 net.
    nvic_sys_reset();
}
