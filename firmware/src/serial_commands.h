#include <SerialCommand.h>

void setupCommands();
void commandPrompt();
void commandLoop();

void unrecognized(const char *command);
void uptime();
void reset();
void programmingMode();
void hello();
void bluetooth();
void voltageMeasurement();
void isChargingNow();
void currentUsage();
void beep();
void auxDevicesEnable();
void charge();
void led();
