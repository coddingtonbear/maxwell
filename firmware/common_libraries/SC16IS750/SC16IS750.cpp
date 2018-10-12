/*
Description:
This is a example code for Sandbox Electronics' I2C/SPI to UART bridge module.
You can get one of those products on
http://sandboxelectronics.com

Version:
V0.1

Release Date:
2014-02-16

Author:
Tiequan Shao          info@sandboxelectronics.com

Lisence:
CC BY-NC-SA 3.0

Please keep the above information when you use this code in your project.
*/

//#define SC16IS750_DEBUG_PRINT
#include <SPI.h>
#include "SC16IS750.h"


SPISettings settings(2000000, MSBFIRST, SPI_MODE0);
//SPISettings settings(250000, MSBFIRST, SPI_MODE0);

SC16IS750::SC16IS750(
    uint8_t addr_sspin,
    uint8_t chan,
    unsigned long crystal_freq
){
    crystal_frequency = crystal_freq;
    channel = chan;
    device_address_sspin = addr_sspin;

    digitalWrite(device_address_sspin, HIGH);
    pinMode(device_address_sspin, OUTPUT);

    spiBus = &SPI;
}

void SC16IS750::setSpiBus(SPIClass* bus) {
    spiBus = bus;
}


void SC16IS750::begin(uint32_t baud, bool reset)
{
    if (baud == 0) {
        baud = _baud;
    }
    _baud = baud;

    spiBus->beginTransaction(settings);
    digitalWrite(device_address_sspin, LOW);
    if (reset) {
        ResetDevice();
    }
    FIFOEnable(1);

    // Enable enhanced functions
    uint8_t temp_lcr = ReadRegister(SC16IS750_REG_LCR);
    WriteRegister(SC16IS750_REG_LCR, 0xBF);
    WriteRegister(SC16IS750_REG_EFR, 1 << 4);
    WriteRegister(SC16IS750_REG_LCR, temp_lcr);;

    SetBaudrate(baud);
    SetLine(8,0,1);
    FIFOReset();
    digitalWrite(device_address_sspin, HIGH);
    spiBus->endTransaction();
}

uint8_t SC16IS750::transfer(uint8_t byte) {
    uint8_t result = spiBus->transfer(byte);

#ifdef  SC16IS750_DEBUG_PRINT
    Serial.print("TX: ");
    printByteVerbose(byte);
    Serial.println();

    Serial.print("RX: ");
    printByteVerbose(result);
    Serial.println();
#endif

    return result;
}

void SC16IS750::writeBytes(uint8_t bytes[], uint8_t size) {
    spiBus->beginTransaction(settings);
    digitalWrite(device_address_sspin, LOW);

    transfer(channel << 1);

    for(uint8_t i = 0; i < size; i++) {
        transfer(bytes[i]);
    }

    digitalWrite(device_address_sspin, HIGH);
    spiBus->endTransaction();
}

int SC16IS750::available(void)
{
    return FIFOAvailableData();
}

int SC16IS750::read(void)
{
    return ReadByte();
}

size_t SC16IS750::write(uint8_t val)
{
    WriteByte(val);
}

uint8_t SC16IS750::ReadRegister(uint8_t reg_addr)
{
    uint8_t result;
    spiBus->beginTransaction(settings);
    digitalWrite(device_address_sspin, LOW);
    //delayMicroseconds(10);
#ifdef  SC16IS750_DEBUG_PRINT
    Serial.print("//: ");
    Serial.print(channel);
    Serial.print(" Read from ");
    Serial.println(reg_addr, HEX);
#endif

    // BIT   [8]: R/W (2=read, 0=write)
    // BIT [6:3]: Register ID
    // BIT [2:1]: Channel (01=A, 01=B)
    // BIT   [0]: Not Used
    transfer(BIT_7 | (reg_addr<<3) | (channel << 1));
    result = transfer(0xff);

    //delayMicroseconds(10);
    digitalWrite(device_address_sspin, HIGH);
    spiBus->endTransaction();

    return result;
}

