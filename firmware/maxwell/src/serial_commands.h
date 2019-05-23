#pragma once

namespace console {
    void init();
    void unrecognized(const char *command);
    void prompt();
    void loop();

    void repeat();

    void uptime();
    void hello();
    void led();
    void bridgeUART();
    void printStatistics();
    void printTaskStatistics();

    void voltageMeasurement();
    void isChargingNow();
    void currentUsage();
    void getPowerIOState();
    void getPowerIOPinState();

    void getTripOdometer();
    void resetTripOdometer();

    void getTemperature();

    void toggleLightingPreset();

    void enableBacklight();
    void disableBacklight();
    void setContrast();
    void menuUp();
    void menuDown();
    void menuIn();
    void menuOut();

    void disableAuxPower();
    void enableAuxPower();

    void sleep();
    void bleCmd();
    void reset();

    void flash();

    void enableAutosleep();
    void disableAutosleep();
    void disableBluetooth();
    void enableBluetooth();
    void setBluetoothTimeoutSeconds();

    void enableDynamoPower();
    void disableDynamoPower();

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

    void getUartRegister();
    void setUartRegister();

    void logStatus();
    void logList();
    void logDelete();
    void logPrint();
    void logSearch();
    void sdErrorState();

    void setTime();
    void getTime();

    void sendStatusUpdate();

    void getGpsStats();
    void gpsSendCommand();
};
