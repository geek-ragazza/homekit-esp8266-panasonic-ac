#include "thermostat.h"

Thermostat::Thermostat() : oneWire(TEMP_SENSOR_PIN), sensors(&oneWire), ac(IR_TRANSMITTER_PIN), server(80) {
  jsonDocument["targetHeatingCoolingState"] = 2;
  jsonDocument["targetTemperature"] = 25.0;
  jsonDocument["currentHeatingCoolingState"] = 0;
}


void Thermostat::setupWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void Thermostat::setupServer() {
    server.on("/temperature", [this]() {
        handleTemperature();
    });
    server.on("/thermostat/status", [this]() {
        handleInitialThermostat();
    });
    server.on("/thermostat/targetHeatingCoolingState", [this]() {
        handlesetTargetHeatingCoolingState();
    });
    server.on("/thermostat/targetTemperature", [this]() {
        handletargetTemperature();
    });
    server.begin();
    Serial.println("HTTP server started");
}
void Thermostat::setupTemperatureSensor() {
  sensors.begin();
}

void Thermostat::handleTemperature() {
  sensors.requestTemperatures();
  temperature = sensors.getTempCByIndex(0);
  String temperatureString = String(temperature);
  server.send(200, "text/plain", temperatureString);
}

void Thermostat::setupIRTransmitter(){
  pinMode(IR_TRANSMITTER_PIN, OUTPUT);
}


void Thermostat::printState() {
  Serial.println("Panasonic A/C remote is in the following state:");
  Serial.printf("  %s\n", ac.toString().c_str());
  unsigned char* ir_code = ac.getRaw();
  Serial.print("IR Code: 0x");
  for (uint8_t i = 0; i < kPanasonicAcStateLength; i++)
    Serial.printf("%02X", ir_code[i]);
  Serial.println();
}

void Thermostat::turnOnAC(int targetTemperature) {
  // Set up what we want to send. See ir_Panasonic.cpp for all the options.
  Serial.println("Default state of the remote.");
  printState();
  Serial.println("Setting desired state for A/C.");
  ac.setModel(kPanasonicDke);
  ac.on();
  ac.setFan(kPanasonicAcFanAuto);
  ac.setMode(kPanasonicAcCool);
  ac.setTemp(targetTemperature);
  ac.setSwingVertical(kPanasonicAcSwingVAuto);
  ac.setSwingHorizontal(kPanasonicAcSwingHAuto);
  ac.send();
  delay(50); // Wait for the IR signal to be sent
  
}

void Thermostat::turnOffAC() {
    Serial.println("Default state of the remote.");
    printState();
    Serial.println("Turn off the AC");
    ac.setModel(kPanasonicDke);
    ac.off();
    ac.send();
    delay(50); // Wait for the IR signal to be sent
}

void Thermostat::handleInitialThermostat() {
  setupTemperatureSensor();  // Initialize the temperature sensor

  float temperature = sensors.getTempCByIndex(0);
  String temperatureString = String(temperature);

  // Set the values in the JSON document
  jsonDocument["currentTemperature"] = temperatureString; // Replace with the desired float value

  // Serialize the JSON document to a string
  String jsonString;
  serializeJson(jsonDocument, jsonString);

  // Set the Content-Type header to application/json
  server.sendHeader("Content-Type", "application/json");

  // Send the JSON response with the appropriate HTTP status code
  server.send(200, "application/json", jsonString);
}


void Thermostat::handlesetTargetHeatingCoolingState() {
  String value = server.arg("value");
  int targetHeatingCoolingState = value.toInt();
  // Set the values in the JSON document
  jsonDocument["targetHeatingCoolingState"] = targetHeatingCoolingState;

  if (targetHeatingCoolingState == 0) {
    turnOffAC();
    // Update the current heating/cooling state
    jsonDocument["currentHeatingCoolingState"] = targetHeatingCoolingState;
  } else {
    // Update the current heating/cooling state
    jsonDocument["currentHeatingCoolingState"] = targetHeatingCoolingState;
    // Set the desired heating/cooling state
    // (e.g., turn on the AC, set to cooling mode)
    // You can modify this part based on your specific requirements
    turnOnAC(25);
  }

  // Serialize the JSON document to a string
  String jsonString;
  serializeJson(jsonDocument, jsonString);

  // Set the Content-Type header to application/json
  server.sendHeader("Content-Type", "application/json");

  // Send the JSON response with the appropriate HTTP status code
  server.send(200, "application/json", jsonString);

}

void Thermostat::handletargetTemperature() {
  String value = server.arg("value");
  Serial.println("Received value: " + value);

  // Convert the value to an integer
  int targetTemperature = value.toInt();
  // Set the values in the JSON document
  jsonDocument["targetTemperature"] = targetTemperature;
  // Turn on the AC
  //ac.setTemp(targetTemperature);
  turnOnAC(targetTemperature);
 
  String jsonString;
  
  serializeJson(jsonDocument, jsonString);

  // Set the Content-Type header to application/json
  server.sendHeader("Content-Type", "application/json");

  // Send the JSON response with the appropriate HTTP status code
  server.send(200, "application/json", jsonString);
  Serial.println("Updated state of the remote:");
  printState();
}



