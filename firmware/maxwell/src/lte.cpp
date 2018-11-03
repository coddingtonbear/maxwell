#include <Arduino.h>
#include <libmaple/iwdg.h>
#include <Adafruit_FONA.h>
#include <Regexp.h>
#include <Time.h>

#include "main.h"
#include "pin_map.h"
#include "lte.h"
#include "tasks.h"
#include "status.h"

Adafruit_FONA_LTE LTE = Adafruit_FONA_LTE();

bool lteEnabled = false;

enum lte_log_status {
    CONNECTED,
    DISCONNECTED,
    UNKNOWN
};
enum lte_state {
    LTE_STATE_NULL,
    LTE_STATE_OFF,
    LTE_STATE_PRESSED,
    LTE_STATE_RELEASED,
    LTE_STATE_ON,
};
lte_state lteTargetStatus = LTE_STATE_NULL;
lte_state nextLteTargetStatus = LTE_STATE_NULL;
long minNextLteStatusTransition = 0;
long maxNextLteStatusTransition = 0;

bool lte::asyncEnable(bool enabled) {
    // If we aren't complete with our current transition, drop out
    if(nextLteTargetStatus != LTE_STATE_NULL) {
        return false;
    }


    if(enabled) {
        // If already powered; skip pressing the power button
        lteTargetStatus = LTE_STATE_ON;
        if(lte::isPoweredOn()) {
            nextLteTargetStatus = LTE_STATE_ON;
        }
    } else {
        lteTargetStatus = LTE_STATE_OFF;
    }

    tasks::enableLTEStatusManager();

    return true;
}

void lte::asyncManagerLoop() {
    if(minNextLteStatusTransition > millis()) {
        #ifdef LTE_DEBUG
            Output.print("LTE Transition wait for ");
            Output.print(minNextLteStatusTransition - millis());
            Output.println(" ms");
        #endif
        return;
    }
    if(maxNextLteStatusTransition > 0 && millis() > maxNextLteStatusTransition) {
        #ifdef LTE_DEBUG
            Output.println("LTE Transition timeout for target ");
            Output.println(lteTargetStatus);
        #endif
        nextLteTargetStatus = LTE_STATE_NULL;
        lteTargetStatus = LTE_STATE_NULL;
        maxNextLteStatusTransition = 0;
        tasks::enableLTEStatusManager(false);
        return;
    }

    #ifdef LTE_DEBUG
        Output.print("Processing LTE Target: ");
        Output.println(lteTargetStatus);
    #endif

    if(lteTargetStatus == LTE_STATE_ON) {
        if(nextLteTargetStatus == LTE_STATE_NULL) {
            pressPowerKey();
            #ifdef LTE_DEBUG
                Output.print("Pressing LTE Power key");
            #endif
            minNextLteStatusTransition = millis() + 2500;
            nextLteTargetStatus = LTE_STATE_RELEASED;
        } else if (nextLteTargetStatus == LTE_STATE_RELEASED) {
            unpressPowerKey();
            #ifdef LTE_DEBUG
                Output.print("Unpressing LTE Power key");
            #endif
            maxNextLteStatusTransition = millis() + 30000;
            nextLteTargetStatus = LTE_STATE_ON;
        } else if (nextLteTargetStatus == LTE_STATE_ON) {
            #ifdef LTE_DEBUG
                Output.print("Checking LTE Power status...");
            #endif
            if(isPoweredOn()) {
                #ifdef LTE_DEBUG
                    Output.print("LTE powered on; enabling now...");
                #endif
                bool result = enable();
                if(!result) {
                    return;
                }
                lteTargetStatus = LTE_STATE_NULL;
                nextLteTargetStatus = LTE_STATE_NULL;
                tasks::enableLTEStatusManager(false);
                maxNextLteStatusTransition = 0;
            } else {
                #ifdef LTE_DEBUG
                    Output.print("LTE not yet powered on");
                #endif
            }
            #ifdef LTE_DEBUG
                Output.print("LTE enabled");
            #endif
        }
    } else if (lteTargetStatus == LTE_STATE_OFF) {
        enable(false);
        lteTargetStatus = LTE_STATE_NULL;
        nextLteTargetStatus = LTE_STATE_NULL;
        maxNextLteStatusTransition = 0;
        tasks::enableLTEStatusManager(false);
    }
}

