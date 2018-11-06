#include <CANCommand.h>

//#define DEBUG_CAN_MESSAGES

#pragma once

namespace can {
    void init();
    void handle(CANCommand::CANMessage* command);

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

    void unrecognized(CANCommand::CANMessage*);
};

namespace console {
    void init();
    void unrecognized(const char *command);
    void prompt();
    void loop();

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
    void getLTELogStatus();
    void connectLTELogger();
    void disconnectLTELogger();

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
