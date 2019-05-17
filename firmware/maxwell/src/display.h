#pragma once

#include <Arduino.h>
#include "U8g2lib.h"
#include "menu.h"

#define SMALL_DISPLAY_FONT u8g2_font_helvB12_tr
#define SMALL_DISPLAY_FONT_HEIGHT 12
#define LARGE_DISPLAY_FONT u8g2_font_helvB24_tr
#define LARGE_DISPLAY_FONT_HEIGHT 24

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64

#define MENU_EXEC_NOTICE_TIMEOUT 100
#define MENU_TIMEOUT 15000

#define FONT_HEIGHT 14

#define STATUS_PHASE_DURATION 600
#define ALERT_DURATION 10000;

#define LONG_PRESS_INTERVAL 500

namespace display {
    void init();
    void loop();
};

class DisplayManager {
    public:
        DisplayManager(MenuList*);

        void begin();
        void enable(bool _enabled=true);
        void refresh();
        void sleep();

        void setContrast(uint8_t);
        void setAutosleep(bool _enabled=true);
        void addAlert(String message);
        void redisplayAlert();

        void enableBacklight(bool _enabled=true);
        void toggleBacklight();

        void menuKeepalive();
        void up();
        void down();
        void in();
        void out();

        void enableTimeout(bool);
        void setActionTimeout();

    protected:
        void wake();

        MenuList* getCurrentMenu();

        char currentAlert[255];
        uint32_t currentAlertEnd = 0;

        bool enabled = true;
        bool autosleep = false;
        bool sleeping = false;
        bool backlightOn = false;
        bool timeout = true;

        uint8_t menuDepth = 0;
        uint8_t menuPosition[10];

        void showMenu();
        void executeMenuCommand(void(*)());

        uint8_t statusPhase = 0;
        uint8_t statusPhaseCount = 10;
        unsigned long statusPhaseEnds = 0;

        unsigned long showMenuUntil = 0;
        unsigned long showMenuExecNoticeUntil = 0;

        MenuList* mainMenu;
};

extern DisplayManager Display;
