#pragma once

#include <stdint.h>

#include "RollingAverage.h"

template <typename T, int size>
RollingAverage<T, size>::RollingAverage() {
}

template <typename T, int size>
void RollingAverage<T, size>::addMeasurement(T value) {
    if(! initialized) {
        for(uint32_t i = 0; i < getSize(); i++) {
            measurements[i] = value;
        }
        initialized = true;
    } else {
        measurements[idx] = value;

        idx++;
        if(idx >= getSize()) {
            idx = 0;
        }
    }
}

template <typename T, int size>
uint32_t RollingAverage<T, size>::getSize() {
    return (sizeof(measurements) / sizeof(measurements[0]));
}

template <typename T, int size>
T RollingAverage<T, size>::getValue() {
    T value = 0;

    for(uint32_t i = 0; i < getSize(); i++) {
        value += measurements[i];
    }

    return value / getSize();
}
