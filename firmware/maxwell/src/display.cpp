#include "U8g2lib.h"
#undef max
#undef min
#include <AsyncModem.h>
#include <MCP79412RTC.h>
#include <time.h>
#include <JC_Button.h>

#include "display.h"
#include "power.h"
#include "status.h"
#include "lte.h"
#include "icons.h"
#include "pin_map.h"
#include "bluetooth.h"
#include "neopixel.h"
#include "main.h"
#include "led_cycles.h"
#include "serial_commands.h"

U8G2_ST7565_JLX12864_F_4W_HW_SPI displayCtl(U8G2_R0, DISPLAY_CS, DISPLAY_DC, DISPLAY_RST);

Button buttonLeftA = Button(BUTTON_LEFT_A, 120, true, true);
Button buttonLeftB = Button(BUTTON_LEFT_B, 120, true, true);
Button buttonRightA = Button(BUTTON_RIGHT_A, 120, true, true);
Button buttonRightB = Button(BUTTON_RIGHT_B, 120, true, true);

void display::init() {
    buttonRightA.begin();
    buttonRightB.begin();
    buttonLeftA.begin();
    buttonLeftB.begin();

    pinMode(BUTTON_RIGHT_A, INPUT_PULLUP);
    pinMode(BUTTON_RIGHT_B, INPUT_PULLUP);
    pinMode(BUTTON_LEFT_A, INPUT_PULLUP);
    pinMode(BUTTON_LEFT_B, INPUT_PULLUP);

    buttonLeftA.ignoreNextChange();
}

void display::loop() {
    buttonLeftA.read();
    buttonRightA.read();
    buttonLeftB.read();
    buttonRightB.read();

    if(buttonLeftA.pressedFor(LONG_PRESS_INTERVAL)) {
        buttonLeftA.ignorePress();
        buttonLeftA.ignoreNextChange();

        Display.setActionTimeout();

        neopixel::activatePreset(LED_CYCLE_OFF);
    } else if (buttonLeftA.wasReleased()) {
        Display.up();
    }

    if(buttonLeftB.pressedFor(LONG_PRESS_INTERVAL)) {
        buttonLeftB.ignorePress();
        buttonLeftB.ignoreNextChange();

        Display.setActionTimeout();

        console::toggleLightingPreset();
    } else if (buttonLeftB.wasReleased()) {
        Display.down();
    }

    if(buttonRightB.pressedFor(LONG_PRESS_INTERVAL)) {
        buttonRightB.ignorePress();
        buttonRightB.ignoreNextChange();

        Display.setActionTimeout();

        power::sleep();
    } else if(buttonRightB.wasReleased()) {
        Display.in();
    }

    if(buttonRightA.pressedFor(LONG_PRESS_INTERVAL)) {
        buttonRightA.ignorePress();
        buttonRightA.ignoreNextChange();

        Display.setActionTimeout();
        Display.toggleBacklight();
    } else if(buttonRightA.wasReleased()) {
        Display.out();
    }
}

DisplayManager::DisplayManager(MenuList* menuList) {
    mainMenu = menuList;
}

void DisplayManager::enable(bool _enabled) {
    enabled = _enabled;
}

void DisplayManager::enableBacklight(bool _enabled, bool save) {
    if(_enabled) {
        digitalWrite(DISPLAY_BACKLIGHT_ON_, LOW);
        if(save) {
            backlightOn = true;
        }
    } else {
        digitalWrite(DISPLAY_BACKLIGHT_ON_, HIGH);
        if(save) {
            backlightOn = false;
        }
    }
}

void DisplayManager::toggleBacklight() {
    if(backlightOn) {
        enableBacklight(false);
    } else {
        enableBacklight(true);
    }
}

void DisplayManager::enableTimeout(bool enable) {
    timeout = enable;
}

void DisplayManager::menuKeepalive() {
    showMenuUntil = millis() + MENU_TIMEOUT;
}

void DisplayManager::setContrast(uint8_t value) {
    displayCtl.setContrast(value);
}

void DisplayManager::setAutosleep(bool _enabled) {
    autosleep = _enabled;
    sleeping = false;
}

void DisplayManager::sleep() {
    enableBacklight(false);
    displayCtl.setPowerSave(true);
    sleeping = true;
}

void DisplayManager::wake() {
    //displayCtl.ssd1306_command(SSD1306_DISPLAYON);
    displayCtl.setPowerSave(false);
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
    if(currentAlertEnd > 0 && currentAlertEnd > millis()) {
        currentAlertEnd = 0;
        return;
    }
    if(showMenuUntil < millis()) {
        menuKeepalive();
        return;
    }

    menuKeepalive();

    menuPosition[menuDepth] = 0;

    if(menuDepth == 0) {
        // Hide the menu
        showMenuUntil = 0;
    } else if(menuDepth > 0) {
        menuDepth--;
    } else {
        menuDepth = 0;
        showMenuUntil = 0;
    }
}

