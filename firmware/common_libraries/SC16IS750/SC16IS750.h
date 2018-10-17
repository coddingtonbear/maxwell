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

#pragma once

#include "Arduino.h"

//Device Address

//A:VDD
//B:GND
//C:SCL
//D:SDA

#define BIT_0 (0x01)
#define BIT_1 (0x02)
#define BIT_2 (0x04)
#define BIT_3 (0x08)
#define BIT_4 (0x10)
#define BIT_5 (0x20)
#define BIT_6 (0x40)
#define BIT_7 (0x80)

#define     SC16IS750_ADDRESS_AA     (0X90)
#define     SC16IS750_ADDRESS_AB     (0X92)
#define     SC16IS750_ADDRESS_AC     (0X94)
#define     SC16IS750_ADDRESS_AD     (0X96)
#define     SC16IS750_ADDRESS_BA     (0X98)
#define     SC16IS750_ADDRESS_BB     (0X9A)
#define     SC16IS750_ADDRESS_BC     (0X9C)
#define     SC16IS750_ADDRESS_BD     (0X9E)
#define     SC16IS750_ADDRESS_CA     (0XA0)
#define     SC16IS750_ADDRESS_CB     (0XA2)
#define     SC16IS750_ADDRESS_CC     (0XA4)
#define     SC16IS750_ADDRESS_CD     (0XA6)
#define     SC16IS750_ADDRESS_DA     (0XA8)
#define     SC16IS750_ADDRESS_DB     (0XAA)
#define     SC16IS750_ADDRESS_DC     (0XAC)
#define     SC16IS750_ADDRESS_DD     (0XAE)

//General Registers
#define     SC16IS750_REG_RHR        (0x00)
#define     SC16IS750_REG_THR        (0X00)
#define     SC16IS750_REG_IER        (0X01)
#define     SC16IS750_REG_FCR        (0X02)
#define     SC16IS750_REG_IIR        (0X02)
#define     SC16IS750_REG_LCR        (0X03)
#define     SC16IS750_REG_MCR        (0X04)
#define     SC16IS750_REG_LSR        (0X05)
#define     SC16IS750_REG_MSR        (0X06)
#define     SC16IS750_REG_SPR        (0X07)
#define     SC16IS750_REG_TCR        (0X06)
#define     SC16IS750_REG_TLR        (0X07)
#define     SC16IS750_REG_TXLVL      (0X08)
#define     SC16IS750_REG_RXLVL      (0X09)
#define     SC16IS750_REG_IODIR      (0X0A)
#define     SC16IS750_REG_IOSTATE    (0X0B)
#define     SC16IS750_REG_IOINTENA   (0X0C)
#define     SC16IS750_REG_IOCONTROL  (0X0E)
#define     SC16IS750_REG_EFCR       (0X0F)

//Special Registers
#define     SC16IS750_REG_DLL        (0x00)
#define     SC16IS750_REG_DLH        (0X01)

//Enhanced Registers
#define     SC16IS750_REG_EFR        (0X02)
#define     SC16IS750_REG_XON1       (0X04)
#define     SC16IS750_REG_XON2       (0X05)
#define     SC16IS750_REG_XOFF1      (0X06)
#define     SC16IS750_REG_XOFF2      (0X07)

//Channels
#define     SC16IS750_CHAN_A         (0x00)
#define     SC16IS750_CHAN_B         (0x01)

//
#define     SC16IS750_INT_CTS        (0X80)
#define     SC16IS750_INT_RTS        (0X40)
#define     SC16IS750_INT_XOFF       (0X20)
#define     SC16IS750_INT_SLEEP      (0X10)
#define     SC16IS750_INT_MODEM      (0X08)
#define     SC16IS750_INT_LINE       (0X04)
#define     SC16IS750_INT_THR        (0X02)
#define     SC16IS750_INT_RHR        (0X01)

//Application Related 

//#define     SC16IS750_DEBUG_PRINT   (0)
#define     SC16IS750_PROTOCOL_I2C  (0)
#define     SC16IS750_PROTOCOL_SPI  (1)


#define Debug Serial


class SC16IS750 : public Stream
{ 
    public:
        SC16IS750(
            uint8_t addr = SC16IS750_ADDRESS_AD,
            uint8_t chan = SC16IS750_CHAN_A,
            unsigned long crystal_frequency = 14745600UL
        );
        void setSpiBus(SPIClass*);
        void begin(uint32_t baud=0, bool reset=false);
        int read();
        size_t write(uint8_t val);
        int available();
		uint8_t ping();
	//	void setTimeout(uint32_t);
	//	size_t readBytes(char *buffer, size_t length);
		int peek();
		void flush();
		uint8_t GPIOGetPortState(void);
		uint8_t InterruptPendingTest(void);
		void    SetPinInterrupt(uint8_t io_int_ena);
		void    InterruptControl(uint8_t int_ena);
		void    ModemPin(uint8_t gpio); //gpio == 0, gpio[7:4] are modem pins, gpio == 1 gpio[7:4] are gpios
		void    GPIOLatch(uint8_t latch);
        uint8_t ReadRegister(uint8_t reg_addr);
        void    WriteRegister(uint8_t reg_addr, uint8_t val);
        void    printAllRegisters(bool general=true, bool special=true, bool enhanced=false);
        void    printRegister(uint8_t registerId);
        void    printRegisters(uint8_t registers[], uint8_t size);

        void    writeBytes(uint8_t bytes[], uint8_t size);
        void    GPIOSetPinMode(uint8_t pin_number, uint8_t i_o);
        void    GPIOSetPinState(uint8_t pin_number, uint8_t pin_state);
        void    FIFOReset();
        void    sleep();

        uint8_t gpioState = 0;
        
    
    private:
        SPIClass* spiBus;
        unsigned long crystal_frequency;
        uint32_t _baud;
        uint8_t channel;
        uint8_t device_address_sspin;
        uint8_t protocol;
        uint8_t transfer(uint8_t byte);
        void    printByteVerbose(uint8_t byte);
        void    BeginTransaction();
        void    EndTransaction();
	//	uint32_t timeout;
        int16_t SetBaudrate(uint32_t baudrate);
        void    SetLine(uint8_t data_length, uint8_t parity_select, uint8_t stop_length );
		
        uint8_t GPIOGetPinState(uint8_t pin_number);
        void    GPIOSetPortMode(uint8_t port_io);
        void    GPIOSetPortState(uint8_t port_state);
        void    ResetDevice(void);
        
        void    __isr(void);
        void    FIFOEnable(uint8_t fifo_enable);
        void    FIFOSetTriggerLevel(uint8_t rx_fifo, uint8_t length);
        uint8_t FIFOAvailableData(void);
        uint8_t FIFOAvailableSpace(void);
        void    WriteByte(uint8_t val);
        int     ReadByte(void);
        void    EnableTransmit(uint8_t tx_enable);
	//	int16_t readwithtimeout();
		int 	peek_buf;
		uint8_t peek_flag;

#ifdef  SC16IS750_DEBUG_PRINT
        bool printedPreamble = false;	
        bool outbound = true;
#endif
};
