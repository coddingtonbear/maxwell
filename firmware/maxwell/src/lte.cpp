#include <Arduino.h>
#include <libmaple/iwdg.h>
#include <Adafruit_FONA.h>
#include <Regexp.h>
#include <Time.h>

#include "main.h"
#include "pin_map.h"
#include "lte.h"

Adafruit_FONA_LTE LTE = Adafruit_FONA_LTE();

bool lteEnabled = false;

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

bool asyncEnableLte(bool enabled) {
    // If we aren't complete with our current transition, drop out
    if(nextLteTargetStatus != LTE_STATE_NULL) {
        return false;
    }

    // If we're already enabled, we don't need to do anything at all
    if(enabled && lteIsPoweredOn()) {
        return true;
    } else if ((!enabled) && (!lteIsPoweredOn())) {
        return true;
    }

    lteTargetStatus = enabled ? LTE_STATE_ON : LTE_STATE_OFF;

    return true;
}

void asyncLteManager() {
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
        return;
    }

    #ifdef LTE_DEBUG
        Output.print("Processing LTE Target: ");
        Output.println(lteTargetStatus);
    #endif

    if(lteTargetStatus == LTE_STATE_ON) {
        if(nextLteTargetStatus == LTE_STATE_NULL) {
            pressLTEPowerKey();
            #ifdef LTE_DEBUG
                Output.print("Pressing LTE Power key");
            #endif
            minNextLteStatusTransition = millis() + 2500;
            nextLteTargetStatus = LTE_STATE_RELEASED;
        } else if (nextLteTargetStatus == LTE_STATE_RELEASED) {
            unpressLTEPowerKey();
            #ifdef LTE_DEBUG
                Output.print("Unpressing LTE Power key");
            #endif
            maxNextLteStatusTransition = millis() + 5000;
            nextLteTargetStatus = LTE_STATE_ON;
        } else if (nextLteTargetStatus == LTE_STATE_ON) {
            #ifdef LTE_DEBUG
                Output.print("Checking LTE Power status...");
            #endif
            if(lteIsPoweredOn()) {
                #ifdef LTE_DEBUG
                    Output.print("LTE powered on; enabling now...");
                #endif
                enableLTE();
                lteTargetStatus = LTE_STATE_NULL;
                nextLteTargetStatus = LTE_STATE_NULL;
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
        disableLTE();
        lteTargetStatus = LTE_STATE_NULL;
        nextLteTargetStatus = LTE_STATE_NULL;
        maxNextLteStatusTransition = 0;
    }
}

bool lteIsPoweredOn() {
    return LTEUart.GPIOGetPinState(
        PIN_LTE_STATUS
    ) == 1;
}

void pressLTEPowerKey() {
    LTEUart.GPIOSetPinMode(PIN_LTE_PWRKEY, OUTPUT);
    LTEUart.GPIOSetPinState(PIN_LTE_PWRKEY, LOW);
}

void unpressLTEPowerKey() {
    LTEUart.GPIOSetPinMode(PIN_LTE_PWRKEY, INPUT);
}

void toggleLTEPower() {
    pressLTEPowerKey();
    iwdg_feed();
    delay(2500);
    iwdg_feed();
    unpressLTEPowerKey();
}

void enableLTE() {
    if(!lteIsPoweredOn()) {
        toggleLTEPower();
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
    LTE.enableGPRS(true);
    delay(10);
    lteEnabled = true;
}

bool lteIsEnabled() {
    return lteEnabled;
}

void disableLTE() {
    LTEUart.println("\r\nAT+CPOWD=1\r\n");
    LTEUart.flush();
    LTEUart.begin(115200);
    lteEnabled = false;
}

time_t getLTETimestamp() {
    char reply[128];

    LTE.getReply("AT+CCLK?", reply);

    MatchState ms;
    ms.Target(reply);

    char result = ms.Match(
        "+CCLK: \"([%d]+)/([%d]+)/([%d]+),([%d]+):([%d]+):([%d]+)([\\+\\-])([%d]+)\""
    );
    //char result = ms.Match(
    //    "+CCLK: \"([%d]+)/"
    //);
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
