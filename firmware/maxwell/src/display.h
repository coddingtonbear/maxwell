#pragma once

#include <Arduino.h>
#include "U8g2lib.h"
#include "menu.h"

#define SMALL_DISPLAY_FONT u8g2_font_helvB12_tr
#define SMALL_DISPLAY_FONT_HEIGHT 12
#define LARGE_DISPLAY_FONT u8g2_font_helvB24_tr
#define LARGE_DISPLAY_FONT_HEIGHT 24
#define MESSAGE_DISPLAY_FONT u8g2_font_8x13B_tr
#define MESSAGE_DISPLAY_FONT_HEIGHT 10

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64

#define MENU_EXEC_NOTICE_TIMEOUT 100
#define MENU_TIMEOUT 300000

#define FONT_HEIGHT 14

#define ALERT_COUNT 10
#define ALERT_DURATION 10000;

#define STATUS_PHASE_COUNT 8
#define STATUS_PHASE_DURATION 500

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
        void setBacklightBrightness(uint8_t);
        uint8_t getBacklightBrightness();

        void addAlert(String message);
        String getAlert();
        void redisplayAlert();

        bool backlightEnabled();
        void enableBacklight(bool _enabled=true, bool save=true);
        void toggleBacklight();

        void menuKeepalive();
        void up();
        void down();
        void in();
        void out();

        bool timeoutEnabled();
        void enableTimeout(bool);
        void setActionTimeout();

    protected:
        void wake();
        void applyBacklightBrightness(uint8_t);

        MenuList* getCurrentMenu();

        uint8_t backlightBrightness = 255;

        bool displayingAlertNow = false;
        unsigned long currentAlertEnd = 0;
        uint8_t alertCount = 0;
        String alert[ALERT_COUNT];

        bool enabled = true;
        bool autosleep = false;
        bool sleeping = false;
        bool backlightOn = false;
        bool timeout = true;

        uint8_t menuDepth = 0;
        uint8_t menuPosition[10];

        void showMenu();

        uint8_t statusPhase = 0;
        uint8_t statusPhaseCount = STATUS_PHASE_COUNT;
        unsigned long statusPhaseEnds = 0;

        unsigned long showMenuUntil = 0;
        unsigned long showMenuExecNoticeUntil = 0;

        MenuList* mainMenu;
};

extern DisplayManager Display;
