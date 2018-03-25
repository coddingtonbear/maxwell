#pragma once

#include <Arduino.h>
#undef min
#undef max

#include <functional>

#define MAX_MENU_LENGTH 20

class MenuList;

class MenuItem {
    public:
        MenuItem(String, MenuList*);
       //MenuItem(String, void(*function)());
       MenuItem(String, std::function<void()>);

        String name;
        MenuList* subMenu;
        //void(*function)();
        std::function<void()> function;
};

class MenuList {
    public:
        MenuList(MenuItem[], uint8_t);

        MenuItem* items;
        uint8_t length = -1;
};

extern MenuList mainMenu;
