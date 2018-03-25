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

void DisplayManager::menuKeepalive() {
    showMenuUntil = millis() + MENU_TIMEOUT;
}

void DisplayManager::up() {
    MenuList* currentMenu = getCurrentMenu();

    menuKeepalive();

    if(menuPosition[menuDepth] > 0) {
        menuPosition[menuDepth]--;
    } else {
        menuPosition[menuDepth] = currentMenu->length - 1;
    }
}

void DisplayManager::down() {
    MenuList* currentMenu = getCurrentMenu();

    menuKeepalive();

    menuPosition[menuDepth]++;
    if(menuPosition[menuDepth] >= currentMenu->length) {
        menuPosition[menuDepth] = 0;
    }
}

void DisplayManager::in() {
    MenuList* currentMenu = getCurrentMenu();
    MenuItem selectedItem = currentMenu->items[menuPosition[menuDepth]];

    menuKeepalive();

    if(selectedItem.function != NULL) {
        showMenuExecNoticeUntil = millis() + MENU_EXEC_NOTICE_TIMEOUT;
        selectedItem.function();
    } else {
        menuDepth++;
    }
}

void DisplayManager::out() {
    MenuList* currentMenu = getCurrentMenu();

    menuKeepalive();

    menuPosition[menuDepth] = 0;

    if(menuDepth == 0) {
        // Hide the menu
        showMenuUntil = 0;
    }  else if(menuDepth > 0) {
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
    display.display();
}

void DisplayManager::refresh() {
    display.clearDisplay();

    /* Display Menu or Power */
    display.setCursor(0, 16);
    if(showMenuUntil > millis()) {
        showMenu();
    } else {
        String velocity = String(
            getDoubleStatusParameter(
                CAN_VELOCITY
            ),
            1
        );

        display.setTextSize(6);
        display.println(velocity);
    }

    /* Display Status Information */
    display.setTextSize(2);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(0, 0);
    DisplayManager::DisplayBounds bounds;
    uint32 mainMcStatus = getStatusMainMc();
    if(mainMcStatus == CAN_MAIN_MC_WAKE) {
        String voltage = String(
            getDoubleStatusParameter(
                CAN_VOLTAGE_BATTERY
            ),
            2
        );
        bounds = getTextBounds(voltage);
        display.println(voltage);

        String amps = String(
            getDoubleStatusParameter(
                CAN_AMPS_CURRENT
            ),
            2
        );
        bounds = getTextBounds(amps);
        display.setCursor(DISPLAY_WIDTH - bounds.w, 0);
        display.println(amps);
    } else {
        switch(mainMcStatus) {
            case CAN_MAIN_MC_SLEEP:
                display.println("<SLEEP>");
                break;
            case CAN_MAIN_MC_FLASH_BEGIN:
                display.println("<FLASH>");
                break;
            default:
                display.println("");
                break;
        }
    }

    display.display();
}

MenuList* DisplayManager::getCurrentMenu() {
    MenuList* currMenu = mainMenu;

    for(uint8_t i = 0; i < menuDepth; i++) {
        currMenu = currMenu->items[menuPosition[i]].subMenu;
    }

    return currMenu;
}

void DisplayManager::showMenu() {
    if(millis() < showMenuExecNoticeUntil) {
        display.setTextSize(6);
        display.println("OK");

        return;
    }

    display.setTextSize(2);
    int startingIndex = menuPosition[menuDepth] - 1;

    MenuList* currMenu = getCurrentMenu();


    for(int8_t i = startingIndex; i < currMenu->length; i++) {
        //Output.print(i);
        //Output.print("/");
        //Output.println(currMenu->length);
        display.setTextColor(WHITE, BLACK);
        if(i < 0) {
            display.println();
            continue;
        }
        if(i == menuPosition[menuDepth]) {
            display.setTextColor(BLACK, WHITE);
        }

        display.println(currMenu->items[i].name);
    }
}

void DisplayManager::executeMenuCommand(void(*function)()) {
    function();
}

DisplayManager::DisplayBounds DisplayManager::getTextBounds(String text) {
    int16_t x, y;
    uint16_t w, h;
    static DisplayManager::DisplayBounds textBounds;

    char *txt = const_cast<char*>(text.c_str());

    display.getTextBounds(
        txt,
        0, 0,
        &x, &y, &w, &h
    );
    textBounds.x = x;
    textBounds.y = y;
    textBounds.w = w;
    textBounds.h = h;

    return textBounds;
}

DisplayManager Display(&mainMenu);

