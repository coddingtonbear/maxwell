/*
    Video: https://www.youtube.com/watch?v=oCMOYS71NIU
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleNotify.cpp
    Ported to Arduino ESP32 by Evandro Copercini
   Create a BLE server that, once we receive a connection, will send periodic notifications.
   The service advertises itself as: 6E400001-B5A3-F393-E0A9-E50E24DCCA9E
   Has a characteristic of: 6E400002-B5A3-F393-E0A9-E50E24DCCA9E - used for receiving data with "WRITE" 
   Has a characteristic of: 6E400003-B5A3-F393-E0A9-E50E24DCCA9E - used to send data with  "NOTIFY"
   The design of creating the BLE server is:
   1. Create a BLE Server
   2. Create a BLE Service
   3. Create a BLE Characteristic on the Service
   4. Create a BLE Descriptor on the characteristic
   5. Start the service.
   6. Start advertising.
   In this example rxValue is the data received (only accessible inside that function).
   And txValue is the data to be sent, in this example just a byte incremented every second. 
*/
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <esp_wifi.h>

#include "main.h"
#include "serial_commands.h"

bool bleReleased = false;
bool bleEnabled = false;

BLECharacteristic *pCharacteristic;
bool deviceConnected = false;
uint8_t txValue = 0;

WiFiClient client;

CameraStatusContainer CameraStatus;

unsigned long lastStatus = 0;
unsigned long lastGoproStatus = 0;

char outputBuffer[4096];

HardwareSerial Output(0);
HardwareSerial Ctrl(1);

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();

      if (rxValue.length() > 0) {
        for (int i = 0; i < rxValue.length(); i++){
          Output.print(rxValue[i]);
        }
      }
    }
};


void startBle() {
    if(bleReleased) {
        return;
    }

    Output.begin(230400, SERIAL_8E1);

    // Create the BLE Device
    BLEDevice::init("Maxwell");

    // Create the BLE Server
    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    // Create the BLE Service
    BLEService *pService = pServer->createService(SERVICE_UUID);

    // Create a BLE Characteristic
    pCharacteristic = pService->createCharacteristic(
                        CHARACTERISTIC_UUID_TX,
                        BLECharacteristic::PROPERTY_NOTIFY
                      );
                        
    pCharacteristic->addDescriptor(new BLE2902());

    BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                           CHARACTERISTIC_UUID_RX,
                                           BLECharacteristic::PROPERTY_WRITE
                                         );

    pCharacteristic->setCallbacks(new MyCallbacks());

    // Start the service
    pService->start();

    // Start advertising
    pServer->getAdvertising()->start();

    bleEnabled = true;
}

void stopBle() {
    btStop();
}

void setup() {
    Ctrl.begin(9600);

    delay(250);

    Ctrl.println("Ready");
    Ctrl.flush();

    sendStatus();

    setupCommands();
}

String sendValue = "";
unsigned long lastSend = 0;

void sendNow() {
    pCharacteristic->setValue((std::string)sendValue.c_str());
    pCharacteristic->notify();
    sendValue = "";
    lastSend = millis();
}

void sendStatus() {
    DynamicJsonBuffer jsonBuffer(512);
    JsonObject& root = jsonBuffer.createObject();

    root["messageClass"] = "status";
    root["uptime"] = millis();
    root["memoryAvailable"] = ESP.getFreeHeap();

    root["bleEnabled"] = bleEnabled;

    root["cameraConnected"] = WiFi.status() == WL_CONNECTED;
    root["wifiStatus"] = (int)WiFi.status();

    root["localIp"] = String(WiFi.localIP());

    JsonObject& status = root.createNestedObject("cameraStatus");

    status["lastUpdated"] = CameraStatus.lastUpdated;
    status["recordingNow"] = CameraStatus.recordingNow;
    status["batteryLevel"] = CameraStatus.batteryLevel;
    status["bytesAvailable"] = CameraStatus.bytesAvailable;

    root.printTo(Ctrl);
    Ctrl.println();

    lastStatus = millis();
}

void updateGoproStatus() {
    int httpCode = sendGoproCommand("/gp/gpControl/status", outputBuffer);
    
    if(httpCode == 200) {
        DynamicJsonBuffer cameraStatus(2048);

        JsonObject& root = cameraStatus.parseObject(outputBuffer);

        CameraStatus.lastUpdated = millis();
        CameraStatus.batteryLevel = root["status"]["2"];
        CameraStatus.bytesAvailable = root["status"]["54"];
        CameraStatus.recordingNow = root["status"]["8"];
    } else if(httpCode == -101) {
        CameraStatus.recordingNow = false;
        WiFi.disconnect();
        WiFi.reconnect();
    }

    lastGoproStatus = millis();
}

