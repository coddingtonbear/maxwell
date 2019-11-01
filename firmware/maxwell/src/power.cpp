#include <Arduino.h>
#undef min
#undef max
#include <Adafruit_INA219.h>
#include <RollingAverage.h>
#include <STM32Sleep.h>
#include <KeepAlive.h>
#include <libmaple/adc.h>
#include <libmaple/dma.h>
#include <libmaple/iwdg.h>
#include <PCA9536.h>

#include "main.h"
#include "pin_map.h"
#include "power.h"
#include "lte.h"
#include "util.h"
#include "status.h"
#include "display.h"

namespace power {
    long int lastUpdated = 0;

    bool batteryChargingEnabled = false;
    bool auxiliaryPowerEnabled = false;
    bool dynamoEnabled = false;

    bool dynamoOvervoltage = false;
    bool dynamoOvervoltageCheckingEnabled = true;

    RollingAverage<double, 10> currentAmps;
    RollingAverage<double, 25> batteryVoltage;
    RollingAverage<double, 25> dynamoVoltage;

    double lastChargingStatusSample = 0;

    KeepAlive SleepTimeout(INACTIVITY_SLEEP_DURATION);

    Adafruit_INA219 currentSense(CURRENT_SENSE_ADDRESS);
    PCA9536 powerIo;
}

void power::init() {
    powerIo.setMode(PIN_PWR_I_BATT_CHARGING, IO_INPUT);
    powerIo.setPolarity(PIN_PWR_I_BATT_CHARGING, IO_NON_INVERTED);

    currentSense.begin();

    power::enableDynamoPower(true);
    power::enableAux(true);
}

void power::enableDynamoPower(bool enabled) {
    if(enabled) {
        powerIo.setState(PIN_RECTIFIER_RELAY_A, IO_HIGH);
        powerIo.setState(PIN_RECTIFIER_RELAY_B, IO_LOW);
        Log.log("power", "Enabling dynamo power");
    } else {
        powerIo.setState(PIN_RECTIFIER_RELAY_A, IO_LOW);
        powerIo.setState(PIN_RECTIFIER_RELAY_B, IO_HIGH);
        Log.log("power", "Disabling dynamo power");
    }
    powerIo.setMode(PIN_RECTIFIER_RELAY_A, IO_OUTPUT);
    powerIo.setMode(PIN_RECTIFIER_RELAY_B, IO_OUTPUT);
    delay(100);
    powerIo.setMode(PIN_RECTIFIER_RELAY_A, IO_INPUT);
    powerIo.setMode(PIN_RECTIFIER_RELAY_B, IO_INPUT);

    dynamoEnabled = enabled;
    dynamoOvervoltage = false;
}

bool power::isOvervoltageCheckingEnabled() {
    return dynamoOvervoltageCheckingEnabled;
}

void power::enableDynamoOvervoltageChecking(bool enabled) {
    dynamoOvervoltageCheckingEnabled = enabled;
}

bool power::isOvervoltage() {
    return dynamoOvervoltage;
}

bool power::isDynamoEnabled() {
    return dynamoEnabled;
}

void power::setWake(bool enable) {
    if(enable) {
        digitalWrite(PIN_POWER_ON, HIGH);
    } else {
        digitalWrite(PIN_POWER_ON, LOW);
    }
    pinMode(PIN_POWER_ON, OUTPUT);
}

void power::loop() {
    double voltage = dynamoVoltage.getValue();

    if(dynamoOvervoltageCheckingEnabled) {
        if(!dynamoOvervoltage && voltage > OVERVOLTAGE_HIGH) {
            dynamoOvervoltage = true;

            enableDynamoPower(false);

            Display.addAlert("Dynamo Overvoltage!");
        } else if(dynamoOvervoltage && voltage < OVERVOLTAGE_LOW) {
            dynamoOvervoltage = false;

            enableDynamoPower(true);
        }
    }

    if(Output.available()) {
        power::refreshSleepTimeout();
    }
    checkSleepTimeout();
}

