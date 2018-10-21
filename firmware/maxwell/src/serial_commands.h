#pragma once

void setupCommands();
void commandPrompt();
void commandLoop();
void handleCANCommand(CANCommand::CANMessage* command);

namespace can {
    void init();

    void sleep();
    void reset();

    void flash();
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

void canBeep();
void canSetLedCycle();
void canSetLedColor();
void canSetLedColor2();
void canSetLedBrightness();
void canSetLedInterval();
void canLedEnable();
void canLedPreset();
void canEnableBluetooth();
void canChargeEnable();
void setLedInterval();
void getGpsCoordinates();
void doSendCanMesage();
void canAutosleepEnable();
void canReceivePosition();
