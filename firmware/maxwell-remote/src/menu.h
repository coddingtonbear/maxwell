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
       //MenuItem(String, void(*function)());
       MenuItem(String, std::function<void()>);

        String name;
        MenuList* subMenu;
        //void(*function)();
        std::function<void()> function;
};

class MenuList {
    public:
        MenuList(std::vector<MenuItem>);
        std::vector<MenuItem> items;
};

extern MenuList mainMenu;
