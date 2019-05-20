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
#include "display.h"


void LoggedSIM7000::newLineReceived() {
    char buffer[256];
    getLatestLine(buffer, 256);
    String line = String(buffer);
    line.trim();

    if(line.length() > 0) {
        Log.log("lte", "Rx: " + line);
    }

    AsyncModem::SIM7000::newLineReceived();
};
void LoggedSIM7000::commandSent(char* cmd) {
    Log.log("lte", "Tx: " + String(cmd));
}

LoggedSIM7000 LTE = LoggedSIM7000();

namespace lte {
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

    char connectionStatus[32] = {'\0'};
    time_t millisOffset = 0;

    uint8_t lteEnableAttempts = 0;

    void lteEnabledSuccess(MatchState ms) {
        lteEnabled = true;
        lteEnableAttempts = 0;
    }

    void lteEnabledFailure(ManagedSerialDevice::Command* cmd) {
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
}

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

    tasks::enableLTEStatusManager(true);

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
            [](ManagedSerialDevice::Command* cmd) {
                if(lte::isPoweredOn()) {
                    // If we're _still_ powered-on,
                    // send the "urgent shutdown" command
                    LTE.execute("AT+CPOWD=0");
                    util::safeDelay(2500);
                    // If we're _still_ powered-on show
                    // an error message on the console &
                    // display.
                    if(lte::isPoweredOn()) {
                        Output.println(
                            "Could not power down LTE modem!"
                        );
                        Display.addAlert(
                            "Could not power\ndown LTE modem!"
                        );
                    } else {
                        lteEnabled = false;
                    }
                }
            },
            10000
        );
    }
}

bool lte::isEnabled() {
    return lteEnabled;
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
    ManagedSerialDevice::Command commands[] = {
        ManagedSerialDevice::Command(
            "AT+CIPSHUT",
            ".+\n",
            [](MatchState ms) {
                connectionStatus[0] = '\0';
            }
        ),
        ManagedSerialDevice::Command(
            "AT+CIPMUX=0",
            "OK"
        ),
        ManagedSerialDevice::Command(
            "AT+CIPRXGET=1",
            "OK"
        ),
        ManagedSerialDevice::Command(
            atCipstart,
            "OK"
        ),
        ManagedSerialDevice::Command(
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
    return LTE.getNetworkStatus();
}

bool lte::collectStatusInformation() {
    LTE.execute(
        "AT+CIPSTATUS",
        "STATE: (.*)\r",
        [](MatchState ms) {
            ms.GetCapture(connectionStatus, 0);
        }
    );
}

bool lte::isLoggingNow() {
    return (
        ((millis() - status::getLastStatusUpdateTime()) < 60000)
        && status::getLastStatusUpdateTime() > 0
    );
}
