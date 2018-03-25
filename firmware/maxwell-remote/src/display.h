#pragma once

#include <Arduino.h>
#include "menu.h"

#define DISPLAY_ADDRESS 0x3C
#define DISPLAY_ON_ PB4

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64

#define MENU_EXEC_NOTICE_TIMEOUT 500
#define MENU_TIMEOUT 5000

#define FONT_WIDTH 6
#define FONT_HEIGHT 8

class DisplayManager {
    public:
        DisplayManager(MenuList*);

        void begin();
        void refresh();

        void menuKeepalive();
        void up();
        void down();
        void in();
        void out();

    //protected:
        struct DisplayBounds {
            int x, y, w, h;
        };

        MenuList* getCurrentMenu();

        uint8_t menuDepth = 0;
        uint8_t menuPosition[10];

        void showMenu();
        void executeMenuCommand(void(*)());
        DisplayBounds getTextBounds(String);

        unsigned long showMenuUntil = 0;
        unsigned long showMenuExecNoticeUntil = 0;

        MenuList* mainMenu;
};

extern DisplayManager Display;
