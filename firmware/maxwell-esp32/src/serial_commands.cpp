#include <SerialCommand.h>

#include "serial_commands.h"
#include "main.h"

SerialCommand commands(&Ctrl);

void setupCommands() {
    commands.disableEcho();
    commands.addCommand("start_ble", startBle);
    commands.addCommand("stop_ble", stopBle);

    commands.addCommand("connect_camera", connectCamera);
    commands.addCommand("disconnect_camera", disconnectCamera);
    commands.addCommand("delete_gopro_media", deleteGoproMedia);
    commands.addCommand("start_recording", startRecording);
    commands.addCommand("stop_recording", stopRecording);
    commands.addCommand("power_off_camera", powerOffCamera);
}

void commandLoop() {
    commands.readSerial();
}