void SC16IS750::WriteRegister(uint8_t reg_addr, uint8_t val)
{
    spiBus->beginTransaction(settings);
    digitalWrite(device_address_sspin, LOW);
    //delayMicroseconds(10);
#ifdef  SC16IS750_DEBUG_PRINT
    Serial.print("//: ");
    Serial.print(channel);
    Serial.print(" Write to ");
    Serial.print(reg_addr, HEX);
    Serial.print("; value: ");
    Serial.println(val, HEX);
#endif

    // BIT   [7]: R/W (1=read, 0=write)
    // BIT [6:3]: Register ID
    // BIT [2:1]: Channel (00=A, 01=B)
    // BIT   [0]: Not Used
    transfer((reg_addr<<3) | (channel << 1));
    transfer(val);

    //delayMicroseconds(10);
    digitalWrite(device_address_sspin, HIGH);
    spiBus->endTransaction();
}

int16_t SC16IS750::SetBaudrate(uint32_t baudrate) //return error of baudrate parts per thousand
{
    uint16_t divisor;
    uint8_t prescaler = 1;
    uint32_t actual_baudrate;
    int16_t error;
    uint8_t temp_lcr;

    divisor = (crystal_frequency/prescaler)/(baudrate*16);

    temp_lcr = ReadRegister(SC16IS750_REG_LCR);
    temp_lcr |= BIT_7;
    WriteRegister(SC16IS750_REG_LCR,temp_lcr);

    //write to DLL
    WriteRegister(SC16IS750_REG_DLL,(uint8_t)divisor);
    //write to DLH
    WriteRegister(SC16IS750_REG_DLH,(uint8_t)(divisor>>8));
    temp_lcr &= ~BIT_7;
    WriteRegister(SC16IS750_REG_LCR,temp_lcr);


    actual_baudrate = (crystal_frequency/prescaler)/(16*divisor);
    error = ((float)actual_baudrate-baudrate)*1000/baudrate;


#ifdef  SC16IS750_DEBUG_PRINT
    Serial.print("Desired baudrate: ");
    Serial.println(baudrate,DEC);
    Serial.print("Crystal Frequency: ");
    Serial.println(crystal_frequency);
    Serial.print("Calculated divisor: ");
    Serial.println(divisor,DEC);
    Serial.print("Actual baudrate: ");
    Serial.println(actual_baudrate,DEC);
    Serial.print("Baudrate error: ");
    Serial.println(error,DEC);
#endif

    return error;

}

void SC16IS750::SetLine(uint8_t data_length, uint8_t parity_select, uint8_t stop_length )
{
    uint8_t temp_lcr;
    temp_lcr = ReadRegister(SC16IS750_REG_LCR);
    temp_lcr &= 0xC0; //Clear the lower six bit of LCR (LCR[0] to LCR[5]
    switch (data_length) {            //data length settings
        case 5:
            break;
        case 6:
            temp_lcr |= 0x01;
            break;
        case 7:
            temp_lcr |= 0x02;
            break;
        case 8:
            temp_lcr |= 0x03;
            break;
        default:
            temp_lcr |= 0x03;
            break;
    }

    if ( stop_length == 2 ) {
        temp_lcr |= 0x04;
    }

    switch (parity_select) {            //parity selection length settings
        case 0:                         //no parity
             break;
        case 1:                         //odd parity
            temp_lcr |= 0x08;
            break;
        case 2:                         //even parity
            temp_lcr |= 0x18;
            break;
        case 3:                         //force '1' parity
            temp_lcr |= 0x03;
            break;
        case 4:                         //force '0' parity
            break;
        default:
            break;
    }

    WriteRegister(SC16IS750_REG_LCR,temp_lcr);
}