void DisplayManager::begin() {
    enableBacklight(false);
    displayCtl.begin();
    displayCtl.setFlipMode(true);
    displayCtl.setCursor(0, 0);

    digitalWrite(DISPLAY_BACKLIGHT_ON_, HIGH);
    pinMode(DISPLAY_BACKLIGHT_ON_, OUTPUT);
}

void DisplayManager::refresh() {
    displayCtl.clearBuffer();
    displayCtl.setFont(SMALL_DISPLAY_FONT);

    if(millis() > statusPhaseEnds) {
        statusPhase++;
        statusPhaseEnds = millis() + STATUS_PHASE_DURATION;
        if(statusPhase >= statusPhaseCount) {
            statusPhase = 0;
        }
    }

    int width;

    if(millis() < showMenuExecNoticeUntil) {
        //displayCtl.invertDisplay(true);
    } else {
        //displayCtl.invertDisplay(false);
    }

    /* Display Menu or Speed */
    if((showMenuUntil > millis()) || (showMenuUntil > 0 && !timeout)) {
        if(sleeping) {
            wake();
        }
        showMenu();
    } else {
        uint8_t chargingStatus = power::getChargingStatus();
        if(chargingStatus == CHARGING_STATUS_CHARGING_NOW) {
            if(statusPhase % 2 == 0) {
                displayCtl.drawXBM(
                    0, 0,
                    ICON_WIDTH, ICON_HEIGHT,
                    batteryFull_bits
                );
            } else {
                displayCtl.drawXBM(
                    0, 0,
                    ICON_WIDTH, ICON_HEIGHT,
                    batteryHalf_bits
                );
            }
        }
        if (! power::isDynamoEnabled()) {
            displayCtl.drawXBM(
                16, 0,
                ICON_WIDTH, ICON_HEIGHT,
                dynamoPower_bits
            );
        }
        AsyncModem::SIM7000::NETWORK_STATUS status = lte::getNetworkStatus();
        if(lte::isLoggingNow()) {
            displayCtl.drawXBM(
                DISPLAY_WIDTH - ICON_WIDTH - 1, 0,
                ICON_WIDTH, ICON_HEIGHT,
                reporting_bits
            );
        } else if(
            lte::isEnabled() &&
            (
                status == AsyncModem::SIM7000::NETWORK_STATUS::REGISTERED_HOME ||
                status == AsyncModem::SIM7000::NETWORK_STATUS::REGISTERED_ROAMING
            )
        ) {
            displayCtl.drawXBM(
                DISPLAY_WIDTH - ICON_WIDTH - 1, 0,
                ICON_WIDTH, ICON_HEIGHT,
                lte_bits
            );
        }
        if(status::gpsFixValid()) {
            displayCtl.drawXBM(
                DISPLAY_WIDTH - (ICON_WIDTH + 1) * 2, 0,
                ICON_WIDTH, ICON_HEIGHT,
                gps_bits
            );
        }
        if (bluetooth::bluetoothIsEnabled()) {
            displayCtl.drawXBM(
                DISPLAY_WIDTH - ICON_WIDTH - 1,
                ICON_HEIGHT + 1,
                ICON_WIDTH, ICON_HEIGHT,
                bt_bits
            );
        }

        if(autosleep && !sleeping) {
            sleep();
        }
        displayCtl.setFont(LARGE_DISPLAY_FONT);

        time_t localTime = status::getTime() + (status::getEffectiveUTCOffset() * 3600);
        char displayCtlTime[10];
        sprintf(
            displayCtlTime,
            "%02d:%02d",
            hour(localTime),
            minute(localTime)
        );
        width = displayCtl.getStrWidth(displayCtlTime);
        displayCtl.setCursor(
            (DISPLAY_WIDTH - width - 1) / 2,
            DISPLAY_HEIGHT - 1 - 17
        );
        displayCtl.println(displayCtlTime);

        displayCtl.setFont(SMALL_DISPLAY_FONT);
        if((statusPhase / 2) % 2 == 0) {
            String voltage = String(
                power::getVoltage(VOLTAGE_BATTERY),
                2
            );
            voltage += "V";

            width = displayCtl.getStrWidth(voltage.c_str());
            displayCtl.setCursor(
                (DISPLAY_WIDTH - width - 1) / 2,
                SMALL_DISPLAY_FONT_HEIGHT + 1
            );
            displayCtl.println(voltage);
        } else {
            String amps = String(
                power::getCurrentUsage(),
                2
            );
            amps += "A";
            width = displayCtl.getStrWidth(amps.c_str());
            displayCtl.setCursor(
                (DISPLAY_WIDTH - width - 1) / 2,
                SMALL_DISPLAY_FONT_HEIGHT + 1
            );
            displayCtl.println(amps);
        }


    }
    displayCtl.setFont(SMALL_DISPLAY_FONT);

    /* Display Status Information */
    displayCtl.setDrawColor(0);
    displayCtl.drawBox(0, 48, 128, 16);
    displayCtl.setDrawColor(1);

    displayCtl.setCursor(0, DISPLAY_HEIGHT - 1);
    // Velocity
    String velocity = "";
    velocity = String(
        status::getSpeed(),
        1
    );
    velocity += "mph";
    displayCtl.println(velocity);

    // Distance
    String distance = "";
    distance = String(
        status::getTripOdometer(),
        2
    );
    distance += "mi";
    width = displayCtl.getStrWidth(distance.c_str());
    displayCtl.setCursor(
        DISPLAY_WIDTH - width - 1,
        DISPLAY_HEIGHT - 1
    );
    displayCtl.println(distance);

    /* Display alert if necessary */
    String currentAlert = getAlert();
    if(currentAlert.length() > 0) {
        displayCtl.setDrawColor(1);
        displayCtl.drawLine(0, 0, 128, 0);
        displayCtl.drawLine(0, 47, 128, 47);
        displayCtl.setDrawColor(0);
        displayCtl.drawBox(0, 1, 128, 46);

        displayCtl.setDrawColor(1);

        uint8_t startingChar = 0;
        uint8_t currentChar = 0;
        uint8_t currentLine = 1;
        while(currentChar < currentAlert.length()) {
            if(displayCtl.getStrWidth(currentAlert.substring(startingChar, currentChar).c_str()) > DISPLAY_WIDTH) {
                displayCtl.setCursor(0, (2 + FONT_HEIGHT) * currentLine);

                displayCtl.println(currentAlert.substring(startingChar, currentChar - 1));

                startingChar = currentChar - 1;
                currentLine++;
            } else if (currentChar == currentAlert.length() - 1) {
                displayCtl.setCursor(0, (2 + FONT_HEIGHT) * currentLine);

                displayCtl.println(currentAlert.substring(startingChar));
            }

            currentChar++;
        }

        if((millis() % 1000) < 500) {
            enableBacklight(true, false);
        } else {
            enableBacklight(false, false);
        }
    } else {
        enableBacklight(backlightOn, false);
    }

    displayCtl.sendBuffer();
}

