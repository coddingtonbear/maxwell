#pragma once

#include <Arduino.h>
#undef min
#undef max

#define MAX_MENU_LENGTH 20

class MenuList;

class MenuItem {
    public:
        // Name w/ Action
        MenuItem(String, MenuList*);
        // Dynamic Name w/ Menu
        MenuItem(String(*)(), MenuList*);
        // Name w/ Action
        MenuItem(String, void(*)());
        // Dynamic Name w/ Action
        MenuItem(String(*)(), void(*)());
        // Display-only
        MenuItem(String(*)());
        // Toggle
        MenuItem(String, bool(*)(), void(*)(), void(*)());

        String getName();
        bool hasAction();
        bool hasSubmenu();
        void runAction();

        String name;
        String (*nameFunction)();
        MenuList* subMenu;
        void (*function)();

        bool(*statusFunction)();
        void(*enableFunction)();
        void(*disableFunction)();
};

class MenuList {
    public:
        MenuList(MenuItem* menuItems, uint8_t length);
        MenuItem* items;
        uint8_t length;
};

extern MenuList mainMenu;