void SC16IS750::GPIOSetPinMode(uint8_t pin_number, uint8_t i_o)
{
    uint8_t temp_iodir;

    temp_iodir = ReadRegister(SC16IS750_REG_IODIR);
    if ( i_o == OUTPUT ) {
      temp_iodir |= (0x01 << pin_number);
    } else {
      temp_iodir &= (uint8_t)~(0x01 << pin_number);
    }

    WriteRegister(SC16IS750_REG_IODIR, temp_iodir);
    return;
}

void SC16IS750::GPIOSetPinState(uint8_t pin_number, uint8_t pin_state)
{
    uint8_t temp_iostate;

    temp_iostate = ReadRegister(SC16IS750_REG_IOSTATE);
    if ( pin_state == 1 ) {
      temp_iostate |= (0x01 << pin_number);
    } else {
      temp_iostate &= (uint8_t)~(0x01 << pin_number);
    }

    WriteRegister(SC16IS750_REG_IOSTATE, temp_iostate);
    return;
}


uint8_t SC16IS750::GPIOGetPinState(uint8_t pin_number)
{
    uint8_t temp_iostate;

    temp_iostate = ReadRegister(SC16IS750_REG_IOSTATE);
    if ( (temp_iostate & (0x01 << pin_number))== 0 ) {
      return 0;
    }
    return 1;
}

uint8_t SC16IS750::GPIOGetPortState(void)
{

    return ReadRegister(SC16IS750_REG_IOSTATE);

}

void SC16IS750::GPIOSetPortMode(uint8_t port_io)
{
    WriteRegister(SC16IS750_REG_IODIR, port_io);
    return;
}

void SC16IS750::GPIOSetPortState(uint8_t port_state)
{
    WriteRegister(SC16IS750_REG_IOSTATE, port_state);
    return;
}

void SC16IS750::SetPinInterrupt(uint8_t io_int_ena)
{
    WriteRegister(SC16IS750_REG_IOINTENA, io_int_ena);
    return;
}

void SC16IS750::ResetDevice(void)
{
    uint8_t reg;

    reg = ReadRegister(SC16IS750_REG_IOCONTROL);
    reg |= 0x08;
    WriteRegister(SC16IS750_REG_IOCONTROL, reg);

    return;
}

void SC16IS750::ModemPin(uint8_t gpio) //gpio == 0, gpio[7:4] are modem pins, gpio == 1 gpio[7:4] are gpios
{
    uint8_t temp_iocontrol;

    temp_iocontrol = ReadRegister(SC16IS750_REG_IOCONTROL);
    if ( gpio == 0 ) {
        temp_iocontrol |= 0x02;
    } else {
        temp_iocontrol &= 0xFD;
    }
    WriteRegister(SC16IS750_REG_IOCONTROL, temp_iocontrol);

    return;
}

void SC16IS750::GPIOLatch(uint8_t latch)
{
    uint8_t temp_iocontrol;

    temp_iocontrol = ReadRegister(SC16IS750_REG_IOCONTROL);
    if ( latch == 0 ) {
        temp_iocontrol &= 0xFE;
    } else {
        temp_iocontrol |= 0x01;
    }
    WriteRegister(SC16IS750_REG_IOCONTROL, temp_iocontrol);

    return;
}

void SC16IS750::InterruptControl(uint8_t int_ena)
{
    WriteRegister(SC16IS750_REG_IER, int_ena);
}

uint8_t SC16IS750::InterruptPendingTest(void)
{
    return (ReadRegister(SC16IS750_REG_IIR) & 0x01);
}

void SC16IS750::__isr(void)
{
    uint8_t irq_src;

    irq_src = ReadRegister(SC16IS750_REG_IIR);
    irq_src = (irq_src >> 1);
    irq_src &= 0x3F;

    switch (irq_src) {
        case 0x06:                  //Receiver Line Status Error
            break;
        case 0x0c:               //Receiver time-out interrupt
            break;
        case 0x04:               //RHR interrupt
            break;
        case 0x02:               //THR interrupt
            break;
        case 0x00:                  //modem interrupt;
            break;
        case 0x30:                  //input pin change of state
            break;
        case 0x10:                  //XOFF
            break;
        case 0x20:                  //CTS,RTS
            break;
        default:
            break;
    }
    return;
}

