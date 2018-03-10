#pragma once

#define DISPLAY_ADDRESS 0x3C
#define DISPLAY_ON_ PB4

class DisplayManager {
    public:
        DisplayManager();

        void begin();
        void refresh();
};

extern DisplayManager Display;
