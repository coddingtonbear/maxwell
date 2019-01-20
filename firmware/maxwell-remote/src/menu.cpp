#include <MicroNMEA.h>

#include "menu.h"
#include "serial_commands.h"
#include "led_cycles.h"
#include "display.h"
#include "status.h"
#include "can_message_ids.h"

#include "main.h"


#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

uint8_t colorStep = 5;


MenuItem::MenuItem(String _name, MenuList* _subMenu){
    name = _name;
    subMenu = _subMenu;
}

MenuItem::MenuItem(String (*_name_function)(), MenuList* _subMenu){
    nameFunction = _name_function;
    subMenu = _subMenu;
}

MenuItem::MenuItem(String _name, void(*_function)()) {
    name = _name;
    function = _function;
}

MenuItem::MenuItem(String(*_name_function)(), void(*_function)()) {
    nameFunction = _name_function;
    function = _function;
}

MenuItem::MenuItem(String(*_function)()) {
    nameFunction = _function;
}

MenuList::MenuList(MenuItem* menuItems, uint8_t _length) {
    items = menuItems;
    length = _length;
}

// Please excuse the weird indentation below; this is a rare instance
// in which I think a non-standard indentation actually makes the code
// easier to understand (given the hierarchical nature of the menu
// defined below.

        MenuItem statsMenuItems[] = {
            MenuItem(
                []() -> String {
                    return String("Uptime: ") + String(
                        (float)millis() / 1000.0 / 60.0, 1
                    ) + String("min");
                }
            ),
            MenuItem(
                []() -> String {
                    MicroNMEA* fix = getGpsFix();
                    return String("GPS lock: ") + String(
                        fix->isValid() ? "Yes" : "No"
                    );
                }
            ),
            MenuItem(
                []() -> String {
                    MicroNMEA* fix = getGpsFix();
                    return String("Latitude: ") + String((float)fix->getLatitude() / 1e6);
                }
            ),
            MenuItem(
                []() -> String {
                    MicroNMEA* fix = getGpsFix();
                    return String("Longitude: ") + String((float)fix->getLongitude() / 1e6);
                }
            ),
            MenuItem(
                []() -> String {
                    MicroNMEA* fix = getGpsFix();
                    long altitude;
                    bool gotAltitude = fix->getAltitude(altitude);
                    if(gotAltitude) {
                        return String("Altitude: ") + String((float)altitude / 1e3) + String("m");
                    } else {
                        return String("Altitude: ?m");
                    }
                }
            ),
            MenuItem(
                []() -> String {
                    CANStatusMainMC status = getStatusMainMc();
                    return String("Charging: ") + String(
                        status.is_charging ? "Yes" : "No"
                    );
                }
            ),
            MenuItem(
                []() -> String {
                    bool btEnabled = getBluetoothEnabled();
                    return String("Local BT: ") + String(
                        btEnabled ? "Yes" : "No"
                    );
                }
            ),
            MenuItem(
                []() -> String {
                    CANStatusMainMC status = getStatusMainMc();
                    return String("Main BT: ") + String(
                        status.bt_enabled ? "Yes" : "No"
                    );
                }
            ),
            MenuItem(
                []() -> String {
                    CANStatusMainMC status = getStatusMainMc();
                    return String("Charge En: ") + String(
                        status.charging_enabled ? "Yes" : "No"
                    );
                }
            ),
            /*
            MenuItem(
                []() -> String {
                    CANStatusMainMC status = getStatusMainMc();
                    return String("Wifi En: ") + String(
                        status.wifi_enabled ? "Yes" : "No"
                    );
                }
            ),
            MenuItem(
                []() -> String {
                    CANStatusMainMC status = getStatusMainMc();
                    return String("Cam Cnctd: ") + String(
                        status.camera_connected ? "Yes" : "No"
                    );
                }
            ),
            MenuItem(
                []() -> String {
                    CANStatusMainMC status = getStatusMainMc();
                    return String("Recording: ") + String(
                        status.recording_now ? "Yes" : "No"
                    );
                }
            ),
            MenuItem(
                []() -> String {
                    CANStatusMainMC status = getStatusMainMc();
                    return String("Lighting En: ") + String(
                        status.lighting_enabled ? "Yes" : "No"
                    );
                }
            ),*/
            MenuItem(
                []() -> String {
                    CANStatusMainMC status = getStatusMainMc();
                    return String("Logging: ") + String(
                        status.logging_now ? "Yes" : "No"
                    );
                }
            ),
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
            ),
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
                        []() -> void {
                            activateLightingPreset(LED_PRESET_SAFETY);
                        }
                    ),
                    MenuItem(
                        "Midnight",
                        []() -> void {
                            activateLightingPreset(LED_PRESET_MIDNIGHT);
                        }
                    ),
                    MenuItem(
                        "Rainbow",
                        []() -> void {
                            activateLightingPreset(LED_PRESET_RAINBOW);
                        }
                    )
                };
            MenuList presetMenuList(presetOptions, COUNT_OF(presetOptions));
                MenuItem cycleOptions[] = {
                    MenuItem(
                        "On",
                        []() -> void {
                            setLightingCycle(LED_CYCLE_ON);
                        }
                    ),
                    MenuItem(
                        "Random",
                        []() -> void {
                            setLightingCycle(LED_CYCLE_RANDOM);
                        }
                    ),
                    MenuItem(
                        "Motion",
                        []() -> void {
                            setLightingCycle(LED_CYCLE_MOTION);
                        }
                    ),
                    MenuItem(
                        "Blink",
                        []() -> void {
                            setLightingCycle(LED_CYCLE_BLINK);
                        }
                    ),
                    MenuItem(
                        "Rotation",
                        []() -> void {
                            setLightingCycle(LED_CYCLE_ROTATION);
                        }
                    )
                };
            MenuList cycleMenuList(cycleOptions, COUNT_OF(cycleOptions));
                MenuItem brightnessOptions[] = {
                    MenuItem(
                        "100%",
                        []() -> void {
                            setLightingBrightness(255);
                        }
                    ),
                    MenuItem(
                        "90%",
                        []() -> void {
                            setLightingBrightness(205);
                        }
                    ),
                    MenuItem(
                        "80%",
                        []() -> void {
                            setLightingBrightness(158);
                        }
                    ),
                    MenuItem(
                        "70%",
                        []() -> void {
                            setLightingBrightness(111);
                        }
                    ),
                    MenuItem(
                        "60%",
                        []() -> void {
                            setLightingBrightness(64);
                        }
                    ),
                    MenuItem(
                        "50%",
                        []() -> void {
                            setLightingBrightness(32);
                        }
                    ),
                    MenuItem(
                        "40%",
                        []() -> void {
                            setLightingBrightness(16);
                        }
                    ),
                    MenuItem(
                        "30%",
                        []() -> void {
                            setLightingBrightness(8);
                        }
                    ),
                    MenuItem(
                        "20%",
                        []() -> void {
                            setLightingBrightness(4);
                        }
                    ),
                    MenuItem(
                        "10%",
                        []() -> void {
                            setLightingBrightness(2);
                        }
                    ),
                    MenuItem(
                        "0%",
                        []() -> void {
                            setLightingBrightness(0);
                        }
                    )
                };
            MenuList brightnessMenuList(brightnessOptions, COUNT_OF(brightnessOptions));
                MenuItem color1Options[] = {
                    MenuItem(
                        []() -> String {
                            return "+Step (" + String(colorStep) + ")";
                        },
                        []() -> void {
                            colorStep++;
                        }
                    ),
                    MenuItem(
                        []() -> String {
                            return "-Step";
                        },
                        []() -> void {
                            colorStep--;
                        }
                    ),
                    MenuItem(
                        []() -> String {
                            CANLedStatusColor colors = getLedColors();
                            return "-Red (" + String(colors.red) + ")";
                        },
                        []() -> void {
                            CANLedStatusColor colors = getLedColors();
                            colors.red -= colorStep;

                            setLedColor(colors);
                        }
                    ),
                    MenuItem(
                        []() -> String {
                            return "+Red";
                        },
                        []() -> void {
                            CANLedStatusColor colors = getLedColors();
                            colors.red += colorStep;

                            setLedColor(colors);
                        }
                    ),
                    MenuItem(
                        []() -> String {
                            CANLedStatusColor colors = getLedColors();
                            return "-Green (" + String(colors.green) + ")";
                        },
                        []() -> void {
                            CANLedStatusColor colors = getLedColors();
                            colors.green -= colorStep;

                            setLedColor(colors);
                        }
                    ),
                    MenuItem(
                        []() -> String {
                            return "+Green";
                        },
                        []() -> void {
                            CANLedStatusColor colors = getLedColors();
                            colors.green += colorStep;

                            setLedColor(colors);
                        }
                    ),
                    MenuItem(
                        []() -> String {
                            CANLedStatusColor colors = getLedColors();
                            return "-Blue (" + String(colors.blue) + ")";
                        },
                        []() -> void {
                            CANLedStatusColor colors = getLedColors();
                            colors.blue -= colorStep;

                            setLedColor(colors);
                        }
                    ),
                    MenuItem(
                        []() -> String {
                            return "+Blue";
                        },
                        []() -> void {
                            CANLedStatusColor colors = getLedColors();
                            colors.blue += colorStep;

                            setLedColor(colors);
                        }
                    ),
                };
            MenuList color1MenuList(color1Options, COUNT_OF(color1Options));
                MenuItem color2Options[] = {
                    MenuItem(
                        []() -> String {
                            return "+Step (" + String(colorStep) + ")";
                        },
                        []() -> void {
                            colorStep++;
                        }
                    ),
                    MenuItem(
                        []() -> String {
                            return "-Step";
                        },
                        []() -> void {
                            colorStep--;
                        }
                    ),
                    MenuItem(
                        []() -> String {
                            CANLedStatusColor colors = getLedColors();
                            return "-Red (" + String(colors.red2) + ")";
                        },
                        []() -> void {
                            CANLedStatusColor colors = getLedColors();
                            colors.red2 -= colorStep;

                            setLedColor(colors);
                        }
                    ),
                    MenuItem(
                        []() -> String {
                            return "+Red";
                        },
                        []() -> void {
                            CANLedStatusColor colors = getLedColors();
                            colors.red2 += colorStep;

                            setLedColor(colors);
                        }
                    ),
                    MenuItem(
                        []() -> String {
                            CANLedStatusColor colors = getLedColors();
                            return "-Green (" + String(colors.green2) + ")";
                        },
                        []() -> void {
                            CANLedStatusColor colors = getLedColors();
                            colors.green2 -= colorStep;

                            setLedColor(colors);
                        }
                    ),
                    MenuItem(
                        []() -> String {
                            return "+Green";
                        },
                        []() -> void {
                            CANLedStatusColor colors = getLedColors();
                            colors.green2 += colorStep;

                            setLedColor(colors);
                        }
                    ),
                    MenuItem(
                        []() -> String {
                            CANLedStatusColor colors = getLedColors();
                            return "-Blue (" + String(colors.blue2) + ")";
                        },
                        []() -> void {
                            CANLedStatusColor colors = getLedColors();
                            colors.blue2 -= colorStep;

                            setLedColor(colors);
                        }
                    ),
                    MenuItem(
                        []() -> String {
                            return "+Blue";
                        },
                        []() -> void {
                            CANLedStatusColor colors = getLedColors();
                            colors.blue2 += colorStep;

                            setLedColor(colors);
                        }
                    ),
                };
            MenuList color2MenuList(color2Options, COUNT_OF(color2Options));
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
                "Color #1",
                &color1MenuList
            ),
            MenuItem(
                "Color #2",
                &color2MenuList
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

                MenuItem cameraConnectionItems[] = {
                    MenuItem(
                        "Connect",
                        connectCamera
                    ),
                    MenuItem(
                        "Disconnect",
                        disconnectCamera
                    )
                };
            MenuList cameraConnectionList(cameraConnectionItems, COUNT_OF(cameraConnectionItems));
        MenuItem cameraMenuItems[] = {
            /*
            MenuItem(
                []() -> String {
                    CANStatusMainMC status = getStatusMainMc();
                    return String("Connected: ") + String(
                        status.camera_connected ? "Yes" : "No"
                    );
                },
                &cameraConnectionList
            ),*/
            MenuItem(
                "Delete Media",
                deleteCameraMedia
            )
        };
    MenuList cameraMenuList(cameraMenuItems, COUNT_OF(cameraMenuItems));
MenuItem cameraMenu("Camera", &cameraMenuList);

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

                MenuItem baseLTEMenuItems[] = {
                    MenuItem(
                        "Disable",
                        disableLTE
                    ),
                    MenuItem(
                        "Enable",
                        enableLTE
                    )
                };
            MenuList baseLTEMenuList(baseLTEMenuItems, COUNT_OF(baseLTEMenuItems));

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
                "Base LTE",
                &baseLTEMenuList
            ),
        };
    MenuList commsMenuList(commsMenuItems, COUNT_OF(commsMenuItems));
MenuItem commsMenu("Bluetooth", &commsMenuList);

MenuItem mainMenuItems[] = {
    statsMenu,
    powerMenu,
    commsMenu,
    cameraMenu,
    lightingMenu
};
MenuList mainMenu(mainMenuItems, COUNT_OF(mainMenuItems));
