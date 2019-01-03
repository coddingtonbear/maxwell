#define VOLTAGE_DYNAMO 1
#define VOLTAGE_BATTERY 2
#define VOLTAGE_SENSE 3

#define SENSE_RESISTOR_VALUE 0.1

#define CHARGING_STATUS_CHARGING_NOW 1
#define CHARGING_STATUS_SHUTDOWN 3

#define MOVEMENT_WAKE_ENABLED false

#define ADC_ADDRESS B0101000
#define ADC_SAMPLES 10

namespace power {
    void init();
    double getVoltage(uint source);
    double getCurrentUsage();
    uint16_t getAdcValue(uint8_t pin);
    uint8_t getChargingStatus();

    double convertAdcToVoltage(uint32_t value, uint16_t r1, uint16_t r2);

    void updatePowerMeasurements();

    void sleep();
    void checkSleepTimeout();
    void enableAutosleep(bool);
    void refreshSleepTimeout();
};
