#pragma once

#include <Arduino.h>
#undef min
#undef max

#define MAX_MENU_LENGTH 20

class MenuList;

class MenuItem {
    public:
        MenuItem(String, MenuList*);
        MenuItem(String(*)(), MenuList*);
        MenuItem(String, void(*)());
        MenuItem(String(*)(), void(*)());
        MenuItem(String(*)());

        String name;
        String (*nameFunction)();
        MenuList* subMenu;
        void (*function)();
};

class MenuList {
    public:
        MenuList(MenuItem* menuItems, uint8_t length);
        MenuItem* items;
        uint8_t length;
};

extern MenuList mainMenu;
