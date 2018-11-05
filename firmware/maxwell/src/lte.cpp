#include <Arduino.h>
#undef min
#undef max
#include <libmaple/iwdg.h>
#include <AsyncModem.h>
#include <Regexp.h>
#include <Time.h>

#include "main.h"
#include "pin_map.h"
#include "lte.h"
#include "tasks.h"
#include "status.h"
#include "util.h"

AsyncModem::SIM7000 LTE = AsyncModem::SIM7000();

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

AsyncModem::SIM7000::NETWORK_STATUS networkStatus = AsyncModem::SIM7000::NETWORK_STATUS::NOT_YET_READY;
char connectionStatus[32] = {'\0'};
time_t millisOffset = 0;

void lte::loop() {
    LTE.loop();
}

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
        Output.println("Processing LTE Target: ");
        Output.println(lteTargetStatus);
    #endif

    if(lteTargetStatus == LTE_STATE_ON) {
        if(nextLteTargetStatus == LTE_STATE_NULL) {
            pressPowerKey();
            #ifdef LTE_DEBUG
                Output.println("Pressing LTE Power key");
            #endif
            minNextLteStatusTransition = millis() + 2500;
            nextLteTargetStatus = LTE_STATE_RELEASED;
        } else if (nextLteTargetStatus == LTE_STATE_RELEASED) {
            unpressPowerKey();
            #ifdef LTE_DEBUG
                Output.println("Unpressing LTE Power key");
            #endif
            maxNextLteStatusTransition = millis() + 30000;
            nextLteTargetStatus = LTE_STATE_ON;
        } else if (nextLteTargetStatus == LTE_STATE_ON) {
            #ifdef LTE_DEBUG
                Output.println("Checking LTE Power status...");
            #endif
            if(isPoweredOn()) {
                // Wait until the modem has fully-processed all
                // tasks.
                if(LTE.getQueueLength() > 0) {
                    #ifdef LTE_DEBUG
                        Output.println("LTE modem busy; checking in a moment...");
                    #endif
                    return;
                }
                #ifdef LTE_DEBUG
                    Output.println("LTE powered on; enabling now...");
                #endif
                bool result = enable();
                if(!result) {
                    #ifdef LTE_DEBUG
                        Output.println("Failed to enqueue task to enable LTE!");
                    #endif
                    return;
                }
                lteTargetStatus = LTE_STATE_NULL;
                nextLteTargetStatus = LTE_STATE_NULL;
                tasks::enableLTEStatusManager(false);
                maxNextLteStatusTransition = 0;
                #ifdef LTE_DEBUG
                    Output.println("LTE enablement queued");
                #endif
            } else {
                #ifdef LTE_DEBUG
                    Output.println("LTE not yet powered on");
                #endif
            }
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

uint8_t lteEnableAttempts = 0;

void lteEnabledSuccess(MatchState ms) {
    lteEnabled = true;
    lteEnableAttempts = 0;
    lte::refreshTimestamp();
}

void lteEnabledFailure(AsyncDuplex::Command* cmd) {
    lteEnableAttempts++;
    if(lteEnableAttempts < 3) {
        LTE.enableGPRS(
            "hologram",
            NULL,
            NULL,
            lteEnabledSuccess,
            lteEnabledFailure
        );
    } else {
        lteEnableAttempts = 0;
    }
}

bool lte::enable(bool _enable) {
    if(_enable) {
        if(!isPoweredOn()) {
            lte::togglePower();
        }

        #ifdef LTE_DEBUG
            Output.println("Running LTE.begin now...");
            Output.flush();
            delay(100);
        #endif
        LTE.begin(&LTEUart, &Output);
        #ifdef LTE_DEBUG
            Output.println("LTE begin queued...");
            Output.flush();
            delay(100);
        #endif
        return LTE.enableGPRS(
            "hologram",
            NULL,
            NULL,
            lteEnabledSuccess,
            lteEnabledFailure
        );
    } else {
        if(status::statusConnectionConnected()) {
            status::connectStatusConnection(false);
        }
        return LTE.execute(
            "AT+CPOWD=1",
            "POWER DOWN",
            [](MatchState ms) {
                lteEnabled = false;
            },
            [](AsyncDuplex::Command* cmd) {
                Output.println("Could not power down LTE modem!");
            },
            5000
        );
    }
}

bool lte::isEnabled() {
    return lteEnabled;
}

bool lte::refreshTimestamp() {
    LTE.execute(
        "AT+CCLK?",
        "+CCLK: \"([%d]+)/([%d]+)/([%d]+),([%d]+):([%d]+):([%d]+)([\\+\\-])([%d]+)\"",
        AsyncDuplex::Timing::ANY,
        [](MatchState ms){
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

            int offset = atoi(zone_str);
            if(zone_dir_str[0] == '-') {
                offset = -1 * offset;
            }
            composedTime -= (offset * 15 * 60);

            millisOffset = composedTime - millis();

            util::syncTimestampWithLTE();
        }
    );
}

time_t lte::getTimestamp() {
    return millis() + millisOffset;
}

bool lte::getConnectionStatus(char* buffer)  {
    strcpy(buffer, connectionStatus);
    return true;
}

bool lte::connectTo(char* host, uint16_t port) {
    char atCipstart[128] = {'\0'};
    sprintf(
        atCipstart,
        "AT+CIPSTART=\"TCP\",\"%s\",\"%d\"",
        host,
        port
    );
    AsyncDuplex::Command commands[] = {
        AsyncDuplex::Command(
            "AT+CIPSHUT",
            ".+\n",
            [](MatchState ms) {
                connectionStatus[0] = '\0';
            }
        ),
        AsyncDuplex::Command(
            "AT+CIPMUX=0",
            "OK"
        ),
        AsyncDuplex::Command(
            "AT+CIPRXGET=1",
            "OK"
        ),
        AsyncDuplex::Command(
            atCipstart,
            "OK"
        ),
        AsyncDuplex::Command(
            "AT+CIPSTATUS",
            "(CONNECT OK)",
            [](MatchState ms) {
                ms.GetCapture(connectionStatus, 0);
            },
            NULL,
            10000
        )
    };
    return LTE.executeChain(
        commands,
        sizeof(commands)/sizeof(commands[0])
    );
}

bool lte::disconnectConnection() {
    LTE.execute(
        "AT+CIPSHUT",
        ".+\n",
        [](MatchState ms) {
            connectionStatus[0] = '\0';
        }
    );
}

AsyncModem::SIM7000::NETWORK_STATUS lte::getNetworkStatus() {
    return networkStatus;
}

bool lte::collectStatusInformation() {
    LTE.execute(
        "AT+CIPSTATUS",
        "STATE: (.*)\r",
        [](MatchState ms) {
            ms.GetCapture(connectionStatus, 0);
        }
    );
    LTE.getNetworkStatus(&networkStatus);
}
