#pragma once

#include <Arduino.h>
#include <mcp2515.h>
#include <CANCommand.h>

#include "can_message_ids.h"
#include "power.h"
#include "neopixel.h"
#include "serial_commands.h"
#include "can.h"

// CAN
#define I_CAN_INT PA0
#define CAN_CS PA1

// Sound
#define BUZZER PB6

// Bluetooth
#define BT_KEY PB7

// Speed
#define I_SPEED PB13


void setup();
void loop();

String sendBluetoothCommand(String);
