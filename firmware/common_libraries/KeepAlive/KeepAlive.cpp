#include <Arduino.h>

#include "KeepAlive.h"

KeepAlive::KeepAlive(uint32_t _timeoutInterval) {
    timeoutInterval = _timeoutInterval;
    refresh();
}

void KeepAlive::refresh() {
    timeout = millis() + timeoutInterval;
}

void KeepAlive::enable(bool _enable) {
    enabled = _enable;
}

void KeepAlive::delayUntil(uint32_t _until) {
    timeout = _until;
}

bool KeepAlive::isEnabled() {
    return enabled;
}

bool KeepAlive::isTimedOut() {
    if(enabled) {
        return millis() > timeout;
    }
    return false;
}