uint16_t power::getAdcValue(uint8_t ch) {
    uint8_t adcConfig = 0;
    if(ch == 2) {
        adcConfig |= 1 << 6;  // CH2
    }
    if(ch == 1) {
        adcConfig |= 1 << 5;  // CH1
    }
    if(ch == 0) {
        adcConfig |= 1 << 4;  // CH0
    }
    adcConfig |= 1 << 3;  // External VREF

    Wire.beginTransmission(ADC_ADDRESS);
    Wire.write(adcConfig);
    Wire.endTransmission();

    float result;
    for(uint8_t i = 0; i < ADC_SAMPLES; i++) {
        Wire.requestFrom(ADC_ADDRESS, 2);
        delay(1);
        uint16_t byte0 = Wire.read();
        uint16_t byte1 = Wire.read();
        result = ((byte0 & B1111) << 8) + byte1;
    }

    return result;
}

void power::updatePowerMeasurements() {
    uint16_t tempDynamoVoltage = getAdcValue(PIN_ADC_DYNAMO_VOLTAGE);
    uint16_t tempBattVoltage = getAdcValue(PIN_ADC_BATT_VOLTAGE);

    dynamoVoltage.addMeasurement(
        convertAdcToVoltage(tempDynamoVoltage, 20000, 1500)
    );
    batteryVoltage.addMeasurement(
        convertAdcToVoltage(tempBattVoltage, 1000, 1000)
    );

    double tempAmps = currentSense.getCurrent_mA();
    currentAmps.addMeasurement(tempAmps / 1000);

    Statistics.put("Dynamo Voltage", dynamoVoltage.getValue());
    if(Statistics.valueFor("Dynamo Voltage (Max)") < dynamoVoltage.getValue()) {
        Statistics.put("Dynamo Voltage (Max)", dynamoVoltage.getValue());
    }
    Statistics.put("Battery Voltage", batteryVoltage.getValue());
    if(Statistics.valueFor("Battery Voltage (Max)") < batteryVoltage.getValue()) {
        Statistics.put("Battery Voltage (Max)", batteryVoltage.getValue());
    }
    Statistics.put("Dynamo Voltage", dynamoVoltage.getValue());
    if(Statistics.valueFor("Dynamo Voltage (Max)") < dynamoVoltage.getValue()) {
        Statistics.put("Dynamo Voltage (Max)", dynamoVoltage.getValue());
    }
    Statistics.put("Current (Amps)", currentAmps.getValue());
    if(Statistics.valueFor("Current (Amps) (Max)") < currentAmps.getValue()) {
        Statistics.put("Current (Amps) (Max)", currentAmps.getValue());
    }

    uint8_t status = getChargingStatus();
    String minutesName = "Charging Status " + String(status) + " (minutes)";
    Statistics.put("Charging Status (now)", status);
    double value = Statistics.valueFor(minutesName) + (
        (millis() - lastChargingStatusSample) / 60000
    );
    Statistics.put(minutesName, value);

    lastChargingStatusSample = millis();
}

double power::getVoltage(uint source) {
    double result = 0;

    switch(source) {
        case VOLTAGE_BATTERY:
            result = batteryVoltage.getValue();
            break;
        case VOLTAGE_DYNAMO:
            result = dynamoVoltage.getValue();
            break;
    }

    return result;
}

double power::convertAdcToVoltage(uint32_t value, uint16_t r1=1000, uint16_t r2=1000) {
    return ((float)value / 4096 * 2.5 * (r1 + r2)) / r2;
}

double power::getCurrentUsage() {
    return currentAmps.getValue();
}

uint8_t power::getChargingStatus() {
    if(
        dynamoVoltage.getValue() > 4.0
        && powerIo.getState(PIN_PWR_I_BATT_CHARGING) == IO_LOW
    ) {
        return CHARGING_STATUS_CHARGING_NOW;
    }
    return CHARGING_STATUS_SHUTDOWN;
}

