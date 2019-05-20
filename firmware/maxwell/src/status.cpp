#include <Arduino.h>
#undef min
#undef max
#include <ArduinoJson.h>
#include <RollingAverage.h>
#include <MCP79412RTC.h>
#include <MicroNMEA.h>

#include "main.h"
#include "power.h"
#include "neopixel.h"
#include "lte.h"
#include "status.h"

#include "private.h"

namespace status {
    uint32 speedCounter = 0;
    uint32 speedCounterPrev = 0;
    uint32 lastSpeedRefresh = 0;
    RollingAverage<double, 5> currentSpeedMph;

    bool gpsFixAvailable = false;
    char nmeaBuffer[255] = {'\0'};
    MicroNMEA nmea(nmeaBuffer, sizeof(nmeaBuffer));

    uint32_t lastStatusUpdate = 0;
    unsigned long lastTimeUpdate = 0;

    uint8_t logRotation = 0;
}

extern "C" char* sbrk(int incr);
static int32_t status::getFreeMemory() {
  char top = 't';
  return &top - reinterpret_cast<char*>(sbrk(0));
}

void status::init() {
    // Configure the speed counter for event counting mode
    Wire.beginTransmission(SPEED_COUNTER_ADDRESS);
    Wire.write(0x0);
    Wire.write(B00100000);
    Wire.write(0x0);
    Wire.write(0x0);
    Wire.write(0x0);
    Wire.endTransmission();

    time_t powerFailed, powerReturned;
    if(Clock.powerFail(&powerFailed, &powerReturned)) {
        Output.println(
            "Warning: Power has failed since last boot!"
        );
    }

    Clock.out(LOW);
    Clock.alarmPolarity(HIGH);
    Clock.vbaten(true);

    GPSUart.begin(9600);
    delay(100);
    gpsEnable(true);
}

void status::loop() {
    updateGpsFix();
    if(
        gpsFixValid() && (
            lastTimeUpdate == 0 ||
            (millis() - lastTimeUpdate) > GPS_TIME_UPDATE_INTERVAL
        )
    ) {
        syncClockWithGps();
    }
}

uint16_t status::getSpeedCounter() {
    Wire.beginTransmission(SPEED_COUNTER_ADDRESS);
    Wire.write(0x1);
    Wire.endTransmission();

    uint16_t value = 0;
    Wire.requestFrom(SPEED_COUNTER_ADDRESS, 3);
    for (uint8_t i = 0; i < 3; i++) {
        uint8_t digit = Wire.read();
        // Convert the digit from BCD, and multiply by position
        value += ( (digit/16*10) + (digit%16) ) * pow(10, i * 2);
    }

    Statistics.put("Dynamo Pole Counter", value);

    return value;
}

void status::refreshSpeed() {
    uint16_t speedCounter = getSpeedCounter();
    uint16_t pulseCount = speedCounter - speedCounterPrev;

    // There are 14 poles in the hub, and the outer tire is 80in in
    // circumference; so every pole is 5.714in of travel.
    double mph = (
        pulseCount * (SPEED_WHEEL_RADIUS_INCHES / SPEED_PULSES_PER_ROTATION)
        / (millis() - lastSpeedRefresh)
    ) / SPEED_INCHES_PER_MILE * SPEED_SECONDS_PER_HOUR;
    lastSpeedRefresh = millis();
    currentSpeedMph.addMeasurement(mph);

    if (
        pulseCount > 0 ||
        power::getChargingStatus() == CHARGING_STATUS_CHARGING_NOW
    ) {
        power::refreshSleepTimeout();
    }

    Statistics.put("Speed", currentSpeedMph.getValue());

    speedCounterPrev = speedCounter;
}

double status::getSpeed() {
    return currentSpeedMph.getValue();
}

void appendStatusUpdateLine(char* dest, const char* field, const char* value) {
    char statusUpdateLine[128];
    sprintf(statusUpdateLine, "%s=%s\r\n", field, value);
    strcat(dest, statusUpdateLine);
}

