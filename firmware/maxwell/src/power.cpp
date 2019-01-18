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
#include "can_message_ids.h"
#include "can.h"
#include "status.h"

long int lastUpdated = 0;

bool batteryChargingEnabled = false;
bool auxiliaryPowerEnabled = false;

RollingAverage<double, 5> currentAmps;
RollingAverage<double, 10> batteryVoltage;
RollingAverage<double, 10> dynamoVoltage;

double lastChargingStatusSample = 0;

KeepAlive SleepTimeout(INACTIVITY_SLEEP_DURATION);

Adafruit_INA219 currentSense(CURRENT_SENSE_ADDRESS);
PCA9536 powerIo;

void power::init() {
    powerIo.setState(PIN_PWR_DISABLE_BATTERY_SRC, IO_LOW);
    powerIo.setState(PIN_PWR_ENABLE_VREF, IO_HIGH);

    powerIo.setMode(PIN_PWR_DISABLE_BATTERY_SRC, IO_OUTPUT);
    powerIo.setMode(PIN_PWR_I_POWER_SOURCE_INDICATOR, IO_INPUT);
    powerIo.setMode(PIN_PWR_I_BATT_CHARGING, IO_INPUT);
    powerIo.setMode(PIN_PWR_ENABLE_VREF, IO_OUTPUT);

    currentSense.begin();
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
        Statistics.put("Battery Voltage (Max)", dynamoVoltage.getValue());
    }
    Statistics.put("Battery Voltage", batteryVoltage.getValue());
    if(Statistics.valueFor("Battery Voltage (Max)") < batteryVoltage.getValue()) {
        Statistics.put("Battery Voltage (Max)", batteryVoltage.getValue());
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

void power::enableAutosleep(bool enable) {
    Log.log("Autosleep enabled: " + String(enable));
    SleepTimeout.enable(enable);
}

void power::refreshSleepTimeout() {
    SleepTimeout.refresh();
}

void power::checkSleepTimeout() {
    if(SleepTimeout.isTimedOut()) {
        power::sleep();
    }
}

power::PowerSource power::getPowerSource() {
    if(powerIo.getState(PIN_PWR_I_POWER_SOURCE_INDICATOR) == IO_LOW) {
        return power::PowerSource::dynamo;
    }
    return power::PowerSource::battery;
}

void power::sleep() {
    Log.log("Sleep requested");
    Output.println("Sleeping now");
    Output.flush();
    #if MOVEMENT_WAKE_ENABLED
        Log.log("Movement wake enabled");
    #endif

    // Stop logging
    Log.end();
    filesystem.card()->spiStop();

    powerIo.setState(PIN_PWR_ENABLE_VREF, IO_LOW);
    currentSense.powerDown();

    Output.end();

    // Disable canbus
    CanMsg sleepMsg;
    sleepMsg.IDE = CAN_ID_STD;
    sleepMsg.RTR = CAN_RTR_DATA;
    sleepMsg.ID = CAN_MAIN_MC_SLEEP;
    sleepMsg.DLC = 0;
    CanBus.send(&sleepMsg);

    util::beep(CHIRP_INIT_FREQUENCY, CHIRP_INIT_DURATION);

    // Disable neopixels before waiting for LTE modem shutdown
    digitalWrite(PIN_ENABLE_GNDPWR, LOW);

    // Stop LTE module
    if(LTEUart.ping()) {
        LTE.wait(5000, iwdg_feed);
        lte::enable(false);
        LTE.wait(6000, iwdg_feed);
        LTEUart.GPIOSetPinMode(PIN_LTE_OE, INPUT);
        LTEUart.flush();
        LTEUart.sleep();
    }
    CanBus.end();

    setGPIOModeToAllPins(GPIO_INPUT_FLOATING);
    // Turn of CAN transceiver
    pinMode(PIN_CAN_RS, OUTPUT);
    digitalWrite(PIN_CAN_RS, HIGH);
    // Disable neopixels (again since we just floated all of the pins)
    pinMode(PIN_ENABLE_GNDPWR, OUTPUT);
    digitalWrite(PIN_ENABLE_GNDPWR, LOW);
    // Disable buzzer
    pinMode(PIN_BUZZER, OUTPUT);
    digitalWrite(PIN_BUZZER, LOW);
    //pinMode(PIN_ESP_BOOT_FLASH_, OUTPUT);
    //digitalWrite(PIN_ESP_BOOT_FLASH_, LOW);
    // Disable Bluetooth
    pinMode(PIN_BT_DISABLE_, OUTPUT);
    digitalWrite(PIN_BT_DISABLE_, LOW);
    // Configure wake conditions
    attachInterrupt(PIN_I_POWER_ON, nvic_sys_reset, RISING);
    #if MOVEMENT_WAKE_ENABLED
        pinMode(PIN_I_SPEED, INPUT_PULLDOWN);
        attachInterrupt(PIN_I_SPEED, nvic_sys_reset, RISING);
    #endif

    systick_disable();
    adc_disable_all();
    disableAllPeripheralClocks();
    bkp_init();
    bkp_enable_writes();
    while(true) {
        iwdg_feed();
        sleepAndWakeUp(STOP, &Clock, 20);
    }
}
