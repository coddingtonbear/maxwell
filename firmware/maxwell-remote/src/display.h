#pragma once

#include <Arduino.h>
#include "menu.h"

#define DISPLAY_ADDRESS 0x3C
#define DISPLAY_ON_ PB4

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64

#define MENU_EXEC_NOTICE_TIMEOUT 100
#define MENU_TIMEOUT 5000

#define FONT_HEIGHT 14

#define STATUS_PHASE_DURATION 3000
#define ALERT_DURATION 10000;

class DisplayManager {
    public:
        DisplayManager(MenuList*);

        void begin();
        void enable(bool _enabled=true);
        void refresh();

        void setContrast(uint8_t);
        void setAutosleep(bool _enabled=true);
        void addAlert(String message);
        void redisplayAlert();

        void menuKeepalive();
        void up();
        void down();
        void in();
        void out();

    protected:
        struct DisplayBounds {
            int x, y, w, h;
        };

        void sleep();
        void wake();

        MenuList* getCurrentMenu();

        char currentAlert[255];
        uint32_t currentAlertEnd = 0;

        bool enabled = true;
        bool autosleep = false;
        bool sleeping = false;

        uint8_t menuDepth = 0;
        uint8_t menuPosition[10];

        void showMenu();
        void executeMenuCommand(void(*)());
        DisplayBounds getTextBounds(String);

        uint8_t statusPhase = 0;
        uint8_t statusPhaseCount = 2;
        unsigned long statusPhaseEnds = 0;

        unsigned long showMenuUntil = 0;
        unsigned long showMenuExecNoticeUntil = 0;

        MenuList* mainMenu;
};

extern DisplayManager Display;
