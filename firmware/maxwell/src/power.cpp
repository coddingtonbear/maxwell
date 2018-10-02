#include <Arduino.h>
#include <RollingAverage.h>
#include "main.h"
#include "pin_map.h"
#include "power.h"

#include <libmaple/adc.h>
#include <libmaple/dma.h>

long int lastUpdated = 0;

bool batteryChargingEnabled = false;
bool auxiliaryPowerEnabled = false;

RollingAverage<double, 5> currentAmps;
RollingAverage<double, 10> senseVoltage;
RollingAverage<double, 10> batteryVoltage;

double lastChargingStatusSample = 0;

uint32 adcbuf[POWER_SAMPLE_COUNT+1]; 
uint8 ADC1_Sequence[] = {10, 0, 0, 0, 0, 0};
uint8 ADC2_Sequence[] = {11, 0, 0, 0, 0, 0};

void initADCs() {
    // Note: much of this was lifted from 
    // http://www.stm32duino.com/viewtopic.php?f=3&t=757&p=8474#p8474

    adc_set_sample_rate(ADC1, POWER_SAMPLE_RATE);
    adc_set_sample_rate(ADC2, POWER_SAMPLE_RATE);

    adc_calibrate(ADC1);
    adc_calibrate(ADC2);

    ADC1->regs->CR1 = 1 << 8;        // Set scan mode  
    ADC1->regs->CR1 |= 6 << 16;      //Regular simultaneous mode. Required for ADC1 only, ADC2 is slave
    ADC1->regs->CR2 = ( ADC_CR2_CONT | ADC_CR2_DMA | ADC_CR2_EXTSEL | ADC_CR2_EXTTRIG); //0xe0102; cont conversion, DMA, right aligned, disable external; EXTSEL, exttrig=0,jswstart=0
      
    adc_set_reg_seqlen(ADC1, POWER_CHANNEL_COUNT);  // how many channels per ADC
    //ADCx->regs->SQR3-1 holds the sequence of channels to convert. A conversion function is provided calc_adc_sequence(ADC1_Sequence) only for SQR3. 
    //If more than 6 channels are needed, repeat the same for SQR2 and SQR1 (SQR1 only holds 4 sequences)
    ADC1->regs->SQR3 |= calc_adc_SQR3(ADC1_Sequence);                //200; for IN8 and IN6, on Maple Mini these are D3, D5

    ADC2->regs->CR1 = 1 << 8;  // Set scan mode 
    ADC2->regs->CR2 = ( ADC_CR2_CONT | ADC_CR2_EXTSEL | ADC_CR2_EXTTRIG); //0xe0003; 

    adc_set_reg_seqlen(ADC2, POWER_CHANNEL_COUNT);
    ADC2->regs->SQR3 |= calc_adc_SQR3(ADC2_Sequence);                //= 167 forIN7 and IN5, on Maple Mini these are D4, D6 respectively

    ADC1->regs->CR2 |= ADC_CR2_ADON;  // it is critical to enable ADC (bit 0=1) independently of all other changes to the CR2 register
    ADC2->regs->CR2 |= ADC_CR2_ADON;  // enabling all at once (i.e. ADC_CR2_ADON | ADC_CR2_CONT | ADC_CR2_EXTSEL ) will cause problems when used with continuous mode  
}

// calculate values for SQR3. Function could be extended to also work for SQR2 and SQR1. As is, you can sequence only 6 sequences per ADC
uint32 calc_adc_SQR3(uint8 adc_sequence[6]){
  int SQR3=0;

  for (int i=0;i<6;i++)     // There are 6 available sequences in SQR3 (SQR2 also 6, and 4 in SQR1).
  {
    //each sequence is 5 bits
    SQR3 |= adc_sequence[i] << ((i*5));  
  } 
  return SQR3;
} 

// set only the registers that need to be reset before each conversion
void adc_to_ready() {
  ADC1->regs->CR2 = ( ADC_CR2_CONT | ADC_CR2_DMA | ADC_CR2_EXTSEL | ADC_CR2_EXTTRIG); //0xe0102; cont conversion, DMA, right aligned, disable external; EXTSEL, exttrig=0,jswstart=0
  ADC2->regs->CR2 = ( ADC_CR2_CONT | ADC_CR2_EXTSEL | ADC_CR2_EXTTRIG); //0xe0002; 
  ADC1->regs->CR2 |= ADC_CR2_ADON;  // it is critical to enable ADC (bit 0=1) independently of all other changes to the CR2 register
  ADC2->regs->CR2 |= ADC_CR2_ADON;  // enabling all at once (i.e. ADC_CR2_ADON | ADC_CR2_CONT | ADC_CR2_EXTSEL ) will cause problems when used with continuous mode   
}

