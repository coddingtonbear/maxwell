#pragma once

#include <PCA9536.h>

#define PIN_BT_DISABLE_ PC7
#define PIN_BT_KEY PC6

#define PIN_SPI_CS_A PA2
#define PIN_SPI_CS_B PA1

#define PIN_NEOPIXEL PA7
#define PIN_ENABLE_NEOPIXEL PC4
#define PIN_ENABLE_AUX PB10

#define DISPLAY_BACKLIGHT_ON_ PB1
#define DISPLAY_CS PA0
#define DISPLAY_DC PC5
#define DISPLAY_RST PB0

#define PIN_POWER_ON PB3

#define BUTTON_LEFT_A PC13
#define BUTTON_LEFT_B PC14
#define BUTTON_RIGHT_A PC15
#define BUTTON_RIGHT_B PC3

// EXTERNAL: LTE Module
#define PIN_LTE_DTR 7
#define PIN_LTE_STATUS 6
#define PIN_LTE_OE 5
#define PIN_LTE_PWRKEY 4

// EXTERNAL: Power/ADC
#define PIN_ADC_BATT_VOLTAGE 1
#define PIN_ADC_DYNAMO_VOLTAGE 2

// EXTERNAL: Power/IO
#define PIN_RECTIFIER_RELAY_A IO0
#define PIN_RECTIFIER_RELAY_B IO1
#define PIN_PWR_I_BATT_CHARGING IO2

#define BTSerial Serial
#define UART2 Serial1
#define UART3 Serial2
#define UART4 Serial3
#define UART5 Serial4

#define I2C_SCL PB6
#define I2C_SDA PB7
