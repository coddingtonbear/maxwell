#pragma once 

#include <stdint.h>


template <typename T, int size>
class RollingAverage{
    public:
        RollingAverage();

        void addMeasurement(T value);
        T getValue();
        uint32_t getSize();

    private:
        T measurements[size];
        bool initialized = false;
        int32_t idx = 0;
};

#include "RollingAverage_Impl.h"