// check for DMA transfer finished, resetting isr bit
uint8 dma_transfer_finished() {
  if(dma_get_isr_bits(DMA1,DMA_CH1)==0x07) {
    int result=dma_get_irq_cause(DMA1,DMA_CH1);//<--clears isr bits
    return 1;
  }
  return 0;
}

// initialize DMA1, Channel1 (ADC)
void set_dma() {
  dma_init(DMA1);
  dma_setup_transfer(DMA1, DMA_CH1, &ADC1->regs->DR, DMA_SIZE_32BITS,
                     adcbuf, DMA_SIZE_32BITS, DMA_MINC_MODE);
  dma_set_num_transfers(DMA1, DMA_CH1,POWER_SAMPLE_COUNT);
  dma_set_priority(DMA1, DMA_CH1, DMA_PRIORITY_VERY_HIGH);   
  
  dma_enable(DMA1, DMA_CH1);   
}

void updatePowerMeasurements() {
    double tempVoltage;
    double tempBattVoltage;
    double tempSenseVoltage;
    double tempAmps;

    adc_to_ready();
    set_dma();
    ADC1->regs->CR2 |= ADC_CR2_SWSTART; //start conversion, STM32 will reset this bit immediately. Only ADC1 (master) needs to be started
    
    while(!dma_transfer_finished());
    dma_disable(DMA1,DMA_CH1); //stop dma transfer

    uint32_t battVoltageSum = 0;
    uint32_t senseVoltageSum = 0;
    for(int i=0;i<(POWER_SAMPLE_COUNT);i++) {
        uint16_t battSample = (adcbuf[i] & 0xFFFF);
        uint16_t senseSample = ((adcbuf[i] & 0xFFFF0000) >>16);

        battVoltageSum += battSample;
        senseVoltageSum += senseSample;
    }

    tempBattVoltage = convertAdcToVoltage(battVoltageSum / POWER_SAMPLE_COUNT);
    tempSenseVoltage = convertAdcToVoltage(senseVoltageSum / POWER_SAMPLE_COUNT);

    batteryVoltage.addMeasurement(tempBattVoltage);
    senseVoltage.addMeasurement(tempSenseVoltage);

    tempAmps = (
        tempBattVoltage - tempSenseVoltage
    )/SENSE_RESISTOR_VALUE;
    currentAmps.addMeasurement(tempAmps);

    Statistics.put("Battery Voltage", batteryVoltage.getValue());
    if(Statistics.valueFor("Battery Voltage (Max)") < batteryVoltage.getValue()) {
        Statistics.put("Battery Voltage (Max)", batteryVoltage.getValue());
    }
    Statistics.put("Sense Voltage", senseVoltage.getValue());
    if(Statistics.valueFor("Sense Voltage (Max)") < senseVoltage.getValue()) {
        Statistics.put("Sense Voltage (Max)", senseVoltage.getValue());
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

double getVoltage(uint source) {
    double result = 0;

    switch(source) {
        case VOLTAGE_BATTERY:
            result = batteryVoltage.getValue();
            break;
        case VOLTAGE_SENSE:
            result = senseVoltage.getValue();
            break;
    }

    return result;
}

double convertAdcToVoltage(uint32_t value) {
    return value * 2.5 * 2 / 4096;
}

double getCurrentUsage() {
    return currentAmps.getValue();
}

bool batteryChargingIsEnabled() {
    return batteryChargingEnabled;
}

void enableBatteryCharging(bool enable) {
    if(enable) {
        digitalWrite(PIN_ENABLE_BATT_CHARGE_, LOW);
        batteryChargingEnabled = true;
    } else {
        digitalWrite(PIN_ENABLE_BATT_CHARGE_, HIGH);
        batteryChargingEnabled = false;
    }
}

uint8_t getChargingStatus() {
    // Use ADC3 because we're using a dual simultaneous sampling
    // mode for ADC1/2 for measuring power/current, and by default
    // analogRead uses ADC1
    int value = adc_read(ADC3, 12);

    if(value < 500) {
        return CHARGING_STATUS_CHARGING_NOW;
    } else if(value > 3500) {
        return CHARGING_STATUS_FULLY_CHARGED;
    } else {
        return CHARGING_STATUS_SHUTDOWN;
    }
}
