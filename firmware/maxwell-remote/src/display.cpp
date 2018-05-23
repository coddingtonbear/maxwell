#include <Adafruit_SSD1306.h>
#include <Roboto_Regular8pt7b.h>
#include <Roboto_Regular24pt7b.h>

#include "display.h"
#include "status.h"
#include "can_message_ids.h"
#include "menu.h"
#include "main.h"
#include "icons.h"

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
    if(currentAlertEnd > 0 && currentAlertEnd > millis()) {
        currentAlertEnd = 0;
        return;
    }
    if(showMenuUntil < millis()) {
        menuKeepalive();
        return;
    }

    MenuList* currentMenu = getCurrentMenu();
    MenuItem selectedItem = currentMenu->items[menuPosition[menuDepth]];

    menuKeepalive();

    if(selectedItem.function != NULL) {
        setActionTimeout();
        selectedItem.function();
    } else if(selectedItem.subMenu != NULL) {
        menuDepth++;
    }
}

void DisplayManager::setActionTimeout() {
    showMenuExecNoticeUntil = millis() + MENU_EXEC_NOTICE_TIMEOUT;
}

void DisplayManager::out() {
    if(showMenuUntil < millis()) {
        menuKeepalive();
        return;
    }

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

    if(millis() > statusPhaseEnds) {
        statusPhase++;
        statusPhaseEnds = millis() + STATUS_PHASE_DURATION;
        if(statusPhase >= statusPhaseCount) {
            statusPhase = 0;
        }
    }

    if(millis() < showMenuExecNoticeUntil) {
        display.invertDisplay(true);
    } else {
        display.invertDisplay(false);
    }

    /* Display Menu or Speed */
    if(showMenuUntil > millis()) {
        if(sleeping) {
            wake();
        }
        showMenu();
    } else {
        uint8_t chargingStatus = getChargingStatus();
        if(chargingStatus == CHARGING_STATUS_CHARGING_NOW) {
            if(statusPhase % 2 == 0) {
                display.drawBitmap(
                    0, 0,
                    batteryFull,
                    ICON_WIDTH, ICON_HEIGHT,
                    WHITE
                );
            } else {
                display.drawBitmap(
                    0, 0,
                    batteryHalf,
                    ICON_WIDTH, ICON_HEIGHT,
                    WHITE
                );
            }
        } else if(chargingStatus == CHARGING_STATUS_FULLY_CHARGED) {
            display.drawBitmap(
                0, 0,
                batteryFull,
                ICON_WIDTH, ICON_HEIGHT,
                WHITE
            );
        }

        CANStatusMainMC status = getStatusMainMc();
        if(status.recording_now) {
            display.drawBitmap(
                DISPLAY_WIDTH - ICON_WIDTH - 1, 0,
                video,
                ICON_WIDTH, ICON_HEIGHT,
                WHITE
            );
        } else if(status.camera_connected) {
            display.drawBitmap(
                DISPLAY_WIDTH - ICON_WIDTH - 1, 0,
                wifi,
                ICON_WIDTH, ICON_HEIGHT,
                WHITE
            );
        } else if(status.wifi_enabled) {
            if(statusPhase % 2 == 0) {
                display.drawBitmap(
                    DISPLAY_WIDTH - ICON_WIDTH - 1, 0,
                    wifi,
                    ICON_WIDTH, ICON_HEIGHT,
                    WHITE
                );
            }
        }

        if(autosleep && !sleeping) {
            sleep();
        }
        String velocity = String(
            getDoubleStatusParameter(
                CAN_VELOCITY
            ),
            1
        );

        display.setFont(&Roboto_Regular24pt7b);
        display.setCursor(0, DISPLAY_HEIGHT - 1 - 17);
        bounds = getTextBounds(velocity);
        display.setCursor(
            (DISPLAY_WIDTH - bounds.w - 1) / 2,
            DISPLAY_HEIGHT - 1 - 17
        );
        display.println(velocity);
    }
    display.setFont(&Roboto_Regular8pt7b);

    /* Display alert if necessary */
    if(currentAlertEnd > 0 && currentAlertEnd > millis()) {
        display.drawFastHLine(0, 0, 128, WHITE);
        display.drawFastHLine(0, 47, 128, WHITE);
        display.fillRect(0, 1, 128, 46, BLACK);

        display.setCursor(0, 2 + FONT_HEIGHT);

        display.setTextWrap(true);
        display.println(currentAlert);
        display.setTextWrap(false);
    }

    /* Display Status Information */
    display.setCursor(0, DISPLAY_HEIGHT - 1);
    display.fillRect(0, 48, 128, 16, BLACK);
    if(statusPhase < (statusPhaseCount / 2)) {
        String voltage = String(
            getDoubleStatusParameter(
                CAN_VOLTAGE_BATTERY
            ),
            2
        );
        voltage += "V";
        display.println(voltage);
    } else {
        String amps = String(
            getDoubleStatusParameter(
                CAN_AMPS_CURRENT
            ),
            2
        );
        amps += "A";
        display.println(amps);
    }

    time_t localTime = Clock.TimeZone(
        Clock.getTime(),
        UTC_OFFSET
    );
    char minutes[5];
    sprintf(minutes, "%02d", Clock.minute(localTime));
    String currentTime = (
        String(Clock.hour(localTime))
        + ":"
        + String(minutes)
    );
    bounds = getTextBounds(currentTime);
    display.setCursor(
        DISPLAY_WIDTH - bounds.w - 1,
        DISPLAY_HEIGHT - 1
    );
    display.println(currentTime);

    display.display();
}

void DisplayManager::addAlert(String message) {
    message.toCharArray(currentAlert, 255);
    redisplayAlert();
}

void DisplayManager::redisplayAlert() {
    currentAlertEnd = millis() + ALERT_DURATION;
}

MenuList* DisplayManager::getCurrentMenu() {
    MenuList* currMenu = mainMenu;

    for(uint8_t i = 0; i < menuDepth; i++) {
        currMenu = currMenu->items[menuPosition[i]].subMenu;
    }

    return currMenu;
}

void DisplayManager::showMenu() {
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
        if(
            i == menuPosition[menuDepth]
            && (
                currMenu->items[i].function != NULL ||
                currMenu->items[i].subMenu != NULL

            )
        ) {
            display.print("[");
        }
        if (currMenu->items[i].nameFunction != NULL) {
            display.print(currMenu->items[i].nameFunction());
        } else {
            display.print(currMenu->items[i].name);
        }
        if(
            i == menuPosition[menuDepth]
            && (
                currMenu->items[i].function != NULL ||
                currMenu->items[i].subMenu != NULL

            )
        ) {
            display.print("]");
        }
        if(currMenu->items[i].subMenu != NULL) {
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

