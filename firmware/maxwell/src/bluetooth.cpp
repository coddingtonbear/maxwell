#include <Arduino.h>
#include <KeepAlive.h>

#include "bluetooth.h"
#include "pin_map.h"
#include "main.h"

namespace bluetooth {
    bool bluetoothEnabled = true;
    KeepAlive BluetoothTimeout(BLUETOOTH_TIMEOUT);
}

void bluetooth::init() {
}

void bluetooth::loop() {
    bluetooth::checkTimeout();
    if(Output.available()) {
        bluetooth::refreshTimeout();
    }
}

bool bluetooth::bluetoothIsEnabled() {
    return bluetoothEnabled;
}

void bluetooth::enableBluetooth(bool enable) {
    if(enable && !bluetoothEnabled) {
        digitalWrite(PIN_BT_DISABLE_, HIGH);
        BluetoothTimeout.refresh();
        bluetoothEnabled = true;
    } else if(!enable && bluetoothEnabled) {
        digitalWrite(PIN_BT_DISABLE_, LOW);
        bluetoothEnabled = false;
    }
}

String bluetooth::sendCommand(String command) {
    String result;

    Output.flush();

    delay(250);
    digitalWrite(PIN_BT_KEY, HIGH);
    delay(250);
    Output.println(command);
    Output.flush();
    delay(250);
    digitalWrite(PIN_BT_KEY, LOW);
    delay(250);

    uint32 started = millis();

    Output.flush();
    while(millis() < started + 1000) {
        while(Output.available() > 0) {
            result += (char)Output.read();
        }
    }
    Output.flush();
    delay(100);

    return result;
}

void bluetooth::refreshTimeout() {
    BluetoothTimeout.refresh();
}

void bluetooth::delayTimeout(uint32_t value) {
    BluetoothTimeout.delayUntil(value);
}

void bluetooth::checkTimeout() {
    if(BluetoothTimeout.isTimedOut() && bluetoothEnabled) {
        Output.println("<Bluetooth Timeout>");
        Output.flush();
        Log.log("bluetooth", "Bluetooth timeout; disabling.");
        bluetooth::enableBluetooth(false);
    }
}