void SC16IS750::FIFOEnable(uint8_t fifo_enable)
{
    uint8_t temp_fcr = 0;

    if (fifo_enable == 0){
        temp_fcr &= 0xFE;
    } else {
        temp_fcr |= 0x01;
    }
    WriteRegister(SC16IS750_REG_FCR,temp_fcr);

    return;
}

void SC16IS750::FIFOReset()
{
     uint8_t temp_fcr = 0;

    temp_fcr |= 0x04;
    temp_fcr |= 0x02;
    WriteRegister(SC16IS750_REG_FCR,temp_fcr);

    return;
}

void SC16IS750::FIFOSetTriggerLevel(uint8_t rx_fifo, uint8_t length)
{
    uint8_t temp_reg;

    temp_reg = ReadRegister(SC16IS750_REG_MCR);
    temp_reg |= 0x04;
    WriteRegister(SC16IS750_REG_MCR,temp_reg); //SET MCR[2] to '1' to use TLR register or trigger level control in FCR register

    if (rx_fifo == 0) {
        WriteRegister(SC16IS750_REG_TLR, length<<4); //Tx FIFO trigger level setting
    } else {
        WriteRegister(SC16IS750_REG_TLR, length);    //Rx FIFO Trigger level setting
    }
    return;
}

void SC16IS750::sleep(void)
{
    uint8_t temp_reg = ReadRegister(SC16IS750_REG_IER);
    WriteRegister(SC16IS750_REG_IER, temp_reg | (1 << 4));
}

uint8_t SC16IS750::FIFOAvailableData(void)
{
   return ReadRegister(SC16IS750_REG_RXLVL);
//    return ReadRegister(SC16IS750_REG_LSR) & 0x01;
}

uint8_t SC16IS750::FIFOAvailableSpace(void)
{
   return ReadRegister(SC16IS750_REG_TXLVL);

}

void SC16IS750::WriteByte(uint8_t val)
{
    uint8_t bytes[] = {val};

    writeBytes(bytes, 1);
}

int SC16IS750::ReadByte(void)
{
    volatile uint8_t val;
    val = ReadRegister(SC16IS750_REG_RHR);
    return val;
}

void SC16IS750::EnableTransmit(uint8_t tx_enable)
{
    uint8_t temp_efcr;
    temp_efcr = ReadRegister(SC16IS750_REG_EFCR);
    if ( tx_enable == 0) {
        temp_efcr |= 0x04;
    } else {
        temp_efcr &= 0xFB;
    }
    WriteRegister(SC16IS750_REG_EFCR,temp_efcr);

    return;
}

uint8_t SC16IS750::ping()
{
    int result = 1;

    spiBus->beginTransaction(settings);
    digitalWrite(device_address_sspin, LOW);
    WriteRegister(SC16IS750_REG_SPR,0x55);
    byte firstResult = ReadRegister(SC16IS750_REG_SPR);
    if (firstResult !=0x55) {
        result = 0;
    }
    WriteRegister(SC16IS750_REG_SPR,0xAA);
    byte secondResult = ReadRegister(SC16IS750_REG_SPR);
    if (secondResult !=0xAA) {
        result = 0;
    }

    digitalWrite(device_address_sspin, HIGH);
    spiBus->endTransaction();
    return result;

}
/*
void SC16IS750::setTimeout(uint32_t time_out)
{
    timeout = time_out;
}

size_t SC16IS750::readBytes(char *buffer, size_t length)
{
    size_t count=0;
    int16_t tmp;

    while (count < length) {
        tmp = readwithtimeout();
        if (tmp < 0) {
            break;
        }
        *buffer++ = (char)tmp;
        count++;
    }

    return count;
}

int16_t SC16IS750::readwithtimeout()
{
  int16_t tmp;
  uint32_t time_stamp;
  time_stamp = millis();
  do {
    tmp = read();
    if (tmp >= 0) return tmp;
  } while(millis() - time_stamp < timeout);
  return -1;     // -1 indicates timeout
}
*/