void deleteGoproMedia() {
    int httpCode = sendGoproCommand("/gp/gpControl/command/storage/delete/all");
}

void powerOffCamera() {
    int httpCode = sendGoproCommand("/gp/gpControl/command/system/sleep");
}

void startRecording() {
    int httpCode = sendGoproCommand("/gp/gpControl/command/shutter?p=1");
}

void stopRecording() {
    int httpCode = sendGoproCommand("/gp/gpControl/command/shutter?p=0");
}

int sendGoproCommand(String url, char* buffer) {
    if(!client.connect(GOPRO_HOST, GOPRO_PORT)) {
        return -101;
    }

    client.print("GET " + url + " HTTP/1.1\r\n");
    client.print("Host: " + String(GOPRO_HOST) + "\r\n");
    client.print("Connection: close\r\n\r\n");

    uint16_t bufferPosition = 0;
    bool inHeader = true;

    int returnCode = -100;
    int16_t contentLength = -1;

    char currentLine[4096];
    uint16_t currentLinePos = 0;

    unsigned long timeout = millis() + CONNECTION_TIMEOUT;
    while(millis() < timeout) {
        if(!client.available()) {
            continue;
        }

        char thisChar = client.read();
        currentLine[currentLinePos] = thisChar;
        currentLine[currentLinePos + 1] = '\0';
        currentLinePos++;

        bool forceFlush = false;

        if(
            contentLength > 0
            && bufferPosition + currentLinePos > contentLength
        ) {
            forceFlush = true;
        }

        if(thisChar == '\n' || forceFlush) {
            if(inHeader) {
                String headerLine = String(currentLine);
                headerLine.trim();
                if(returnCode < 0 && headerLine.startsWith("HTTP/1.")) {
                    returnCode = headerLine.substring(9, headerLine.indexOf(' ', 9)).toInt();
                } else if(headerLine.indexOf(':') > -1) {
                    String headerName = headerLine.substring(0, headerLine.indexOf(':'));
                    String headerValue = headerLine.substring(headerLine.indexOf(':') + 1);
                    headerValue.trim();

                    if(headerName.equalsIgnoreCase("Content-Length")) {
                        contentLength = headerValue.toInt();
                    }
                } else if(headerLine == "") {
                    inHeader = false;
                }
            } else {
                if(buffer != NULL) {
                    for(uint16_t i = 0; i < currentLinePos; i++) {
                        buffer[bufferPosition] = currentLine[i];
                        bufferPosition++;
                    }
                }
            }
            currentLine[0] = '\0';
            currentLinePos = 0;
        }
        if(
            contentLength > 0
            && bufferPosition + currentLinePos > contentLength
        ) {
            break;
        }
    }
    if(millis() > timeout) {
        return -102;
    }
    client.stop();

    return returnCode;
}

int sendGoproCommand(String url) {
    sendGoproCommand(url, NULL);
}

void loop() {
    commandLoop();
    if(bleEnabled) {
        while(Output.available()) {
            char byte = Output.read();
            if(deviceConnected) {
                sendValue += String(byte);

                if(byte == '\n') {
                    sendNow();
                }
            }
        }
        if(sendValue.length() > 0 && lastSend + MAX_SEND_WAIT < millis()) {
            sendNow();
        }
    }

    if(lastStatus == 0 || millis() - lastStatus > STATUS_INTERVAL) {
        sendStatus();
    }
    if(
        WiFi.status() == WL_CONNECTED
        && (
            lastGoproStatus == 0
            || millis() - lastGoproStatus > GOPRO_STATUS_INTERVAL
        )
    ) {
        updateGoproStatus();
    }
}

void connectCamera() {
    bleReleased = true;
    esp_bt_controller_mem_release(ESP_BT_MODE_BTDM);
    Output.end();

    if(WiFi.status() == WL_NO_SHIELD) {
        WiFi.begin(CAMERA_WIFI_SSID, CAMERA_WIFI_PWD);
        esp_wifi_set_max_tx_power(0);
    } else {
        WiFi.reconnect();
    }
}

void disconnectCamera() {
    WiFi.disconnect();
    WiFi.mode(WIFI_OFF);
}