bool lte::isPoweredOn() {
    return LTEUart.GPIOGetPinState(
        PIN_LTE_STATUS
    ) == 1;
}

void lte::pressPowerKey() {
    LTEUart.GPIOSetPinMode(PIN_LTE_PWRKEY, OUTPUT);
    LTEUart.GPIOSetPinState(PIN_LTE_PWRKEY, LOW);
}

void lte::unpressPowerKey() {
    LTEUart.GPIOSetPinMode(PIN_LTE_PWRKEY, INPUT);
}

void lte::togglePower() {
    pressPowerKey();
    iwdg_feed();
    delay(2500);
    iwdg_feed();
    unpressPowerKey();
}

bool lte::enable(bool _enable) {
    if(_enable) {
        if(!isPoweredOn()) {
            lte::togglePower();
        }

        LTE.setNetworkSettings(F("hologram"));
        // Disable Echo
        LTEUart.println("ATE0");
        delay(10);
        // Set baud to 9600
        LTEUart.println("AT+IPR=9600");
        delay(10);
        LTEUart.flush();
        LTEUart.begin(9600);
        LTE.begin(LTEUart);
        bool result = LTE.enableGPRS(true);
        if(!result) {
            LTE.enableGPRS(false);
            return false;
        }
        delay(10);
        lteEnabled = true;
        return true;
    } else {
        if(status::statusConnectionConnected()) {
            status::connectStatusConnection(false);
        }
        LTE.sendCommand("AT+CIPSHUT");
        LTE.sendCommand("AT+CPOWD=1");
        LTEUart.flush();
        LTEUart.begin(115200);
        lteEnabled = false;
        return true;
    }
}

bool lte::isEnabled() {
    return lteEnabled;
}

time_t lte::getTimestamp() {
    char reply[128];

    LTE.getReply("AT+CCLK?", reply);

    MatchState ms;
    ms.Target(reply);

    char result = ms.Match(
        "+CCLK: \"([%d]+)/([%d]+)/([%d]+),([%d]+):([%d]+):([%d]+)([\\+\\-])([%d]+)\""
    );
    if(!result) {
        return 0;
    }
    char year_str[3];
    char month_str[3];
    char day_str[3];
    char hour_str[3];
    char minute_str[3];
    char second_str[3];
    char zone_dir_str[2];
    char zone_str[3];

    ms.GetCapture(year_str, 0);
    ms.GetCapture(month_str, 1);
    ms.GetCapture(day_str, 2);
    ms.GetCapture(hour_str, 3);
    ms.GetCapture(minute_str, 4);
    ms.GetCapture(second_str, 5);
    ms.GetCapture(zone_dir_str, 6);
    ms.GetCapture(zone_str, 7);

    tmElements_t timeEts;
    timeEts.Hour = atoi(hour_str);
    timeEts.Minute = atoi(minute_str);
    timeEts.Second = atoi(second_str);
    timeEts.Day = atoi(day_str);
    timeEts.Month = atoi(month_str);
    timeEts.Year = (2000 + atoi(year_str)) - 1970;

    time_t composedTime = makeTime(timeEts);

    // I'm not at _all_ sure what this offset is for; it
    // doesn't seem to be useful for more than converting
    // to UTC, and the raw timestamp isn't local.
    int offset = atoi(zone_str);
    if(zone_dir_str[0] == '-') {
        offset = -1 * offset;
    }
    composedTime += (offset * 15 * 60);

    return composedTime;
}

bool lte::getLteConnectionStatus(char* buffer)  {
    char reply[128];

    uint8_t length = 0;
    length = LTE.getMultilineReply("AT+CIPSTATUS", reply, 100);

    MatchState ms;
    ms.Target(reply);

    char result = ms.Match(
        "STATE: (.*)\n"
    );
    if(!result) {
        return false;
    }
    ms.GetCapture(buffer, 0);

    return true;
}
