#include <MicroNMEA.h>

#include "menu.h"
#include "serial_commands.h"
#include "display.h"
#include "status.h"
#include "bluetooth.h"
#include "power.h"
#include "main.h"
#include "neopixel.h"


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
                    MicroNMEA* fix = status::getGpsFix();
                    return String("GPS lock: ") + String(
                        fix->isValid() ? "Yes" : "No"
                    );
                }
            ),
            MenuItem(
                []() -> String {
                    MicroNMEA* fix = status::getGpsFix();
                    return String("Latitude: ") + String((float)fix->getLatitude() / 1e6);
                }
            ),
            MenuItem(
                []() -> String {
                    MicroNMEA* fix = status::getGpsFix();
                    return String("Longitude: ") + String((float)fix->getLongitude() / 1e6);
                }
            ),
            MenuItem(
                []() -> String {
                    MicroNMEA* fix = status::getGpsFix();
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
                    uint8_t chargingStatus = power::getChargingStatus();
                    return String("Charging: ") + String(
                        chargingStatus == CHARGING_STATUS_CHARGING_NOW ? "Yes" : "No"
                    );
                }
            ),
            MenuItem(
                []() -> String {
                    bool btEnabled = bluetooth::bluetoothIsEnabled();
                    return String("BT: ") + String(
                        btEnabled ? "Yes" : "No"
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
                    uint32 logErrorCode = Log.getErrorCode();
                    return String("Logging: ") + String(
                        logErrorCode == 0 ? "Yes" : "No"
                    );
                }
            ),
            MenuItem(
                []() -> String {
                    return String("Batt V: ") + String(
                        power::getVoltage(VOLTAGE_BATTERY),
                        2
                    );
                }
            ),
            MenuItem(
                []() -> String {
                    return String("Dyn V: ") + String(
                        power::getVoltage(VOLTAGE_DYNAMO),
                        2
                    );
                }
            ),
            MenuItem(
                []() -> String {
                    return String("Current: ") + String(
                        power::getCurrentUsage(),
                        2
                    );
                }
            ),
        };
    MenuList statsMenuList(statsMenuItems, COUNT_OF(statsMenuItems));
MenuItem statsMenu("Stats", &statsMenuList);
                MenuItem dynamoEnMenuOptions[] = {
                    MenuItem(
                        "Enable",
                        []() -> void {
                            power::enableDynamoPower(true);
                        }
                    ),
                    MenuItem(
                        "Disable",
                        []() -> void {
                            power::enableDynamoPower(false);
                        }
                    )
                };
            MenuList dynamoEnMenuList(dynamoEnMenuOptions, COUNT_OF(dynamoEnMenuOptions));
                MenuItem autosleepMenuOptions[] = {
                    MenuItem(
                        "Enable",
                        console::enableAutosleep
                    ),
                    MenuItem(
                        "Disable",
                        console::disableAutosleep
                    )
                };
            MenuList autosleepMenuList(autosleepMenuOptions, COUNT_OF(autosleepMenuOptions));
        MenuItem powerMenuItems[] = {
            MenuItem(
                "Power Off",
                console::sleep
            ),
            MenuItem(
                "Dynamo",
                &dynamoEnMenuList
            ),
            MenuItem(
                "Autosleep",
                &autosleepMenuList
            ),
            MenuItem(
                "Reset",
                console::reset
            )
        };
    MenuList powerMenuList(powerMenuItems, COUNT_OF(powerMenuItems));
