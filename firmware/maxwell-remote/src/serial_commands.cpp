#include <HardwareCAN.h>
#include <SerialCommand.h>
#include <STM32Sleep.h>
#include <libmaple/iwdg.h>

#include "serial_commands.h"
#include "can.h"
#include "can_message_ids.h"
#include "main.h"
#include "status.h"
#include "display.h"


SerialCommand commands(&Output);
CANCommand canCommands;

uint32_t bluetoothEnabledUntil = millis() + BT_TIMEOUT_START;
bool bluetoothEnabled = true;

bool ledEnabled;
uint8_t ledCycle;
uint8_t ledBrightness;
uint32_t ledInterval;
uint8_t ledRed;
uint8_t ledGreen;
uint8_t ledBlue;
uint8_t ledRed2;
uint8_t ledGreen2;
uint8_t ledBlue2;

void setupCommands() {
    commands.setDefaultHandler(unrecognized);
    commands.addCommand("reset", reset);
    commands.addCommand("flash", flash);
    commands.addCommand("beep", beep);
    commands.addCommand("wake", wake);
    commands.addCommand("unWake", wake);
    commands.addCommand("uptime", uptime);
    commands.addCommand("btcmd", bluetooth);
    commands.addCommand("disable_esp", disableEsp);
    commands.addCommand("enable_esp", enableEsp);

    commands.addCommand("enable_charging", enableBatteryCharging);
    commands.addCommand("disable_charging", disableBatteryCharging);

    commands.addCommand("menu_up", menuUp);
    commands.addCommand("menu_down", menuDown);
    commands.addCommand("menu_in", menuIn);
    commands.addCommand("menu_out", menuOut);
    commands.addCommand("menu_debug", menuDebug);

    canCommands.addCommand(CAN_MAIN_MC_SLEEP, sleep);
    canCommands.addCommand(CAN_MAIN_MC_WAKE, receiveMainMcStatus);
    canCommands.addCommand(CAN_MAIN_MC_FLASH_BEGIN, receiveMainMcStatus);

    canCommands.addCommand(CAN_LED_STATUS, receiveLedStatus);
    canCommands.addCommand(CAN_LED_STATUS_COLOR, receiveLedStatusColor);

    canCommands.addCommand(CAN_VELOCITY, receiveCanDouble);
    canCommands.addCommand(CAN_VOLTAGE_BATTERY, receiveCanDouble);
    canCommands.addCommand(CAN_AMPS_CURRENT, receiveCanDouble);
    canCommands.addCommand(CAN_CHARGING_STATUS, receiveCanChargingStatus);
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

    Output.print(result);
}

void refreshLocalBluetoothTimeout() {
    bluetoothEnabledUntil = millis() + BT_TIMEOUT_ACTIVITY;
}

void handleLocalBluetoothTimeout() {
    if(bluetoothEnabled && bluetoothEnabledUntil < millis()) {
        disableLocalBluetooth();
    }
}

void enableLocalBluetooth() {
    enableLocalBluetoothUntil(
        millis() + BT_TIMEOUT_ACTIVITY
    );
}

void enableLocalBluetoothUntil(uint32_t until) {
    pinMode(BT_ENABLE_, OUTPUT);
    digitalWrite(BT_ENABLE_, LOW);

    bluetoothEnabledUntil = until;

    bluetoothEnabled = true;
}

void disableLocalBluetooth() {
    pinMode(BT_ENABLE_, OUTPUT);
    digitalWrite(BT_ENABLE_, HIGH);

    bluetoothEnabled = false;
}

void activateLightingPreset(uint8_t presetId) {
    CanMsg message;
    message.IDE = CAN_ID_STD;
    message.RTR = CAN_RTR_DATA;
    message.ID = CAN_CMD_LED_PRESET;
    message.DLC = sizeof(uint8_t);

    unsigned char *presetIdBytes = reinterpret_cast<byte*>(&presetId);
    for(uint8 i = 0; i < sizeof(uint8_t); i++) {
        message.Data[i] = presetIdBytes[i];
    }
    CanBus.send(&message);

    delay(50);
}

void setLightingBrightness(uint8_t brightness) {
    CanMsg message;
    message.IDE = CAN_ID_STD;
    message.RTR = CAN_RTR_DATA;
    message.ID = CAN_CMD_LED_BRIGHTNESS;
    message.DLC = sizeof(uint8_t);

    unsigned char *brightnessBytes = reinterpret_cast<byte*>(&brightness);
    for(uint8 i = 0; i < sizeof(uint8_t); i++) {
        message.Data[i] = brightnessBytes[i];
    }
    CanBus.send(&message);

    delay(50);
}

void setLightingCycle(uint8_t cycleId) {
    CanMsg message;
    message.IDE = CAN_ID_STD;
    message.RTR = CAN_RTR_DATA;
    message.ID = CAN_CMD_LED_CYCLE;
    message.DLC = sizeof(uint8_t);

    unsigned char *cycleIdBytes = reinterpret_cast<byte*>(&cycleId);
    for(uint8 i = 0; i < sizeof(uint8_t); i++) {
        message.Data[i] = cycleIdBytes[i];
    }
    CanBus.send(&message);

    delay(50);
}

