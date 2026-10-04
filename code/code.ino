// Home Automation: control a 2-channel relay module from the Blynk IoT app
// Board: NodeMCU ESP8266
//
// Wiring
//   Relay module  VCC -> Vin (5 V)   GND -> GND   IN1 -> D1   IN2 -> D2
//
// Blynk: create two datastreams (Integer, 0 to 1) and add two Switch widgets
//   V0 -> Relay 1     V1 -> Relay 2

#define BLYNK_TEMPLATE_ID   "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Home Automation"
#define BLYNK_AUTH_TOKEN    "YOUR_BLYNK_AUTH_TOKEN"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

#define RELAY1 D1
#define RELAY2 D2

// This relay board is active-LOW: LOW switches the relay ON, HIGH switches it OFF.
// If your board works the opposite way, swap LOW and HIGH below.

BLYNK_WRITE(V0) {                                   // Switch 1 in the app
  digitalWrite(RELAY1, param.asInt() ? LOW : HIGH);
}

BLYNK_WRITE(V1) {                                   // Switch 2 in the app
  digitalWrite(RELAY2, param.asInt() ? LOW : HIGH);
}

BLYNK_CONNECTED() {                                 // after every (re)connect, show both as OFF
  Blynk.virtualWrite(V0, 0);
  Blynk.virtualWrite(V1, 0);
}

void setup() {
  digitalWrite(RELAY1, HIGH);                       // both relays OFF at start-up
  digitalWrite(RELAY2, HIGH);
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();
}
