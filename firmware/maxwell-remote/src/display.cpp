#include <Adafruit_SSD1306.h>
#include <Roboto_Regular8pt7b.h>
#include <Roboto_Regular30pt7b.h>

#include "display.h"
#include "status.h"
#include "can_message_ids.h"
#include "menu.h"
#include "main.h"

extern Adafruit_SSD1306 display(-1);

DisplayManager::DisplayManager(MenuList* menuList) {
    mainMenu = menuList;

    pinMode(DISPLAY_ON_, OUTPUT);
    digitalWrite(DISPLAY_ON_, LOW);
}

void DisplayManager::enable(bool _enabled) {
    if(_enabled && !enabled) {
        digitalWrite(DISPLAY_ON_, LOW);
    } if(!_enabled && enabled) {
        digitalWrite(DISPLAY_ON_, HIGH);
    }
    enabled = _enabled;
}

void DisplayManager::menuKeepalive() {
    showMenuUntil = millis() + MENU_TIMEOUT;
}

void DisplayManager::setContrast(uint8_t value) {
    display.ssd1306_command(SSD1306_SETCONTRAST);
    display.ssd1306_command(value);
}

void DisplayManager::setAutosleep(bool _enabled) {
    autosleep = _enabled;
    sleeping = false;
}

void DisplayManager::sleep() {
    display.ssd1306_command(SSD1306_DISPLAYOFF);
    sleeping = true;
}

void DisplayManager::wake() {
    //display.ssd1306_command(SSD1306_DISPLAYON);
    enable(false);
    delay(50);
    enable(true);
    delay(50);
    begin();
    sleeping = false;
}

void DisplayManager::up() {
    if(showMenuUntil < millis()) {
        menuKeepalive();
        return;
    }

    MenuList* currentMenu = getCurrentMenu();

    menuKeepalive();

    if(menuPosition[menuDepth] > 0) {
        menuPosition[menuDepth]--;
    } else {
        menuPosition[menuDepth] = currentMenu->length - 1;
    }
}

void DisplayManager::down() {
    if(showMenuUntil < millis()) {
        menuKeepalive();
        return;
    }

    MenuList* currentMenu = getCurrentMenu();

    menuKeepalive();

    menuPosition[menuDepth]++;
    if(menuPosition[menuDepth] >= currentMenu->length) {
        menuPosition[menuDepth] = 0;
    }
}

void DisplayManager::in() {
    if(showMenuUntil < millis()) {
        menuKeepalive();
        return;
    }

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
    if(showMenuUntil < millis()) {
        menuKeepalive();
        return;
    }

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
    digitalWrite(DISPLAY_ON_, LOW);
    delay(100);
    display.begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADDRESS);
    display.clearDisplay();
    display.display();

    display.setCursor(0, 0);
    display.setTextColor(WHITE);
    display.setTextWrap(false);
    display.setRotation(2);
    setContrast(0xCF);
    display.display();

    display.clearDisplay();
    display.display();
}

void DisplayManager::refresh() {
    DisplayManager::DisplayBounds bounds;
    display.clearDisplay();
    display.setFont(&Roboto_Regular8pt7b);

    /* Display Menu or Speed */
    if(showMenuUntil > millis()) {
        if(sleeping) {
            wake();
        }
        showMenu();
    } else {
        if(autosleep && !sleeping) {
            sleep();
        }
        String velocity = String(
            getDoubleStatusParameter(
                CAN_VELOCITY
            ),
            1
        );

        display.setFont(&Roboto_Regular30pt7b);
        display.setCursor(0, DISPLAY_HEIGHT - 1 - 17);
        bounds = getTextBounds(velocity);
        display.setCursor(
            (DISPLAY_WIDTH - bounds.w - 1) / 2,
            DISPLAY_HEIGHT - 1 - 17
        );
        display.println(velocity);
    }

    /* Display Status Information */
    display.setFont(&Roboto_Regular8pt7b);
    display.setCursor(0, DISPLAY_HEIGHT - 1);
    uint32 mainMcStatus = getStatusMainMc();
    uint8_t chargingStatus = getChargingStatus();
    if(mainMcStatus == CAN_MAIN_MC_WAKE) {
        String voltage = String(
            getDoubleStatusParameter(
                CAN_VOLTAGE_BATTERY
            ),
            2
        );
        voltage += "V";
        if(chargingStatus != CHARGING_STATUS_SHUTDOWN) {
            voltage += "*";
        }
        if(chargingStatus == CHARGING_STATUS_FULLY_CHARGED) {
            voltage += "*";
        }
        bounds = getTextBounds(voltage);
        display.println(voltage);

        String amps = String(
            getDoubleStatusParameter(
                CAN_AMPS_CURRENT
            ),
            2
        );
        amps += "A";
        bounds = getTextBounds(amps);
        display.setCursor(
            DISPLAY_WIDTH - bounds.w - 1,
            DISPLAY_HEIGHT - 1
        );
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
        display.setFont(&Roboto_Regular30pt7b);
        display.setCursor(0, DISPLAY_HEIGHT - 1 - 17);

        String okMessage = "OK";

        DisplayManager::DisplayBounds bounds;
        bounds = getTextBounds(okMessage);
        display.setCursor(
            (DISPLAY_WIDTH - bounds.w - 1) / 2,
            DISPLAY_HEIGHT - 1 - 17
        );
        display.println(okMessage);

        return;
    }
    display.setFont(&Roboto_Regular8pt7b);

    int startingIndex = menuPosition[menuDepth] - 1;
    MenuList* currMenu = getCurrentMenu();

    uint16_t rowHeight = 16;
    uint16_t cursorPosition = 12;
    uint8_t j = 0;
    for(
        int8_t i = startingIndex;
        i < (int8_t)currMenu->length && j < 3;
        i++
    ) {
        display.setCursor(0, cursorPosition);  // X
        cursorPosition += rowHeight;

        if(i < 0) {
            display.println();
            j++;
            continue;
        }
        if(i == menuPosition[menuDepth]) {
            display.print("[");
        }
        display.print(currMenu->items[i].name);
        if(i == menuPosition[menuDepth]) {
            display.print("]");
        }
        if(currMenu->items[i].function == NULL) {
            display.print(" >");
        }
        display.println();
        j++;
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

