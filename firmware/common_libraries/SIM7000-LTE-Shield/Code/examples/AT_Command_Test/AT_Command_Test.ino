/* This code allows you to freely test AT commands by entering them into
 *  the serial monitor! You can type in "ON" to turn on the
 *  SIM7000 and "OFF" to turn it off, as well as "RESET" and "BAUD<value>"
 *  to set a new baud rate! Please note that you should set the serial
 *  monitor to "No line ending"
 *  
 *  Asterisks (***) indicate debug text and arrows (-->) indicate sending
 *  an AT command. Everything else is a response from the module!
 *  
 *  Another way to experiment with AT commands is to use the
 *  "AT Command Library" here: https://github.com/botletics/AT-Command-Library
 *  
 *  Author: Timothy Woo (www.botletics.com)
 *  Github: https://github.com/botletics/NB-IoT-Shield
 *  Last Updated: 4/24/2018
 *  License: GNU GPL v3.0
 */

#include <SoftwareSerial.h> // This is for communicating with the SIM7000 module

// For SIM7000 shield
#define FONA_PWRKEY 6
#define FONA_RST 7
//#define FONA_DTR 8 // Connect with solder jumper
//#define FONA_RI 9 // Need to enable via AT commands
#define FONA_TX 10 // Microcontroller RX
#define FONA_RX 11 // Microcontroller TX
//#define T_ALERT 12 // Connect with solder jumper

// For SIM7500 shield
//#define FONA_PWRKEY 6
//#define FONA_RST 7
////#define FONA_DTR 9 // Connect with solder jumper
////#define FONA_RI 8 // Need to enable via AT commands
//#define FONA_TX 11 // Microcontroller RX
//#define FONA_RX 10 // Microcontroller TX
////#define T_ALERT 5 // Connect with solder jumper

SoftwareSerial fona = SoftwareSerial(FONA_TX, FONA_RX);

uint32_t baudRate;

void setup() {
  Serial.begin(115200);
  Serial.println("*****AT Command Test*****");

  pinMode(FONA_PWRKEY, OUTPUT);
  digitalWrite(FONA_PWRKEY, HIGH);
  pinMode(FONA_RST, OUTPUT);
  digitalWrite(FONA_RST, HIGH);

  FONApower(true); // Turn on the shield
  delay(4000); // Let the shield power up

  // Hard-code baud rate
  // Can use the "BAUD" command to switch baud rate
  // at any time in case of a baud rate mismatch
  fona.begin(115200); // Default baud rate
//  fona.begin(4800);
  
  Serial.println("Turning off echo!");
  fona.println(" --> ATE0"); // Turn off echo
}

void loop() {
  if (Serial.available()) {
    String userCmd = Serial.readString();

    if (userCmd == "ON") FONApower(true);
    else if (userCmd == "OFF") FONApower(false);
    else if (userCmd == "RESET") FONAreset();
    else if (userCmd == "FACTORY") facReset();
    else if (userCmd.startsWith("BAUD")) {
      baudRate = userCmd.substring(4).toInt();
      Serial.print("*** Switching to "); Serial.print(baudRate); Serial.println(" baud");
      Serial.print(" --> ");
      fona.println("AT+IPR=" + String(baudRate));
      delay(100); // Give it some time to chill
      fona.begin(baudRate);
    }
    else {
      Serial.print(" --> ");
      Serial.print(userCmd);
      fona.println(userCmd);
    }
  }
  
  if (fona.available()) {
    Serial.write(fona.read());
  }
}

void flushInput() {
  while (Serial.available()) {
    char c = Serial.read(); // Flush pending data
  }
}

// This function turns the SIM7000 on or off.
// Enter "ON" or "OFF" in the serial monitor
void FONApower(bool option) {
  if (option) {
    Serial.println("*** Turning ON (takes about 4.2s)");
    digitalWrite(FONA_PWRKEY, LOW);
    delay(200); // At least 72ms for SIM7000 and at least 100ms for SIM7500
    digitalWrite(FONA_PWRKEY, HIGH);
  }
  else {
    Serial.println("*** Turning OFF (takes about 1.3s)");
    fona.println("AT+CPOWD=1");
    
    // Alternatively, pulse PWRKEY:
//    digitalWrite(FONA_PWRKEY, LOW);
//    delay(1400); // At least 1.2s for SIM7000, at least 2.5s for SIM7500
//    digitalWrite(FONA_PWRKEY, HIGH);
  }
}

// This function resets the FONA, used mainly in the case of an emergency!
void FONAreset() {
  Serial.println("*** Resetting module...");
  digitalWrite(FONA_RST, LOW);
  delay(100); // Between 50-500ms
  digitalWrite(FONA_RST, HIGH);
}

// This function factory resets the SIM7000
void facReset() {
  Serial.println("*** Factory resetting...");
  Serial.print(" --> AT&F0");
  fona.println("AT&F0");
}
