#pragma once

#include <Arduino.h>
#undef min
#undef max

#include <vector>
#include <functional>

#define MAX_MENU_LENGTH 20

class MenuList;

class MenuItem {
    public:
        MenuItem(String, MenuList*);
        MenuItem(std::function<String()>, MenuList*);
        MenuItem(String, std::function<void()>);
        MenuItem(std::function<String()>, std::function<void()>);
        MenuItem(std::function<String()>);

        String name;
        std::function<String()> nameFunction;
        MenuList* subMenu;
        std::function<void()> function;
};

class MenuList {
    public:
        MenuList(MenuItem* menuItems, uint8_t length);
        MenuItem* items;
        uint8_t length;
};

extern MenuList mainMenu;
