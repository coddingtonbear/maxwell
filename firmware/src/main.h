#include <Arduino.h>
#include <SerialCommand.h>

// CAN
#define I_CAN_INT PA0
#define CAN_CS PA1

// Power Management
#define POWER_ON PB0
#define ENABLE_AUX_DEVICES PB9
#define ENABLE_BATT_CHARGE_ PB14
#define I_BATTERY_CHARGING_ PA3
#define I_DYNAMO_VOLTAGE PB1
#define I_BATTERY_VOLTAGE PC5
#define I_CURRENT_SENSE PC4

// USB Charging
#define USB_ENABLE_ PA2

// Sound
#define BUZZER PB6

// Bluetooth
#define BT_KEY PB7

// Speed
#define I_SPEED PB13

// Neopixels
#define NEOPIXEL PC8


void setup();
void loop();

void unrecognized(const char *command);
void uptime();
void reset();
void hello();
void bluetooth();
