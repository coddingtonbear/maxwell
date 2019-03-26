#include "U8g2lib.h"
#include "display.h"
#include "status.h"
#include "can_message_ids.h"
#include "serial_commands.h"
#include "menu.h"
#include "main.h"
#include "icons.h"

U8G2_ST7565_JLX12864_F_4W_HW_SPI display(U8G2_R0, DISPLAY_CS, DISPLAY_DC, DISPLAY_RST);

DisplayManager::DisplayManager(MenuList* menuList) {
    mainMenu = menuList;
}

void DisplayManager::enable(bool _enabled) {
    enabled = _enabled;
}

void DisplayManager::enableBacklight(bool _enabled) {
    if(_enabled) {
        digitalWrite(BACKLIGHT_ON_, LOW);
        backlightOn = true;
    } else {
        digitalWrite(BACKLIGHT_ON_, HIGH);
        backlightOn = false;
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
    display.setContrast(value);
}

void DisplayManager::setAutosleep(bool _enabled) {
    autosleep = _enabled;
    sleeping = false;
}

void DisplayManager::sleep() {
    enableBacklight(false);
    display.setPowerSave(true);
    sleeping = true;
}

void DisplayManager::wake() {
    //display.ssd1306_command(SSD1306_DISPLAYON);
    display.setPowerSave(false);
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
    enableBacklight(false);
    display.begin();
    display.setFlipMode(true);
    display.setCursor(0, 0);
}

void DisplayManager::refresh() {
    display.clearBuffer();
    display.setFont(SMALL_DISPLAY_FONT);

    bool statusIsAvailable = statusAvailable();

    if(millis() > statusPhaseEnds) {
        statusPhase++;
        statusPhaseEnds = millis() + STATUS_PHASE_DURATION;
        if(statusPhase >= statusPhaseCount) {
            statusPhase = 0;
        }
    }

    if(millis() < showMenuExecNoticeUntil) {
        //display.invertDisplay(true);
    } else {
        //display.invertDisplay(false);
    }

    /* Display Menu or Speed */
    if((showMenuUntil > millis()) || (showMenuUntil > 0 && !timeout)) {
        if(sleeping) {
            wake();
        }
        showMenu();
    } else {
        if(statusIsAvailable) {
            CANStatusMainMC status = getStatusMainMc();
            if(status.is_charging) {
                if(statusPhase % 2 == 0) {
                    display.drawXBM(
                        0, 0,
                        ICON_WIDTH, ICON_HEIGHT,
                        batteryFull_bits
                    );
                } else {
                    display.drawXBM(
                        0, 0,
                        ICON_WIDTH, ICON_HEIGHT,
                        batteryHalf_bits
                    );
                }
            }
            if(status.power_source == 0) {
                display.drawXBM(
                    16, 0,
                    ICON_WIDTH, ICON_HEIGHT,
                    dynamoPower_bits
                );
            }

            if(status.logging_lte) {
                display.drawXBM(
                    DISPLAY_WIDTH - ICON_WIDTH - 1, 0,
                    ICON_WIDTH, ICON_HEIGHT,
                    reporting_bits
                );
            } else if(status.lte_connected) {
                display.drawXBM(
                    DISPLAY_WIDTH - ICON_WIDTH - 1, 0,
                    ICON_WIDTH, ICON_HEIGHT,
                    lte_bits
                );
            }
            if(gpsFixValid()) {
                display.drawXBM(
                    DISPLAY_WIDTH - (ICON_WIDTH + 1) * 2, 0,
                    ICON_WIDTH, ICON_HEIGHT,
                    gps_bits
                );
            }
            if (
                getBluetoothEnabled() && status.bt_enabled
            ) {
                display.drawXBM(
                    DISPLAY_WIDTH - ICON_WIDTH - 1,
                    ICON_HEIGHT + 1,
                    ICON_WIDTH, ICON_HEIGHT,
                    remoteBaseBt_bits
                );
            } else if(getBluetoothEnabled()) {
                display.drawXBM(
                    DISPLAY_WIDTH - ICON_WIDTH - 1,
                    ICON_HEIGHT + 1,
                    ICON_WIDTH, ICON_HEIGHT,
                    remoteBt_bits
                );
            } else if(status.bt_enabled) {
                display.drawXBM(
                    DISPLAY_WIDTH - ICON_WIDTH - 1,
                    ICON_HEIGHT + 1,
                    ICON_WIDTH, ICON_HEIGHT,
                    baseBt_bits
                );
            }

            /*
            } else if(status.recording_now) {
                display.drawXBM(
                    DISPLAY_WIDTH - ICON_WIDTH - 1, rightPosition,
                    ICON_WIDTH, ICON_HEIGHT,
                    video
                );
                rightPosition += ICON_HEIGHT;
            } else if(status.camera_connected) {
                display.drawXBM(
                    DISPLAY_WIDTH - ICON_WIDTH - 1, rightPosition,
                    ICON_WIDTH, ICON_HEIGHT,
                    wifi
                );
                rightPosition += ICON_HEIGHT;
            } else if(status.wifi_enabled) {
                if(statusPhase % 2 == 0) {
                    display.drawXBM(
                        DISPLAY_WIDTH - ICON_WIDTH - 1, rightPosition,
                        ICON_WIDTH, ICON_HEIGHT,
                        wifi
                    );
                }
                rightPosition += ICON_HEIGHT;
            }
            */
        }

        if(autosleep && !sleeping) {
            sleep();
        }
        int width;

        display.setFont(LARGE_DISPLAY_FONT);
        time_t localTime = Clock.TimeZone(
            Clock.getTime(),
            UTC_OFFSET
        );
        String currentTime = "";
        char minutes[5];
        sprintf(minutes, "%02d", Clock.minute(localTime));
        if(statusIsAvailable) {
            currentTime = (
                String(Clock.hour(localTime))
                + ":"
                + String(minutes)
            );
        }
        width = display.getStrWidth(currentTime.c_str());
        display.setCursor(
            (DISPLAY_WIDTH - width - 1) / 2,
            DISPLAY_HEIGHT - 1 - 17
        );
        display.println(currentTime);

        display.setFont(SMALL_DISPLAY_FONT);
        String velocity = "";
        if(statusIsAvailable) {
            velocity = String(
                getDoubleStatusParameter(
                    CAN_VELOCITY
                ),
                1
            );
            velocity += "mph";
        }
        width = display.getStrWidth(velocity.c_str());
        display.setCursor(
            (DISPLAY_WIDTH - width - 1) / 2,
            SMALL_DISPLAY_FONT_HEIGHT + 1
        );
        display.println(velocity);


    }
    display.setFont(SMALL_DISPLAY_FONT);

    /* Display alert if necessary */
    if(currentAlertEnd > 0 && currentAlertEnd > millis()) {
        display.setDrawColor(1);
        display.drawLine(0, 0, 128, 0);
        display.drawLine(0, 47, 128, 47);
        display.setDrawColor(0);
        display.drawBox(0, 1, 128, 46);
        display.setCursor(0, 2 + FONT_HEIGHT);

        display.setDrawColor(1);
        display.println(currentAlert);
    }

    /* Display Status Information */
    display.setCursor(0, DISPLAY_HEIGHT - 1);
    display.setDrawColor(0);
    display.drawBox(0, 48, 128, 16);
    display.setDrawColor(1);

    int width;
    if(statusIsAvailable) {
        String voltage = String(
            getDoubleStatusParameter(
                CAN_VOLTAGE_BATTERY
            ),
            2
        );
        voltage += "V";
        display.println(voltage);

        String amps = String(
            getDoubleStatusParameter(
                CAN_AMPS_CURRENT
            ),
            2
        );
        amps += "A";
        width = display.getStrWidth(amps.c_str());
        display.setCursor(
            DISPLAY_WIDTH - width - 1,
            DISPLAY_HEIGHT - 1
        );
        display.println(amps);
    }

    display.sendBuffer();
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
    display.setFont(SMALL_DISPLAY_FONT);

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

DisplayManager Display(&mainMenu);

