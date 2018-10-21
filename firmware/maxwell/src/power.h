#define VOLTAGE_BATTERY 2
#define VOLTAGE_SENSE 3

#define POWER_CHANNEL_COUNT 1
#define POWER_SAMPLE_COUNT 1024
#define POWER_SAMPLE_RATE ADC_SMPR_71_5

#define SENSE_RESISTOR_VALUE 0.1

#define CHARGING_STATUS_CHARGING_NOW 1
#define CHARGING_STATUS_FULLY_CHARGED 2
#define CHARGING_STATUS_SHUTDOWN 3

#define MOVEMENT_WAKE_ENABLED false

namespace power {
    void initADCs();
    int getRawVoltageAdcValue(uint source);
    double getVoltage(uint source);
    double getCurrentUsage();
    uint8_t getChargingStatus();
    bool batteryChargingIsEnabled();
    void enableBatteryCharging(bool);
    double convertAdcToVoltage(uint32_t value);

    void updatePowerMeasurements();
    uint32 calc_adc_SQR3(uint8*);
    uint8 dma_transfer_finished();
    void adc_to_ready();
    void set_dma();

    void sleep();
    void checkSleepTimeout();
    void enableAutosleep(bool);
    void refreshSleepTimeout();
};
