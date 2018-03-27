#include <functional>

#include "menu.h"
#include "serial_commands.h"
#include "led_cycles.h"
#include "display.h"

#include "main.h"

MenuItem::MenuItem(String _name, MenuList* _subMenu){
    name = _name;
    subMenu = _subMenu;
}

MenuItem::MenuItem(String _name, std::function<void()> _function) {
    name = _name;
    function = _function;
}

MenuList::MenuList(MenuItem menuItems[], uint8_t count) {
    items = menuItems;
    length = count;
}


// Helper functions
std::function<void()> makePresetMenuItem(uint8_t menuItem) {
    return [menuItem]() -> void {
        activateLightingPreset(menuItem);
    };
}
std::function<void()> makeCycleMenuItem(uint8_t menuItem) {
    return [menuItem]() -> void {
        setLightingCycle(menuItem);
    };
}
std::function<void()> makeBrightnessMenuItem(uint8_t value) {
    return [value]() -> void {
        setLightingBrightness(value);
    };
}
std::function<void()> makeDisplayBrightnessMenuItem(uint8_t value) {
    return [value]() -> void {
        if(value > 0) {
            Display.enable(true);
            Display.setContrast(value);
        } else {
            Display.enable(false);
        }
    };
}

// Please excuse the weird indentation below; this is a rare instance
// in which I think a non-standard indentation actually makes the code
// easier to understand (given the hierarchical nature of the menu
// defined below.
                MenuItem chargingMenuOptions[] = {
                    MenuItem(
                        "Enable",
                        enableBatteryCharging
                    ),
                    MenuItem(
                        "Disable",
                        disableBatteryCharging
                    )
                };
            MenuList chargingMenuList(chargingMenuOptions, 2);
        MenuItem powerMenuItems[] = {
            MenuItem(
                "Power Off",
                sleep
            ),
            MenuItem(
                "Wake Base",
                wake
            ),
            MenuItem(
                "Reset",
                reset
            ),
            MenuItem(
                "Charging",
                &chargingMenuList
            )
        };
    MenuList powerMenuList(powerMenuItems, 4);
MenuItem powerMenu("Power", &powerMenuList);

                MenuItem presetOptions[] = {
                    MenuItem(
                        "Safety",
                        makePresetMenuItem(LED_PRESET_SAFETY)
                    )
                };
            MenuList presetMenuList(presetOptions, 1);
                MenuItem cycleOptions[] = {
                    MenuItem(
                        "On",
                        makeCycleMenuItem(LED_CYCLE_ON)
                    ),
                    MenuItem(
                        "Random",
                        makeCycleMenuItem(LED_CYCLE_RANDOM)
                    ),
                    MenuItem(
                        "Motion",
                        makeCycleMenuItem(LED_CYCLE_MOTION)
                    ),
                    MenuItem(
                        "Blink",
                        makeCycleMenuItem(LED_CYCLE_BLINK)
                    ),
                    MenuItem(
                        "Twinkle",
                        makeCycleMenuItem(LED_CYCLE_TWINKLE)
                    ),
                    MenuItem(
                        "Rainbow",
                        makeCycleMenuItem(LED_CYCLE_RAINBOW)
                    )
                };
            MenuList cycleMenuList(cycleOptions, 6);
                MenuItem brightnessOptions[] = {
                    MenuItem(
                        "100%",
                        makeBrightnessMenuItem(255)
                    ),
                    MenuItem(
                        "90%",
                        makeBrightnessMenuItem(205)
                    ),
                    MenuItem(
                        "80%",
                        makeBrightnessMenuItem(158)
                    ),
                    MenuItem(
                        "70%",
                        makeBrightnessMenuItem(111)
                    ),
                    MenuItem(
                        "60%",
                        makeBrightnessMenuItem(64)
                    ),
                    MenuItem(
                        "50%",
                        makeBrightnessMenuItem(32)
                    ),
                    MenuItem(
                        "40%",
                        makeBrightnessMenuItem(16)
                    ),
                    MenuItem(
                        "30%",
                        makeBrightnessMenuItem(8)
                    ),
                    MenuItem(
                        "20%",
                        makeBrightnessMenuItem(4)
                    ),
                    MenuItem(
                        "10%",
                        makeBrightnessMenuItem(2)
                    ),
                    MenuItem(
                        "0%",
                        makeBrightnessMenuItem(0)
                    )
                };
            MenuList brightnessMenuList(brightnessOptions, 11);
        MenuItem lightingMenuItems[] = {
            MenuItem(
                "Enable",
                enableLighting
            ),
            MenuItem(
                "Disable",
                disableLighting
            ),
            MenuItem(
                "Presets",
                &presetMenuList
            ),
            MenuItem(
                "Cycles",
                &cycleMenuList
            ),
            MenuItem(
                "Brightness",
                &brightnessMenuList
            )
        };
    MenuList lightingMenuList(lightingMenuItems, 5);
MenuItem lightingMenu("Lighting", &lightingMenuList);

                MenuItem bluetoothMenuItems[] = {
                    MenuItem(
                        "Disable",
                        disableBluetooth
                    ),
                    MenuItem(
                        "Enable",
                        enableBluetooth
                    )
                };
            MenuList bluetoothMenuList(bluetoothMenuItems, 2);

                MenuItem espMenuItems[] = {
                    MenuItem(
                        "Disable",
                        disableEsp
                    ),
                    MenuItem(
                        "Enable",
                        enableEsp
                    )
                };
            MenuList espMenuList(espMenuItems, 2);

        MenuItem commsMenuItems[] = {
            MenuItem(
                "Local BT",
                &bluetoothMenuList
            ),
            MenuItem(
                "Base BLE",
                &espMenuList
            )
        };
    MenuList commsMenuList(commsMenuItems, 2);
MenuItem commsMenu("Bluetooth", &commsMenuList);

                MenuItem displayBrightnessMenuItems[] = {
                    MenuItem(
                        "High",
                        makeDisplayBrightnessMenuItem(0xCF)
                    ),
                    MenuItem(
                        "Low",
                        makeDisplayBrightnessMenuItem(0x01)
                    ),
                    MenuItem(
                        "Off",
                        makeDisplayBrightnessMenuItem(0)
                    )
                };
            MenuList displayBrightnessMenuList(displayBrightnessMenuItems, 3);
        MenuItem displayMenuItems[] = {
            MenuItem(
                "Brightness",
                &displayBrightnessMenuList
            )
        };
    MenuList displayMenuList(displayMenuItems, 1);
MenuItem displayMenu("Display", &displayMenuList);

MenuItem mainMenuItems[] = {
    powerMenu,
    commsMenu,
    lightingMenu,
    displayMenu
};
MenuList mainMenu(mainMenuItems, 4);
