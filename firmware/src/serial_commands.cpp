#include "main.h"
#include "serial_commands.h"


SerialCommand commands;


void setupCommands() {
    commands.addCommand("uptime", uptime);
    commands.addCommand("ping", hello);
    commands.addCommand("beep", beep);
    commands.addCommand("led", led);

    commands.addCommand("voltage", voltageMeasurement);
    commands.addCommand("charge", charge);
    commands.addCommand("is_charging", isChargingNow);
    commands.addCommand("current", currentUsage);
    commands.addCommand("aux", auxDevicesEnable);

    commands.addCommand("btcmd", bluetooth);
    commands.addCommand("reset", reset);
    commands.addCommand("flash", programmingMode);

    commands.setDefaultHandler(unrecognized);
}

void commandPrompt() {
    commands.prompt();
}

void commandLoop() {
    commands.readSerial();
}

void led() {
    char* subcommandBytes = commands.next();
    if(subcommandBytes == NULL) {
        Serial.println(
            "Subcommand required: cycle, color, interval"
        );
        return;
    }

    String subcommand = String(subcommandBytes);

    if(subcommand == "cycle") {
        char* cycleNameBytes = commands.next();
        if(cycleNameBytes == NULL) {
            Serial.println(
                "Valid cycles required: off, brightness, random, motion, blink"
            );
            return;
        }
        String cycleName = String(cycleNameBytes);

        if (cycleName == "off") {
            ledSetCycle(LED_CYCLE_OFF);
        } else if(cycleName == "random") {
            ledSetCycle(LED_CYCLE_RANDOM);
        } else if(cycleName == "motion") {
            ledSetCycle(LED_CYCLE_MOTION);
        } else if(cycleName == "blink") {
            ledSetCycle(LED_CYCLE_BLINK);
        }
    } else if (subcommand == "color") {
        char* redBytes = commands.next();
        char* greenBytes = commands.next();
        char* blueBytes = commands.next();
        if(redBytes == NULL || greenBytes == NULL || blueBytes == NULL) {
            Serial.println(
                "Required three 8-bit decimal colors in RGB order."
            );
            return;
        }
        ledSetColor(
            atoi(redBytes),
            atoi(greenBytes),
            atoi(blueBytes)
        );
    } else if (subcommand == "interval") {
        char* intervalBytes = commands.next();
        if(intervalBytes == NULL) {
            Serial.println(
                "Required interval in milliseconds"
            );
            return;
        }

        ledSetInterval(atoi(intervalBytes));
    } else if (subcommand == "brightness") {
        char* brightnessBytes = commands.next();
        if(brightnessBytes == NULL) {
            Serial.println(
                "Required 8-bit brightness value."
            );
            return;
        }

        ledSetMaxBrightness(atoi(brightnessBytes));
    }
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

    enableAuxDevices(enable);
    if(enable) {
        Serial.println("Auxiliary devices enabled.");
    } else {
        Serial.println("Auxiliary devices disabled.");
    }
}

void charge() {
    int enable = 1;
    char* state = commands.next();
    if(state != NULL) {
        enable = atoi(state);
    }

    enableBatteryCharging(enable);
    if(enable) {
        Serial.println("Battery charging enabled.");
    } else {
        Serial.println("Battery charging disabled.");
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

    sendBluetoothCommand("AT+PIO=6,1");
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

    String result = sendBluetoothCommand(btcommand);

    Serial.print(result);
}