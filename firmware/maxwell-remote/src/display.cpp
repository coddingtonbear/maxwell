#include <Adafruit_SSD1306.h>
#include "display.h"

extern Adafruit_SSD1306 display(-1);

DisplayManager::DisplayManager() {
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
    display.setCursor(0, 0);
    display.println("0123456789012345");
    display.display();
}

void DisplayManager::refresh() {
}


DisplayManager Display;
