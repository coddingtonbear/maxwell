#include "gps.h"
#include "pin_map.h"
#include "main.h"

NMEAGPS gps;

void gpsPMTK(uint cmd, String data) {
    GPSSerial.println();
    GPSSerial.print("$");
    
    String commandString = "PMTK" + String(cmd) + String(data);

    GPSSerial.print(commandString);
    GPSSerial.print("*");

    uint8_t checkSum = 0;

    for (uint8_t i = 0; i < commandString.length(); i++) {
        checkSum = checkSum ^ commandString.charAt(i);
    }

    GPSSerial.print(String(checkSum, HEX));
    GPSSerial.print("\r\n");

    GPSSerial.flush();
}


void gpsWake() {
    GPSSerial.println();
}
