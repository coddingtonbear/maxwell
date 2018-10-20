#include "bluetooth.h"
#include "pin_map.h"
#include "main.h"

bool bluetoothEnabled = true;

bool ble::bluetoothIsEnabled() {
    return bluetoothEnabled;
}

void ble::enableBluetooth(bool enable) {
    if(enable && !bluetoothEnabled) {
        Log.log("Local bluetooth enabled");
        Output.disableInterface(&BTSerial);
        BTSerial.end();
        digitalWrite(PIN_BT_DISABLE_, HIGH);
        bluetoothEnabled = true;
    } else if(!enable && bluetoothEnabled) {
        Log.log("Local bluetooth disabled");
        digitalWrite(PIN_BT_DISABLE_, LOW);
        Output.enableInterface(&BTSerial);
        Output.begin();
        bluetoothEnabled = false;
    }
}
