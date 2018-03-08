#define VOLTAGE_DYNAMO 1
#define VOLTAGE_BATTERY 2
#define VOLTAGE_SENSE 3

#define VOLTAGE_UPDATE_INTERVAL 100
#define VOLTAGE_SAMPLE_COUNT 100

#define SENSE_RESISTOR_VALUE 0.02

int getRawVoltageAdcValue(uint source);
double getVoltage(uint source);
double getInstantaneousVoltage(uint source);
double getCurrentUsage();
void enableBatteryCharging(bool);

void voltageLoop();
void updateVoltages();
