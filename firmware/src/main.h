#include <Arduino.h>
#include <SerialCommand.h>

#include "power.h"

// CAN
#define I_CAN_INT PA0
#define CAN_CS PA1

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
void programmingMode();
void hello();
void bluetooth();
void voltageMeasurement();
void isChargingNow();
void currentUsage();
