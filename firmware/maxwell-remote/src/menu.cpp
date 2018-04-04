#include <vector>
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

MenuList::MenuList(std::vector<MenuItem> menuItems) {
    items = menuItems;
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
                std::vector<MenuItem> chargingMenuOptions({
                    MenuItem(
                        "Enable",
                        enableBatteryCharging
                    ),
                    MenuItem(
                        "Disable",
                        disableBatteryCharging
                    )
                });
            MenuList chargingMenuList(chargingMenuOptions);
        std::vector<MenuItem> powerMenuItems({
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
            ),
            MenuItem(
                "Low-Power Mode",
                lowPowerMode
            )
        });
    MenuList powerMenuList(powerMenuItems);
MenuItem powerMenu("Power", &powerMenuList);

                std::vector<MenuItem> presetOptions({
                    MenuItem(
                        "Safety",
                        makePresetMenuItem(LED_PRESET_SAFETY)
                    )
                });
            MenuList presetMenuList(presetOptions);
                std::vector<MenuItem> cycleOptions({
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
                });
            MenuList cycleMenuList(cycleOptions);
                std::vector<MenuItem> brightnessOptions({
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
                });
            MenuList brightnessMenuList(brightnessOptions);
        std::vector<MenuItem> lightingMenuItems({
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
        });
    MenuList lightingMenuList(lightingMenuItems);
MenuItem lightingMenu("Lighting", &lightingMenuList);

                std::vector<MenuItem> localBluetoothMenuItems({
                    MenuItem(
                        "Disable",
                        disableLocalBluetooth
                    ),
                    MenuItem(
                        "Enable",
                        enableLocalBluetooth
                    )
                });
            MenuList localBluetoothMenuList(localBluetoothMenuItems);

                std::vector<MenuItem> baseBluetoothMenuItems({
                    MenuItem(
                        "Disable",
                        disableBluetooth
                    ),
                    MenuItem(
                        "Enable",
                        enableBluetooth
                    ),
                });
            MenuList baseBluetoothMenuList(baseBluetoothMenuItems);

                std::vector<MenuItem> espMenuItems({
                    MenuItem(
                        "Disable",
                        disableEsp
                    ),
                    MenuItem(
                        "Enable",
                        enableEsp
                    )
                });
            MenuList espMenuList(espMenuItems);

        std::vector<MenuItem> commsMenuItems({
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
        });
    MenuList commsMenuList(commsMenuItems);
MenuItem commsMenu("Bluetooth", &commsMenuList);

                std::vector<MenuItem> displayBrightnessMenuItems({
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
                });
            MenuList displayBrightnessMenuList(displayBrightnessMenuItems);
        std::vector<MenuItem> displayMenuItems({
            MenuItem(
                "Brightness",
                &displayBrightnessMenuList
            )
        });
    MenuList displayMenuList(displayMenuItems);
MenuItem displayMenu("Display", &displayMenuList);

std::vector<MenuItem> mainMenuItems({
    powerMenu,
    commsMenu,
    lightingMenu,
    displayMenu
});
MenuList mainMenu(mainMenuItems);