status::Status status::getStatus() {
    status::Status st;

    st.free_memory = getFreeMemory();

    MicroNMEA* fix = status::getGpsFix();

    st.gps_locked = fix->isValid();
    st.gps_latitude = (float)(fix->getLatitude() / 1e6);
    st.gps_longitude = (float)(fix->getLongitude() / 1e6);
    long altitude;
    st.gps_altitude_valid = fix->getAltitude(altitude);
    if(st.gps_altitude_valid) {
        st.gps_altitude = (float)(altitude / 1e3);
    }

    st.velocity = (float)currentSpeedMph.getValue();
    st.timestamp = (uint32_t)Clock.get();
    st.uptime = (uint32_t)millis();

    uint32 errCode = Log.getErrorCode();
    st.sd_logging = errCode ? false : true;

    st.voltage_battery = power::getVoltage(VOLTAGE_BATTERY);
    st.voltage_dynamo = power::getVoltage(VOLTAGE_DYNAMO);
    st.current_amps = power::getCurrentUsage();

    LedStatus ledStatus;
    neopixel::getStatus(ledStatus);
    st.led_color_1 = Color(
        ledStatus.red,
        ledStatus.green,
        ledStatus.blue
    );
    st.led_color_2 = Color(
        ledStatus.red2,
        ledStatus.green2,
        ledStatus.blue2
    );
    st.led_enabled = ledStatus.enabled;
    st.led_cycle_id = ledStatus.cycle;
    st.led_brightness = ledStatus.brightness;
    st.led_interval = ledStatus.interval;

    return st;
}

char statusUpdate[1024] = {'\0'};

void status::logStatusUpdate() {
    // Don't log everything every cycle since logging
    // takes enough time that you might see LED stuttering
    Status st = getStatus();

    if(logRotation == 0) {
        Log.log("status", "gps_locked: " + String(st.gps_locked ? "1" : "0"));
    } else if(logRotation == 1) {
        Log.log("status", "gps_latitude: " + String(st.gps_latitude));
    } else if(logRotation == 2) {
        Log.log("status", "gps_longitude: " + String(st.gps_longitude));
    } else if(logRotation == 3) {
        if(st.gps_altitude_valid) {
            Log.log("status", "gps_altitude: " + String(st.gps_altitude));
        }
    } else if(logRotation == 4) {
        Log.log("status", "velocity: " + String(st.velocity));
    } else if(logRotation == 5) {
        Log.log("status", "battery_voltage: " + String(st.voltage_battery));
    } else if(logRotation == 6) {
        Log.log("status", "dynamo_voltage: " + String(st.voltage_dynamo));
    } else if(logRotation == 7) {
        Log.log("status", "current_amps: " + String(st.current_amps));
    } else if(logRotation == 8) {
        Log.log("status", "led_color_1: " + st.led_color_1.asHex());
    } else if(logRotation == 9) {
        Log.log("status", "led_color_2: " + st.led_color_2.asHex());
    } else if(logRotation == 10) {
        Log.log("status", "led_enabled: " + String(st.led_enabled ? "1" : "0"));
    } else if(logRotation == 11) {
        Log.log("status", "led_cycle_id: " + String(st.led_cycle_id));
    } else if(logRotation == 12) {
        Log.log("status", "led_brightness: " + String(st.led_brightness));
    } else if(logRotation == 13) {
        Log.log("status", "led_interval: " + String(st.led_interval));
    } else if(logRotation == 14) {
        Log.log("status", "free_memory: " + String(st.free_memory));
    } else {
        logRotation = 0;
        logStatusUpdate();
        return;
    }

    logRotation++;
}

bool status::sendStatusUpdate() {
    if (!lte::isEnabled()) {
        return false;
    }

    if(!status::statusConnectionConnected()) {
        status::connectStatusConnection();
        return false;
    }
    statusUpdate[0] = '\0';

    Status st = getStatus();

    if(st.gps_locked) {
        char positionBuffer[32];
        sprintf(
            positionBuffer,
            "%.9f|%.9f",
            st.gps_latitude,
            st.gps_longitude
        );
        appendStatusUpdateLine(statusUpdate, "position", positionBuffer);
    };
    appendStatusUpdateLine(
        statusUpdate,
        "velocity",
        String(st.velocity).c_str()
    );
    appendStatusUpdateLine(
        statusUpdate,
        "timestamp",
        String(st.timestamp).c_str()
    );
    appendStatusUpdateLine(
        statusUpdate,
        "uptime",
        String(st.uptime).c_str()
    );
    appendStatusUpdateLine(
        statusUpdate,
        "sd_logging",
        String(st.sd_logging ? "1" : "0").c_str()
    );
    appendStatusUpdateLine(
        statusUpdate,
        "power.battery_voltage",
        String(st.voltage_battery).c_str()
    );
    appendStatusUpdateLine(
        statusUpdate,
        "power.dynamo_voltage",
        String(st.voltage_dynamo).c_str()
    );
    appendStatusUpdateLine(
        statusUpdate,
        "power.current_amps",
        String(st.current_amps).c_str()
    );
    appendStatusUpdateLine(
        statusUpdate,
        "led.color.1",
        st.led_color_1.asHex().c_str()
    );
    appendStatusUpdateLine(
        statusUpdate,
        "led.color.2",
        st.led_color_2.asHex().c_str()
    );
    appendStatusUpdateLine(
        statusUpdate,
        "led.enabled",
        String(st.led_enabled).c_str()
    );
    appendStatusUpdateLine(
        statusUpdate,
        "led.cycle_id",
        String(st.led_cycle_id).c_str()
    );
    appendStatusUpdateLine(
        statusUpdate,
        "led.brightness",
        String(st.led_brightness).c_str()
    );
    appendStatusUpdateLine(
        statusUpdate,
        "led.interval",
        String(st.led_interval).c_str()
    );

    char cipsend[32];
    uint16_t statusUpdateLength = strlen(statusUpdate);
    sprintf(cipsend, "AT+CIPSEND=%d", statusUpdateLength);

    LTE.execute(
        cipsend,
        "",
        [statusUpdateLength](MatchState ms) {
            for(uint16_t pos = 0; pos < statusUpdateLength; pos++) {
                LTE.write(statusUpdate[pos]);
            }
            LTE.write(0x1a);
            lastStatusUpdate = millis();
        }
    );
}


