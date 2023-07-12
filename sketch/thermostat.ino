#include <Arduino.h>
#include "settings.h"
#include "thermostat.h"

Thermostat thermostat;

void setup() {
  Serial.begin(ESP_BAUD);
  thermostat.setupWiFi();
  thermostat.setupTemperatureSensor();
  thermostat.setupIRTransmitter();
  thermostat.setupServer();

}

void loop() {
  thermostat.server.handleClient();
}
