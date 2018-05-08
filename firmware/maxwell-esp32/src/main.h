#pragma once

#define MAX_SEND_WAIT 1000
#define STATUS_INTERVAL 1000
#define GOPRO_STATUS_INTERVAL 5000
#define CONNECTION_TIMEOUT 2000

#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" // UART service UUID
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

#define GOPRO_HOST "10.5.5.9"
#define GOPRO_PORT 80
#define CAMERA_WIFI_SSID "GP55227416"
#define CAMERA_WIFI_PWD "dude1630"

void setup();
void loop();
void sendStatus();

void stopBle();
void startBle();
void sendNow();

int sendGoproCommand(String, char*);
int sendGoproCommand(String);
void updateGoproStatus();
void deleteGoproMedia();
void connectCamera();
void disconnectCamera();
void powerOffCamera();
void startRecording();
void stopRecording();

struct CameraStatusContainer {
    bool recordingNow;

    uint32_t lastUpdated;

    uint32_t batteryLevel;
    uint32_t bytesAvailable;
};

extern HardwareSerial Ctrl;
extern HardwareSerial Output;
extern CameraStatusContainer CameraStatus;
