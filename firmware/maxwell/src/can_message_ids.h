#pragma once

// Status Messages
#define CAN_TEST 0x10

#define CAN_MAIN_MC_SLEEP 0x30
#define CAN_MAIN_MC_WAKE 0x31
#define CAN_MAIN_MC_FLASH_BEGIN 0x32

#define CAN_VOLTAGE_BATTERY 0x040  // double
#define CAN_VOLTAGE_DYNAMO 0x041  // double  (NOT USED)
#define CAN_VOLTAGE_SENSE 0x042  // double
#define CAN_VELOCITY 0x43  // double
#define CAN_AMPS_CURRENT 0x44  // double
#define CAN_CHARGING_STATUS 0x45  // byte
#define CAN_LED_STATUS 0x46  // CANLedStatus
#define CAN_LED_STATUS_COLOR 0x47  // CANLedStatusColor
#define CAN_CURRENT_TIMESTAMP 0x48 // time_t
#define CAN_STATUS_MAIN_MC 0x49  // CANStatusMainMC

// Commands
#define CAN_CMD_MAIN_MC_RESET 0xA0
#define CAN_CMD_MAIN_MC_FLASH 0xA1
#define CAN_CMD_REQ_SET_WAKE 0xA2
#define CAN_CMD_MAIN_MC_SLEEP 0xA4

#define CAN_CMD_BEEP 0xA9

#define CAN_CMD_CHARGE_ENABLE 0xAB  // byte

#define CAN_CMD_LED_CYCLE 0xB0  // byte (cycle ID)
#define CAN_CMD_LED_COLOR 0xB1  // CANLedStatusColor
#define CAN_CMD_LED_INTERVAL 0xB2  // uint32
#define CAN_CMD_LED_BRIGHTNESS 0xB3  // byte
#define CAN_CMD_LED_ENABLE 0xB5  // byte
#define CAN_CMD_LED_PRESET 0xB6  // byte
#define CAN_CMD_ESP_ENABLE 0xB4  // byte
#define CAN_CMD_BT_ENABLE 0xB8  // byte
#define CAN_CMD_AUTOSLEEP_ENABLE 0xB9 // byte

struct CANLedStatus {
    bool enabled:1;
    uint8_t cycle;
    uint8_t brightness;
    uint32_t interval;
};

struct CANLedStatusColor {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t red2;
    uint8_t green2;
    uint8_t blue2;
};

struct CANStatusMainMC {
    bool is_charging:1;

    bool lighting_enabled:1;
    bool charging_enabled:1;
    bool bt_enabled:1;
    bool ble_enabled:1;

    bool has_valid_time:1;
    bool logging_now:1;
};
