#include <Adafruit_SSD1306.h>
#include "display.h"
#include "status.h"
#include "can_message_ids.h"
#include "menu.h"

#include "main.h"

extern Adafruit_SSD1306 display(-1);

DisplayManager::DisplayManager(MenuList* menuList) {
    mainMenu = menuList;
}

void DisplayManager::up() {
    MenuList* currentMenu = getCurrentMenu();

    if(menuPosition[menuDepth] > 0) {
        menuPosition[menuDepth]--;
    } else {
        menuPosition[menuDepth] = currentMenu->length - 1;
    }
}

void DisplayManager::down() {
    MenuList* currentMenu = getCurrentMenu();

    menuPosition[menuDepth]++;
    if(menuPosition[menuDepth] >= currentMenu->length) {
        menuPosition[menuDepth] = 0;
    }
}

void DisplayManager::in() {
    MenuList* currentMenu = getCurrentMenu();
    MenuItem selectedItem = currentMenu->items[menuPosition[menuDepth]];

    if(selectedItem.function != NULL) {
        (*selectedItem.function)();
    } else {
        menuDepth++;
    }
}

void DisplayManager::out() {
    MenuList* currentMenu = getCurrentMenu();

    if(menuDepth > 0) {
        menuDepth--;
    } else {
        menuDepth = 0;
    }
}

void DisplayManager::begin() {
    display.begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADDRESS);
    display.clearDisplay();
    display.display();

    display.setTextSize(2);
    display.setCursor(0, 0);
    display.setTextColor(WHITE);
    display.setTextWrap(true);
    display.display();

    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("0123456789012345");
    display.display();
}

void DisplayManager::refresh() {
}


DisplayManager Display;
