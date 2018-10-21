#include <TimerFreeTone.h>
#include <libmaple/iwdg.h>

#include "util.h"
#include "pin_map.h"
#include "main.h"
#include "lte.h"


void util::beep(uint32_t frequency, uint32_t duration) {
    TimerFreeTone(PIN_BUZZER, frequency, duration);
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

bool util::syncTimestampWithLTE() {
    if(!lte::isEnabled()){
        return false;
    }
    time_t lteTimestamp = lte::getTimestamp();

    if(lteTimestamp < 1) {
        return false;
    }

    // Now convert to my timezone
    lteTimestamp += (TIMEZONE_OFFSET_MINUTES * 60);

    Clock.setTime(lteTimestamp);
    return true;
}