void enableLighting() {
    CanMsg message;
    message.IDE = CAN_ID_STD;
    message.RTR = CAN_RTR_DATA;
    message.ID = CAN_CMD_LED_ENABLE;
    message.DLC = sizeof(uint8_t);

    uint8_t enabled = 1;
    unsigned char *enabledBytes = reinterpret_cast<byte*>(&enabled);
    for(uint8 i = 0; i < sizeof(uint8_t); i++) {
        message.Data[i] = enabledBytes[i];
    }
    CanBus.send(&message);

    delay(50);
}

void disableLighting() {
    CanMsg message;
    message.IDE = CAN_ID_STD;
    message.RTR = CAN_RTR_DATA;
    message.ID = CAN_CMD_LED_ENABLE;
    message.DLC = sizeof(uint8_t);

    uint8_t enabled = 0;
    unsigned char *enabledBytes = reinterpret_cast<byte*>(&enabled);
    for(uint8 i = 0; i < sizeof(uint8_t); i++) {
        message.Data[i] = enabledBytes[i];
    }
    CanBus.send(&message);

    delay(50);
}

String sendBluetoothCommand(String command) {
    String result;

    Output.flush();

    delay(250);
    digitalWrite(BT_KEY, HIGH);
    delay(250);
    Output.println(command);
    Output.flush();
    delay(250);
    digitalWrite(BT_KEY, LOW);
    delay(250);

    uint32 started = millis();

    Output.flush();
    while(millis() < started + 1000) {
        while(Output.available() > 0) {
            result += (char)Output.read();
        }
    }
    Output.flush();
    delay(100);

    return result;
}

void handleCANCommand(CANCommand::CANMessage* command) {
    canCommands.processCANMessage(command);
}

void commandPrompt() {
    commands.prompt();
}

void commandLoop() {
    commands.readSerial();
}

void unrecognized(const char *command) {
    Output.print("Unknown command: ");
    Output.println(command);
}

void uptime() {
    Output.println(millis());
}

void wake() {
    pinMode(WAKE, OUTPUT);
    digitalWrite(WAKE, HIGH);
    delay(1000);
    pinMode(WAKE, INPUT);
}

void sleep() {
    CanMsg message;
    message.IDE = CAN_ID_STD;
    message.RTR = CAN_RTR_DATA;
    message.ID = CAN_CMD_MAIN_MC_SLEEP;
    message.DLC = 0;
    CanBus.send(&message);

    digitalWrite(BT_ENABLE_, HIGH);
    digitalWrite(DISPLAY_ON_, HIGH);
    attachInterrupt(LEFT_A, nvic_sys_reset, FALLING);
    delay(500);
    systick_disable();
    disableAllPeripheralClocks();
    while(true) {
        iwdg_feed();
        sleepAndWakeUp(STOP, &Clock, 14);
    }
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
    }
    for(uint8 i = sizeof(uint32); i < (2* sizeof(uint32)); i++) {
        message.Data[i] = durationBytes[i - sizeof(uint32)];
    }
    Output.flush();

    CanBus.send(&message);

    delay(50);
}

void reset() {
    Output.println(
        "Disconnect within 5 seconds to prevent booting into Flash mode..."
    );
    Output.print("5...");
    Output.flush();
    delay(1000);
    Output.print("4...");
    Output.flush();
    delay(1000);
    Output.print("3...");
    Output.flush();
    delay(1000);
    Output.print("2...");
    Output.flush();
    delay(1000);
    Output.println("1...");
    Output.flush();
    delay(1000);
    Output.println("Resetting device...");
    Output.flush();

    nvic_sys_reset();
}

void flash() {
    Output.println("Resetting device...");
    Output.flush();

    delay(100);

    // Note that resetting while connected via Bluetooth will
    // cause the device to enter flash mode due to to the BT module's
    // 'connected device' line being connected to the BOOT0 net.
    nvic_sys_reset();
}

void receiveCanDouble() {
    static uint8_t data[8];
    canCommands.getData(data);
    uint32 msgId = canCommands.message->ID;

    double value = *(reinterpret_cast<double*>(data));

    setStatusParameter(msgId, value);
}

void receiveCanChargingStatus() {
    static uint8_t data[8];
    canCommands.getData(data);

    setChargingStatus(data[0]);
}

void setLedColor(int32 _red, int32 _green, int32 _blue, bool primary) {
    uint8_t baseRed;
    uint8_t baseGreen;
    uint8_t baseBlue;
    uint8_t cmd;

    if (primary) {
        baseRed = ledRed;
        baseGreen = ledGreen;
        baseBlue = ledBlue;

        cmd = CAN_CMD_LED_COLOR;
    } else {
        baseRed = ledRed2;
        baseGreen = ledGreen2;
        baseBlue = ledBlue2;

        cmd = CAN_CMD_LED_COLOR2;
    }

    if(_red >= 0) {
        baseRed = _red;
    }
    if(_green >= 0) {
        baseGreen = _green;
    }
    if(_blue >= 0) {
        baseBlue = _blue;
    }

    CanMsg message;
    message.IDE = CAN_ID_STD;
    message.RTR = CAN_RTR_DATA;
    message.ID = cmd;
    message.DLC = sizeof(byte) * 3;
    message.Data[0] = baseRed;
    message.Data[1] = baseGreen;
    message.Data[2] = baseBlue;

    CanBus.send(&message);
}