bool status::connectStatusConnection(bool enabled) {
    if(!lte::isEnabled()) {
        return false;
    }

    if(enabled) {
        return lte::connectTo(STATUS_HOST, STATUS_PORT);
    } else {
        return LTE.execute(
            "AT+CIPSEND=3",
            "",
            [](MatchState ms) {
                LTE.write(0x04);  // EOT
                LTE.write('\r');
                LTE.write('\n');

                LTE.write(0x1a);
                lte::disconnectConnection();
            }
        );
    }
}

bool status::statusConnectionConnected() {
    if(!lte::isEnabled()) {
        return false;
    }

    char buffer[20];
    lte::getConnectionStatus(buffer);

    if(strcmp(buffer, "CONNECT OK") == 0) {
        return true;
    }

    return false;
}

uint32_t status::getLastStatusUpdateTime() {
    return lastStatusUpdate;
}

void status::gpsPMTK(uint cmd, String data) {
    return gpsPMTK("PMTK" + String(cmd) + data);
}

void status::gpsPMTK(String commandString) {
    GPSUart.println();
    GPSUart.print("$");

    GPSUart.print(commandString);
    GPSUart.print("*");

    uint8_t checkSum = 0;

    for (uint8_t i = 0; i < commandString.length(); i++) {
        checkSum = checkSum ^ commandString.charAt(i);
    }

    GPSUart.print(String(checkSum, HEX));
    GPSUart.print("\r\n");

    GPSUart.flush();
    delay(100);
}

void status::updateGpsFix() {
    if(GPSUart.available()) {
        char readByte = GPSUart.read();

        #ifdef DEBUG_GPS
            Output.print(readByte);
        #endif

        nmea.process(readByte);

        gpsFixAvailable = nmea.isValid();
    }
}

bool status::gpsFixValid() {
    return gpsFixAvailable;
}

MicroNMEA* status::getGpsFix() {
    return &nmea;
}

void status::gpsEnable(bool enable) {
    if(enable) {
        gpsPMTK(225, ",0");
    } else {
        gpsPMTK(225, ",8");
    }
}

time_t status::getGpsTime() {
    MicroNMEA* nmea = getGpsFix();

    tmElements_t timeEts;
    timeEts.Hour = nmea->getHour();
    timeEts.Minute = nmea->getMinute();
    timeEts.Second = nmea->getSecond();
    timeEts.Day = nmea->getDay();
    timeEts.Month = nmea->getMonth();
    timeEts.Year = nmea->getYear() - 1970;

    return makeTime(timeEts);
}

bool status::syncClockWithGps() {
    MicroNMEA* nmea = getGpsFix();

    time_t time_s;
    if(nmea->isValid()) {
        time_t time_s = getGpsTime();

        if(
            year(time_s) > 2030 ||
            year(time_s) < 2019
        ) {
            // Do nothing; this time is clearly invalid;
            // we'll try again during the next loop
        } else {
            lastTimeUpdate = millis();
            Clock.set(time_s);
            Log.log(
                "status",
                "Setting clock from GPS to " + String((unsigned long)time_s, DEC)
            );
        }

        return true;
    } else {
        return false;
    }
}

String status::Color::asHex() {
    return (
        "#" + String(red, HEX) + String(green, HEX) + String(blue, HEX)
    ).c_str();
}