MenuItem powerMenu("Power", &powerMenuList);

                MenuItem presetOptions[] = {
                    MenuItem(
                        "Safety",
                        []() -> void {
                            neopixel::activatePreset(LED_PRESET_SAFETY);
                        }
                    ),
                    MenuItem(
                        "Midnight",
                        []() -> void {
                            neopixel::activatePreset(LED_PRESET_MIDNIGHT);
                        }
                    ),
                    MenuItem(
                        "Rainbow",
                        []() -> void {
                            neopixel::activatePreset(LED_PRESET_RAINBOW);
                        }
                    )
                };
            MenuList presetMenuList(presetOptions, COUNT_OF(presetOptions));
                MenuItem cycleOptions[] = {
                    MenuItem(
                        "On",
                        []() -> void {
                            neopixel::setCycle(LED_CYCLE_ON);
                        }
                    ),
                    MenuItem(
                        "Off",
                        []() -> void {
                            neopixel::setCycle(LED_CYCLE_OFF);
                        }
                    ),
                    MenuItem(
                        "Random",
                        []() -> void {
                            neopixel::setCycle(LED_CYCLE_RANDOM);
                        }
                    ),
                    MenuItem(
                        "Motion",
                        []() -> void {
                            neopixel::setCycle(LED_CYCLE_MOTION);
                        }
                    ),
                    MenuItem(
                        "Blink",
                        []() -> void {
                            neopixel::setCycle(LED_CYCLE_BLINK);
                        }
                    ),
                    MenuItem(
                        "Rotation",
                        []() -> void {
                            neopixel::setCycle(LED_CYCLE_ROTATION);
                        }
                    )
                };
            MenuList cycleMenuList(cycleOptions, COUNT_OF(cycleOptions));
                MenuItem brightnessOptions[] = {
                    MenuItem(
                        "100%",
                        []() -> void {
                            neopixel::setMaxBrightness(255);
                        }
                    ),
                    MenuItem(
                        "90%",
                        []() -> void {
                            neopixel::setMaxBrightness(205);
                        }
                    ),
                    MenuItem(
                        "80%",
                        []() -> void {
                            neopixel::setMaxBrightness(158);
                        }
                    ),
                    MenuItem(
                        "70%",
                        []() -> void {
                            neopixel::setMaxBrightness(111);
                        }
                    ),
                    MenuItem(
                        "60%",
                        []() -> void {
                            neopixel::setMaxBrightness(64);
                        }
                    ),
                    MenuItem(
                        "50%",
                        []() -> void {
                            neopixel::setMaxBrightness(32);
                        }
                    ),
                    MenuItem(
                        "40%",
                        []() -> void {
                            neopixel::setMaxBrightness(16);
                        }
                    ),
                    MenuItem(
                        "30%",
                        []() -> void {
                            neopixel::setMaxBrightness(8);
                        }
                    ),
                    MenuItem(
                        "20%",
                        []() -> void {
                            neopixel::setMaxBrightness(4);
                        }
                    ),
                    MenuItem(
                        "10%",
                        []() -> void {
                            neopixel::setMaxBrightness(2);
                        }
                    ),
                    MenuItem(
                        "0%",
                        []() -> void {
                            neopixel::setMaxBrightness(0);
                        }
                    )
                };
            MenuList brightnessMenuList(brightnessOptions, COUNT_OF(brightnessOptions));
            /*
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
                            LedStatus status;
                            neopixel::getStatus(status);
                            return "-Red (" + String(status.red) + ")";
                        },
                        []() -> void {
                            LedStatus status;
                            neopixel::getStatus(status);
                            status.red -= colorStep;
                            if(status.red < 0) {
                                status.red = 0;
                            }
                            neopixel::setColor(
                                status.red,
                                status.green,
                                status.blue,
                            );
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
        */
        MenuItem lightingMenuItems[] = {
            MenuItem(
                "Enable",
                []() -> void {neopixel::enable(true);}
            ),
            MenuItem(
                "Disable",
                []() -> void {neopixel::enable(false);}
            ),
            MenuItem(
                "Presets",
                &presetMenuList
            ),
            /*
            MenuItem(
                "Color #1",
                &color1MenuList
            ),
            MenuItem(
                "Color #2",
                &color2MenuList
            ),
            */
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
/*

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
            */
            /*
            MenuItem(
                []() -> String {
                    CANStatusMainMC status = getStatusMainMc();
                    return String("Connected: ") + String(
                        status.camera_connected ? "Yes" : "No"
                    );
                },
                &cameraConnectionList
            ),
            MenuItem(
                "Delete Media",
                deleteCameraMedia
            )
        };
    MenuList cameraMenuList(cameraMenuItems, COUNT_OF(cameraMenuItems));
MenuItem cameraMenu("Camera", &cameraMenuList);
*/

                MenuItem localBluetoothMenuItems[] = {
                    MenuItem(
                        "Disable",
                        console::disableBluetooth
                    ),
                    MenuItem(
                        "Enable",
                        console::enableBluetooth
                    )
                };
            MenuList localBluetoothMenuList(localBluetoothMenuItems, COUNT_OF(localBluetoothMenuItems));

                MenuItem baseLTEMenuItems[] = {
                    MenuItem(
                        "Disable",
                        console::disableLTE
                    ),
                    MenuItem(
                        "Enable",
                        console::enableLTE
                    )
                };
            MenuList baseLTEMenuList(baseLTEMenuItems, COUNT_OF(baseLTEMenuItems));

                MenuItem gpsMenuItems[] = {
                    MenuItem(
                        "Disable",
                        []() -> void {
                            status::gpsEnable(false);
                        }
                    ),
                    MenuItem(
                        "Enable",
                        []() -> void {
                            status::gpsEnable(true);
                        }
                    )
                };
            MenuList gpsMenuList(gpsMenuItems, COUNT_OF(gpsMenuItems));

        MenuItem commsMenuItems[] = {
            MenuItem(
                "BT",
                &localBluetoothMenuList
            ),
            MenuItem(
                "LTE",
                &baseLTEMenuList
            ),
            MenuItem(
                "GPS",
                &gpsMenuList
            )
        };
    MenuList commsMenuList(commsMenuItems, COUNT_OF(commsMenuItems));
MenuItem commsMenu("Radio", &commsMenuList);


                MenuItem menuTimeoutMenuItems[] = {
                    MenuItem(
                        "Disable",
                        [](){Display.enableTimeout(false);}
                    ),
                    MenuItem(
                        "Enable",
                        [](){Display.enableTimeout(true);}
                    )
                };
            MenuList menuTimeoutMenuList(menuTimeoutMenuItems, COUNT_OF(menuTimeoutMenuItems));
                MenuItem menuBacklightMenuItems[] = {
                    MenuItem(
                        "Disable",
                        [](){Display.enableBacklight(false);}
                    ),
                    MenuItem(
                        "Enable",
                        [](){Display.enableBacklight(true);}
                    )
                };
            MenuList menuBacklightMenuList(menuBacklightMenuItems, COUNT_OF(menuBacklightMenuItems));
        MenuItem menuMenuItems[] = {
            MenuItem(
                "Backlight",
                &menuBacklightMenuList
            ),
            MenuItem(
                "Timeout",
                &menuTimeoutMenuList
            )
        };
    MenuList menuMenuList(menuMenuItems, COUNT_OF(menuMenuItems));
MenuItem menuMenu("Menu ", &menuMenuList);

MenuItem mainMenuItems[] = {
    statsMenu,
    powerMenu,
    menuMenu,
    commsMenu,
    //cameraMenu,
    lightingMenu
};
MenuList mainMenu(mainMenuItems, COUNT_OF(mainMenuItems));
