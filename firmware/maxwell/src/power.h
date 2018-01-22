#include <Arduino.h>

#define POWER_ON PB0
#define ENABLE_AUX_DEVICES PB9
#define ENABLE_BATT_CHARGE_ PB14
#define I_BATTERY_CHARGING_ PA3
#define I_DYNAMO_VOLTAGE PB1
#define I_BATTERY_VOLTAGE PC5
#define I_CURRENT_SENSE PC4

// USB Charging
#define USB_ENABLE_ PA2

#define VOLTAGE_DYNAMO 1
#define VOLTAGE_BATTERY 2
#define VOLTAGE_SENSE 3

#define SENSE_RESISTOR_VALUE 0.02

int getRawVoltageAdcValue(uint source);
double getVoltage(uint source);
double getCurrentUsage();
void enableBatteryCharging(bool);
void enableAuxDevices(bool);
