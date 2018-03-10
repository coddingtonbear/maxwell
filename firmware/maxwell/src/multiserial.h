#pragma once

#include <Arduino.h>

class MultiSerial : public Stream
{
    public:
        MultiSerial();

        void addInterface(HardwareSerial*);
        void begin(unsigned long, uint8_t);
        void begin(unsigned long b) {begin(b, SERIAL_8N1);};
        void begin() {begin(baud, mode);};
        void end();

        virtual int available();
        virtual int peek();
        virtual int read();
        virtual int availableForWrite();
        virtual void flush();

        virtual size_t write(uint8_t);
        inline size_t write(unsigned long n) {return write((uint8_t)n);};
        inline size_t write(long n) {return write((uint8_t)n);};
        inline size_t write(unsigned int n) {return write((uint8_t)n);};
        inline size_t write(int n) {return write((uint8_t)n);};
        using Print::write;
        operator bool() {return true;};

    private:
        unsigned long baud;
        uint8_t mode;

        HardwareSerial* interfaces[5];
        uint8_t interfaceCount = 0;
};