void receiveLedStatus() {
    static uint8_t data[8];
    canCommands.getData(data);

    ledEnabled = data[0];
    ledCycle = data[1];
    ledBrightness = data[2];
    ledInterval = *(reinterpret_cast<uint32*>(&data[3]));
}

void receiveLedStatusColor() {
    static uint8_t data[8];
    canCommands.getData(data);

    ledRed = data[0];
    ledGreen = data[1];
    ledBlue = data[2];
    ledRed2 = data[3];
    ledGreen2 = data[4];
    ledBlue2 = data[5];
}

void receiveMainMcStatus() {
    setStatusMainMc(canCommands.message->ID);
}

void disableEsp() {
    CanMsg message;
    message.IDE = CAN_ID_STD;
    message.RTR = CAN_RTR_DATA;
    message.ID = CAN_CMD_ESP_ENABLE;
    message.DLC = sizeof(uint8_t);

    uint8_t enabled = 0;
    unsigned char *enabledBytes = reinterpret_cast<byte*>(&enabled);
    for(uint8 i = 0; i < sizeof(uint8_t); i++) {
        message.Data[i] = enabledBytes[i];
    }

    CanBus.send(&message);
}

void enableEsp() {
    CanMsg message;
    message.IDE = CAN_ID_STD;
    message.RTR = CAN_RTR_DATA;
    message.ID = CAN_CMD_ESP_ENABLE;
    message.DLC = sizeof(uint8_t);

    uint8_t enabled = 1;
    unsigned char *enabledBytes = reinterpret_cast<byte*>(&enabled);
    for(uint8 i = 0; i < sizeof(uint8_t); i++) {
        message.Data[i] = enabledBytes[i];
    }

    CanBus.send(&message);
}

void menuUp() {
    Display.up();
}

void menuDown() {
    Display.down();
}

void menuIn() {
    Display.in();
}

void menuOut() {
    Display.out();
}

void menuDebug() {
    MenuList* curr = Display.getCurrentMenu();

    Output.print("Position: ROOT");
    for(uint8_t i = 0; i <= Display.menuDepth; i++) {
        Output.print(".");
        Output.print(Display.menuPosition[i]);
    }
    Output.println();

    for(uint8_t i = 0; i < curr->items.size(); i++) {
        Output.print(i);
        Output.print(") ");
        Output.print(curr->items[i].name);
        Output.print(": ");
        if(curr->items[i].function != NULL) {
            Output.print("Function");
        } else if(curr->items[i].subMenu != NULL) {
            Output.print("Submenu");
        }
        Output.println();
    }
}

void enableBatteryCharging() {
    CanMsg message;
    message.IDE = CAN_ID_STD;
    message.RTR = CAN_RTR_DATA;
    message.ID = CAN_CMD_CHARGE_ENABLE;
    message.DLC = sizeof(uint8_t);

    uint8_t enabled = 1;
    unsigned char *enabledBytes = reinterpret_cast<byte*>(&enabled);
    for(uint8 i = 0; i < sizeof(uint8_t); i++) {
        message.Data[i] = enabledBytes[i];
    }

    CanBus.send(&message);
}

void disableBatteryCharging() {
    CanMsg message;
    message.IDE = CAN_ID_STD;
    message.RTR = CAN_RTR_DATA;
    message.ID = CAN_CMD_CHARGE_ENABLE;
    message.DLC = sizeof(uint8_t);

    uint8_t enabled = 0;
    unsigned char *enabledBytes = reinterpret_cast<byte*>(&enabled);
    for(uint8 i = 0; i < sizeof(uint8_t); i++) {
        message.Data[i] = enabledBytes[i];
    }

    CanBus.send(&message);
}

void enableBluetooth() {
    CanMsg message;
    message.IDE = CAN_ID_STD;
    message.RTR = CAN_RTR_DATA;
    message.ID = CAN_CMD_BT_ENABLE;
    message.DLC = sizeof(uint8_t);

    uint8_t enabled = 1;
    unsigned char *enabledBytes = reinterpret_cast<byte*>(&enabled);
    for(uint8 i = 0; i < sizeof(uint8_t); i++) {
        message.Data[i] = enabledBytes[i];
    }

    CanBus.send(&message);
}

void disableBluetooth() {
    CanMsg message;
    message.IDE = CAN_ID_STD;
    message.RTR = CAN_RTR_DATA;
    message.ID = CAN_CMD_BT_ENABLE;
    message.DLC = sizeof(uint8_t);

    uint8_t enabled = 1;
    unsigned char *enabledBytes = reinterpret_cast<byte*>(&enabled);
    for(uint8 i = 0; i < sizeof(uint8_t); i++) {
        message.Data[i] = enabledBytes[i];
    }

    CanBus.send(&message);
}
