// Status Messages
#define CAN_TEST 0x10

#define CAN_MC_MILLIS 0x30
#define CAN_MAIN_MC_WAKE 0x31

#define CAN_VOLTAGE_BATTERY 0x040
#define CAN_VOLTAGE_DYNAMO 0x041
#define CAN_VOLTAGE_SENSE 0x042

// Commands
#define CAN_CMD_MAIN_MC_RESET 0xA0
#define CAN_CMD_MAIN_MC_FLASH 0xA1
#define CAN_CMD_REQ_SET_WAKE 0xA2
#define CAN_CMD_BEEP 0xA3
#define CAN_CMD_LED_CYCLE 0xB0
#define CAN_CMD_LED_COLOR 0xB1
#define CAN_CMD_LED_INTERVAL 0xB2
#define CAN_CMD_LED_BRIGHTNESS 0xB3

// Command Arguments
// * CAN_CMD_LED_CYCLE
#define CAN_CMD_LED_CYCLE_OFF 1
#define CAN_CMD_LED_CYCLE_RANDOM 2
#define CAN_CMD_LED_CYCLE_MOTION 3
#define CAN_CMD_LED_CYCLE_BLINK 4
