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

long longitude = 0;
long latitude = 0;
uint32 speedCounter = 0;
uint32 speedCounterPrev = 0;
uint32 lastSpeedRefresh = 0;
RollingAverage<double, 5> currentSpeedMph;

bool gpsFixAvailable = false;
char nmeaBuffer[255] = {'\0'};
MicroNMEA nmea(nmeaBuffer, sizeof(nmeaBuffer));

uint32_t lastStatusUpdate = 0;
unsigned long lastTimeUpdate = 0;

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

char statusUpdate[1024] = {'\0'};

bool status::sendStatusUpdate() {
    if (!lte::isEnabled()) {
        return false;
    }

    if(!status::statusConnectionConnected()) {
        status::connectStatusConnection();
        return false;
    }
    statusUpdate[0] = '\0';

    if(latitude && longitude) {
        char positionBuffer[32];
        sprintf(
            positionBuffer,
            "%.9f|%.9f",
            (float)latitude / 1e6,
            (float)longitude / 1e6
        );
        appendStatusUpdateLine(statusUpdate, "position", positionBuffer);
    }
    appendStatusUpdateLine(
        statusUpdate,
        "velocity",
        String(currentSpeedMph.getValue()).c_str()
    );
    appendStatusUpdateLine(
        statusUpdate,
        "timestamp",
        String((uint32_t)Clock.get()).c_str()
    );
    appendStatusUpdateLine(
        statusUpdate,
        "uptime",
        String(millis()).c_str()
    );
    power::PowerSource source = power::getPowerSource();
    if(source == power::PowerSource::dynamo) {
        appendStatusUpdateLine(
            statusUpdate,
            "power_source",
            "dynamo"
        );
    } else {
        appendStatusUpdateLine(
            statusUpdate,
            "power_source",
            "battery"
        );
    }
    uint32 errCode = Log.getErrorCode();
    if(errCode) {
        appendStatusUpdateLine(
            statusUpdate,
            "sd_logging",
            String("0").c_str()
        );
    } else {
        appendStatusUpdateLine(
            statusUpdate,
            "sd_logging",
            String("1").c_str()
        );
    }
    appendStatusUpdateLine(
        statusUpdate,
        "power.battery_voltage",
        String(power::getVoltage(VOLTAGE_BATTERY)).c_str()
    );
    appendStatusUpdateLine(
        statusUpdate,
        "power.dynamo_voltage",
        String(power::getVoltage(VOLTAGE_DYNAMO)).c_str()
    );
    appendStatusUpdateLine(
        statusUpdate,
        "power.rectified_voltage",
        String(power::getVoltage(VOLTAGE_RECTIFIED)).c_str()
    );
    appendStatusUpdateLine(
        statusUpdate,
        "power.current_amps",
        String(power::getCurrentUsage()).c_str()
    );

    LedStatus ledStatus;
    neopixel::getStatus(ledStatus);
    appendStatusUpdateLine(
        statusUpdate,
        "led.color.1",
        ("#" + String(ledStatus.red, HEX) + String(ledStatus.green, HEX) + String(ledStatus.blue, HEX)).c_str()
    );
    appendStatusUpdateLine(
        statusUpdate,
        "led.color.2",
        ("#" + String(ledStatus.red2, HEX) + String(ledStatus.green2, HEX) + String(ledStatus.blue2, HEX)).c_str()
    );
    appendStatusUpdateLine(
        statusUpdate,
        "led.enabled",
        String(ledStatus.enabled).c_str()
    );
    appendStatusUpdateLine(
        statusUpdate,
        "led.cycle_id",
        String(ledStatus.cycle).c_str()
    );
    appendStatusUpdateLine(
        statusUpdate,
        "led.brightness",
        String(ledStatus.brightness).c_str()
    );
    appendStatusUpdateLine(
        statusUpdate,
        "led.interval",
        String(ledStatus.interval).c_str()
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
    GPSUart.println();
    GPSUart.print("$");

    String commandString = "PMTK" + String(cmd) + String(data);

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
        GPSUart.write('\n');
        GPSUart.write('\n');
    } else {
        gpsPMTK(161, ",0");
    }
}

bool status::syncClockWithGps() {
    MicroNMEA* nmea = getGpsFix();

    time_t time;
    if(nmea->isValid()) {
        tmElements_t timeEts;
        timeEts.Hour = nmea->getHour();
        timeEts.Minute = nmea->getMinute();
        timeEts.Second = nmea->getSecond();
        timeEts.Day = nmea->getDay();
        timeEts.Month = nmea->getMonth();
        timeEts.Year = nmea->getYear() - 1970;

        time = makeTime(timeEts);
        Clock.set(time);
        lastTimeUpdate = millis();

        return true;
    } else {
        return false;
    }
}
