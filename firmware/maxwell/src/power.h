#define VOLTAGE_DYNAMO 1
#define VOLTAGE_BATTERY 2
#define VOLTAGE_SENSE 3

#define VOLTAGE_SAMPLE_COUNT 100

#define SENSE_RESISTOR_VALUE 0.02

#define CHARGING_STATUS_CHARGING_NOW 1
#define CHARGING_STATUS_FULLY_CHARGED 2
#define CHARGING_STATUS_SHUTDOWN 3

int getRawVoltageAdcValue(uint source);
double getVoltage(uint source);
double getInstantaneousVoltage(uint source);
double getCurrentUsage();
uint8_t getChargingStatus();
void enableBatteryCharging(bool);

void updateVoltages();
