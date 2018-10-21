#pragma once

void setupCommands();
void commandPrompt();
void commandLoop();
void handleCANCommand(CANCommand::CANMessage* command);

namespace can {
    void init();

    void sleep();
    void reset();
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
};

void flash();
void canBeep();
void canSetLedCycle();
void canSetLedColor();
void canSetLedColor2();
void canSetLedBrightness();
void canSetLedInterval();
void canLedEnable();
void canLedPreset();
void canChargeEnable();
void setLedInterval();
void send_can();
void emit_can();
void getGpsCoordinates();
void doSendCanMesage();
void canEnableBluetooth();
void cmdDisableAutosleep();
void cmdEnableAutosleep();
void canAutosleepEnable();
void setBluetoothTimeoutSeconds();
void logStatus();
void logList();
void logPrint();
void logDelete();
void logDeleteAll();
void logSearch();
void cmdDisableBluetooth();
void cmdEnableBluetooth();
void sdErrorState();
void setTime();
void getTime();
void getUartRegister();
void setUartRegister();
void getLTEStatus();
void getLTERSSI();
void lteCommand();
void sendTextMessage();
void showLTETimestamp();
void canReceivePosition();
void cmdSendStatusUpdate();