void power::enableAux(bool enable) {
    if(enable) {
        digitalWrite(PIN_ENABLE_AUX, HIGH);
    } else {
        digitalWrite(PIN_ENABLE_AUX, LOW);
    }
    pinMode(PIN_ENABLE_AUX, OUTPUT);
}

void power::enableAutosleep(bool enable) {
    Log.log("power", "Autosleep enabled: " + String(enable));
    SleepTimeout.enable(enable);
}

bool power::isAutosleepEnabled() {
    return SleepTimeout.isEnabled();
}

void power::refreshSleepTimeout() {
    SleepTimeout.refresh();
}

void power::checkSleepTimeout() {
    if(SleepTimeout.isTimedOut()) {
        Output.println("Sleep timeout reached; sleeping.");
        power::sleep();
    }
}

void power::printPowerIOState() {
    pin_t pins[4] = { IO0, IO1, IO2, IO3 };

    Output.println("PIN\tMODE\tSTATE\tPOLARITY");
    Output.println("---\t----\t-----\t--------");
    for (byte j=0; j<4; j++) {
        byte mode = powerIo.getMode(pins[j]);
        byte state = powerIo.getState(pins[j]);
        byte polarity = powerIo.getPolarity(pins[j]);
        Output.print("IO");
        Output.print(j);
        Output.print("\t");
        if(mode) {
            Output.print("IN");
        } else {
            Output.print("OUT");
        }
        Output.print("\t");
        if(state) {
            Output.print("HIGH");
        } else {
            Output.print("LOW");
        }
        Output.print("\t");
        if(polarity) {
            Output.print("INVERTED");
        }
        Output.println();
    }
}

uint8_t power::getPowerIOState(Pca9536::pin_t pin) {
    return powerIo.getState(pin);
}

uint8_t power::getPowerIOComResult() {
    return powerIo.getComResult();
}

void power::sleep() {
    Log.log("power", "Sleep requested");
    Output.println("Sleeping now");
    Output.flush();

    Display.addAlert("Powering down");
    Display.refresh();

    // Turn on the dynamo relay so that if an empty
    // battery is swapped-in, we can charge it even
    // if there's not enough power to turn on the uC
    power::enableDynamoPower(true);

    // Stop logging
    Log.end();
    filesystem.card()->spiStop();

    // Disable GPS
    status::gpsEnable(false);
    status::saveOdometer();
    status::savePosition();

    currentSense.powerDown();

    Output.end();

    // Disable neopixels before waiting for LTE modem shutdown
    digitalWrite(PIN_ENABLE_NEOPIXEL, LOW);

    // Stop LTE module
    if(LTEUart.ping()) {
        LTE.wait(5000, iwdg_feed);
        lte::enable(false);
        LTE.wait(6000, iwdg_feed);
        LTEUart.GPIOSetPinMode(PIN_LTE_OE, LOW);
        LTEUart.flush();
        // Clear out the LTE receive buffer
        while(LTEUart.available()) {
            LTEUart.read();
        }
        LTEUart.sleep();
    }

    // Disable neopixels (again since we just floated all of the pins)
    digitalWrite(PIN_ENABLE_NEOPIXEL, LOW);
    pinMode(PIN_ENABLE_NEOPIXEL, OUTPUT);
    //pinMode(PIN_ESP_BOOT_FLASH_, OUTPUT);
    //digitalWrite(PIN_ESP_BOOT_FLASH_, LOW);
    // Disable Bluetooth
    digitalWrite(PIN_BT_DISABLE_, LOW);
    pinMode(PIN_BT_DISABLE_, OUTPUT);
    // Disable Aux
    power::enableAux(false);

    setGPIOModeToAllPins(GPIO_INPUT_FLOATING);

    // Really: nothing should be running after this command is executed,
    // but let's leave the sleep code after this just in case we're running
    // from a different power source.
    power::setWake(false);
}