void SC16IS750::flush()
{
    uint8_t tmp_lsr;

    spiBus->beginTransaction(settings);
    digitalWrite(device_address_sspin, LOW);

    do {
        tmp_lsr = ReadRegister(SC16IS750_REG_LSR);
    } while ((tmp_lsr&0x20) ==0);

    digitalWrite(device_address_sspin, HIGH);
    spiBus->endTransaction();

}

int SC16IS750:: peek()
{
    if ( peek_flag == 0 ) {
        peek_buf =ReadByte();
        if (  peek_buf >= 0 ) {
            peek_flag = 1;
        }
    }

    return peek_buf;
}

void SC16IS750::printByteVerbose(uint8_t reading) {
    if(reading < pow(2, 4)) {
        Serial.print("0");
    }
    Serial.print(reading, HEX);
    Serial.print(" ");
    for (uint8_t i = 1; i < 8; i++) {
        if(reading < pow(2, i)) {
            Serial.print(B0);
        }
    }
    Serial.print(reading, BIN);
    Serial.print(" ");
    Serial.print((int)reading);
}

void SC16IS750::printRegister(uint8_t registerId) {
    Serial.print(registerId, HEX);
    Serial.print(": 0x");
    uint8_t reading = ReadRegister(registerId);
    printByteVerbose(reading);
    Serial.println();
}

void SC16IS750::printRegisters(uint8_t registers[], uint8_t size) {
    for(uint8_t i = 0; i < size/sizeof(registers[0]); i++) {
        printRegister(registers[i]);
    }
}

void SC16IS750::printAllRegisters(bool general, bool special, bool enhanced) {
    uint8_t generalRegisters[] = {
        SC16IS750_REG_RHR,
        SC16IS750_REG_IER,
        SC16IS750_REG_IIR,
        SC16IS750_REG_LCR,
        SC16IS750_REG_MCR,
        SC16IS750_REG_LSR,
        SC16IS750_REG_MSR,
        SC16IS750_REG_SPR,
        SC16IS750_REG_TXLVL,
        SC16IS750_REG_RXLVL,
        SC16IS750_REG_IODIR,
        SC16IS750_REG_IOSTATE,
        SC16IS750_REG_IOINTENA,
        SC16IS750_REG_IOCONTROL,
        SC16IS750_REG_EFCR,
    };
    uint8_t specialRegisters[] = {
        SC16IS750_REG_DLL,
        SC16IS750_REG_DLH,
    };
    uint8_t enhancedRegisters[] = {
        SC16IS750_REG_EFR,
        SC16IS750_REG_XON2,
        SC16IS750_REG_XON2,
        SC16IS750_REG_XOFF1,
        SC16IS750_REG_XOFF2,
    };
    uint8_t temp_lcr = ReadRegister(SC16IS750_REG_LCR);

    if (general) {
        Serial.println("General Registers:");
        printRegisters(generalRegisters, sizeof(generalRegisters));
    }

    if (special) {
        Serial.println("Special Registers:");
        WriteRegister(SC16IS750_REG_LCR, temp_lcr | 0x80);
        printRegisters(specialRegisters, sizeof(specialRegisters));
    }

    if (enhanced) {
        Serial.println("Enhanced Registers:");
        WriteRegister(SC16IS750_REG_LCR, 0xbf);
        printRegisters(enhancedRegisters, sizeof(enhancedRegisters));
    }

    if(special || enhanced) {
        WriteRegister(SC16IS750_REG_LCR, temp_lcr);
    }
}