String DisplayManager::getAlert() {
    if(displayingAlertNow && millis() > currentAlertEnd) {
        displayingAlertNow = false;

        for(uint8_t i = 1; i < alertCount; i++) {
            alert[i - 1] = alert[i];
        }

        alertCount--;
    }

    if(alertCount > 0) {
        if(!displayingAlertNow) {
            currentAlertEnd = millis() + ALERT_DURATION;
            displayingAlertNow = true;
        }
        return alert[0];
    }

    return "";
}

void DisplayManager::addAlert(String message) {
    if(alertCount < 9) {
        alert[alertCount] = message;
        alertCount++;
    }
}

MenuList* DisplayManager::getCurrentMenu() {
    MenuList* currMenu = mainMenu;

    for(uint8_t i = 0; i < menuDepth; i++) {
        currMenu = currMenu->items[menuPosition[i]].subMenu;
    }

    return currMenu;
}

void DisplayManager::showMenu() {
    displayCtl.setFont(SMALL_DISPLAY_FONT);

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
        displayCtl.setCursor(0, cursorPosition);  // X
        cursorPosition += rowHeight;

        if(i < 0) {
            displayCtl.println();
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
            displayCtl.print("[");
        }
        if (currMenu->items[i].nameFunction != NULL) {
            displayCtl.print(currMenu->items[i].nameFunction());
        } else {
            displayCtl.print(currMenu->items[i].name);
        }
        if(
            i == menuPosition[menuDepth]
            && (
                currMenu->items[i].function != NULL ||
                currMenu->items[i].subMenu != NULL

            )
        ) {
            displayCtl.print("]");
        }
        if(currMenu->items[i].subMenu != NULL) {
            displayCtl.print(" >");
        }
        displayCtl.println();
        j++;
    }
}

void DisplayManager::executeMenuCommand(void(*function)()) {
    function();
}

DisplayManager Display(&mainMenu);
