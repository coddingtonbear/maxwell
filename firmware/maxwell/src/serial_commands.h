#pragma once

void setupCommands();
void commandPrompt();
void commandLoop();
void handleCANCommand(CANCommand::CANMessage* command);

namespace can {
    void init();

    void beep();

    void setLedCycle();
    void setLedColor();
    void setLedBrightness();
    void setLedInterval();
    void ledEnable();
    void ledPreset();

    void reset();
    void sleep();
    void chargeEnable();

    void flash();
    void autosleepEnable();

    void receivePosition();

    void enableBluetooth();
};

namespace console {
    void init();
    void unrecognized(const char *command);

    void uptime();
    void hello();
    void beep();
    void led();
    void bridgeUART();
    void printStatistics();

    void voltageMeasurement();
    void charge();
    void isChargingNow();
    void currentUsage();

    void sleep();
    void bleCmd();
    void reset();

    void flash();
    void enableAutosleep();
    void disableAutosleep();
    void disableBluetooth();
    void enableBluetooth();
    void setBluetoothTimeoutSeconds();

    void enableLTE();
    void disableLTE();
    void getLTEStatus();
    void getLTERSSI();
    void lteCommand();
    void sendTextMessage();
    void showLTETimestamp();

    void sendCan();
    void emitCan();

    void getUartRegister();
    void setUartRegister();

    void logStatus();
    void logList();
    void logDelete();
    void logDeleteAll();
    void logPrint();
    void logSearch();
    void sdErrorState();

    void setTime();
    void getTime();

    void sendStatusUpdate();
};
