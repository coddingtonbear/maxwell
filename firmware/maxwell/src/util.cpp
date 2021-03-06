#include <Arduino.h>
#undef min
#undef max
#include <libmaple/iwdg.h>
#include <MCP79412RTC.h>

#include "util.h"
#include "pin_map.h"
#include "main.h"
#include "lte.h"


void util::safeDelay(uint32_t delaySeconds) {
    uint32_t until = millis() + delaySeconds;
    while(millis() < until) {
        iwdg_feed();
        delay(100);
    }
}

void util::debug(String message) {
    #ifdef DEBUG_VIA_UART
        UART4.print(millis());
        UART4.print(": ");
        UART4.println(message);
        UART4.flush();
        delay(50);
    #endif
}

void util::bridgeUART(HardwareSerial* bridged, uint32_t baud) {
    bridged->begin(baud);

    while(true) {
        iwdg_feed();
        if (Output.available()) {
            uint8_t value = Output.read();

            if (value == 4) {
                break;
            }
            bridged->write(value);
        }
        if (bridged->available()) {
            Output.write(bridged->read());
        }
    }

    Output.begin();
}

void util::bridgeUART(SC16IS750* bridged) {
    while(true) {
        iwdg_feed();
        if (Output.available()) {
            uint8_t value = Output.read();

            if (value == 4) {
                break;
            }
            bridged->write(value);
        }
        if (bridged->available()) {
            Output.write(bridged->read());
        }
    }

    Output.begin();
}

HardwareSerial* util::uartNumberToInterface(uint32_t uartNumber) {
    HardwareSerial* uart;
    if(uartNumber == 1) {
        uart = &BTSerial;
    } else if (uartNumber == 2) {
        uart = &UART2;
    } else if (uartNumber == 3) {
        uart = &UART3;
    } else if (uartNumber == 4) {
        uart = &UART4;
    } else if (uartNumber == 5) {
        uart = &UART5;
    }

    return uart;
}
