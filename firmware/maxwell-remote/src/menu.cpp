#include <functional>

#include "menu.h"
#include "serial_commands.h"
#include "led_cycles.h"
#include "display.h"
#include "status.h"
#include "can_message_ids.h"

#include "main.h"


#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))


MenuItem::MenuItem(String _name, MenuList* _subMenu){
    name = _name;
    subMenu = _subMenu;
}

MenuItem::MenuItem(std::function<String()> _name_function, MenuList* _subMenu){
    nameFunction = _name_function;
    subMenu = _subMenu;
}

MenuItem::MenuItem(String _name, std::function<void()> _function) {
    name = _name;
    function = _function;
}

MenuItem::MenuItem(std::function<String()> _name_function, std::function<void()> _function) {
    nameFunction = _name_function;
    function = _function;
}

MenuItem::MenuItem(std::function<String()> _function) {
    nameFunction = _function;
}

MenuList::MenuList(MenuItem* menuItems, uint8_t _length) {
    items = menuItems;
    length = _length;
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
            Display.setAutosleep(false);
            Display.setContrast(value);
        } else {
            Display.setAutosleep(true);
        }
    };
}

// Please excuse the weird indentation below; this is a rare instance
// in which I think a non-standard indentation actually makes the code
// easier to understand (given the hierarchical nature of the menu
// defined below.

        MenuItem statsMenuItems[] = {
            MenuItem(
                []() -> String {
                    return String("Voltage: ") + String(
                        getDoubleStatusParameter(
                            CAN_VOLTAGE_BATTERY
                        ),
                        2
                    );
                }
            ),
            MenuItem(
                []() -> String {
                    return String("Current: ") + String(
                        getDoubleStatusParameter(
                            CAN_AMPS_CURRENT
                        ),
                        2
                    );
                }
            )
        };
    MenuList statsMenuList(statsMenuItems, COUNT_OF(statsMenuItems));
MenuItem statsMenu("Stats", &statsMenuList);
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
            MenuList chargingMenuList(chargingMenuOptions, COUNT_OF(chargingMenuOptions));
                MenuItem autosleepMenuOptions[] = {
                    MenuItem(
                        "Enable",
                        enableAutosleep
                    ),
                    MenuItem(
                        "Disable",
                        disableAutosleep
                    )
                };
            MenuList autosleepMenuList(autosleepMenuOptions, COUNT_OF(autosleepMenuOptions));
        MenuItem powerMenuItems[] = {
            MenuItem(
                "Power Off",
                sleep
            ),
            MenuItem(
                "Save Power",
                lowPowerMode
            ),
            MenuItem(
                "Charging",
                &chargingMenuList
            ),
            MenuItem(
                "Autosleep",
                &autosleepMenuList
            ),
            MenuItem(
                "Wake Base",
                wake
            ),
            MenuItem(
                "Reset",
                reset
            )
        };
    MenuList powerMenuList(powerMenuItems, COUNT_OF(powerMenuItems));
MenuItem powerMenu("Power", &powerMenuList);

                MenuItem presetOptions[] = {
                    MenuItem(
                        "Safety",
                        makePresetMenuItem(LED_PRESET_SAFETY)
                    )
                };
            MenuList presetMenuList(presetOptions, COUNT_OF(presetOptions));
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
            MenuList cycleMenuList(cycleOptions, COUNT_OF(cycleOptions));
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
            MenuList brightnessMenuList(brightnessOptions, COUNT_OF(brightnessOptions));
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
    MenuList lightingMenuList(lightingMenuItems, COUNT_OF(lightingMenuItems));
MenuItem lightingMenu("Lighting", &lightingMenuList);

                MenuItem localBluetoothMenuItems[] = {
                    MenuItem(
                        "Disable",
                        disableLocalBluetooth
                    ),
                    MenuItem(
                        "Enable",
                        enableLocalBluetooth
                    )
                };
            MenuList localBluetoothMenuList(localBluetoothMenuItems, COUNT_OF(localBluetoothMenuItems));

                MenuItem baseBluetoothMenuItems[] = {
                    MenuItem(
                        "Disable",
                        disableBluetooth
                    ),
                    MenuItem(
                        "Enable",
                        enableBluetooth
                    ),
                };
            MenuList baseBluetoothMenuList(baseBluetoothMenuItems, COUNT_OF(baseBluetoothMenuItems));

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
            MenuList espMenuList(espMenuItems, COUNT_OF(espMenuItems));

        MenuItem commsMenuItems[] = {
            MenuItem(
                "Local BT",
                &localBluetoothMenuList
            ),
            MenuItem(
                "Base BT",
                &baseBluetoothMenuList
            ),
            MenuItem(
                "Base BLE",
                &espMenuList
            )
        };
    MenuList commsMenuList(commsMenuItems, COUNT_OF(commsMenuItems));
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
            MenuList displayBrightnessMenuList(displayBrightnessMenuItems, COUNT_OF(displayBrightnessMenuItems));
        MenuItem displayMenuItems[] = {
            MenuItem(
                "Brightness",
                &displayBrightnessMenuList
            )
        };
    MenuList displayMenuList(displayMenuItems, COUNT_OF(displayMenuItems));
MenuItem displayMenu("Display", &displayMenuList);

MenuItem mainMenuItems[] = {
    statsMenu,
    powerMenu,
    commsMenu,
    lightingMenu,
    displayMenu
};
MenuList mainMenu(mainMenuItems, COUNT_OF(mainMenuItems));
