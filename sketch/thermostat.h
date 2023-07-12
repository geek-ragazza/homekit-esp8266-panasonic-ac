#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRsend.h>
#include <ir_Panasonic.h>
#include <ArduinoJson.h>
#include "settings.h"

class Thermostat {
public:
  float temperature;
  OneWire oneWire;
  DallasTemperature sensors;
  IRPanasonicAc ac;
  StaticJsonDocument<200> jsonDocument;
  ESP8266WebServer server;

  Thermostat();
  void setupWiFi();
  void setupTemperatureSensor();
  void setupIRTransmitter();
  void setupServer();
  void handleTemperature();
  void turnOnAC(int targetTemperature);
  void turnOffAC();
  void handleInitialThermostat();
  void handlesetTargetHeatingCoolingState();
  void handletargetTemperature();

private:
  void printState();
};

#endif  // THERMOSTAT_H



