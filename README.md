# HomeKit ESP8266 Panasonic AC

This repository contains the code and configuration files for a HomeKit ESP8266 Panasonic AC controller. With this project, you can control your Panasonic air conditioner remotely using Apple's HomeKit platform.

## Project Overview

Tired of coming home to a sweltering hot apartment? Wish you could magically summon a cool breeze at your command? Look no further! The HomeKit ESP8266 Panasonic AC Controller is here to save the day (and your comfort).

This project combines the power of the ESP8266 development board, a DS18B20, temperature sensor, an IR transmitter, and some coding magic to create a smart AC controller that integrates seamlessly with Apple's HomeKit platform. Say goodbye to sweaty summer days and hello to the perfect indoor climate!

## Materials Required

To build the HomeKit ESP8266 Panasonic AC controller, you will need the following materials:

-   ESP8266 (e.g., NodeMCU or Wemos D1 Mini)
-   DS18B20 temperature sensor
-   IR transmitter module
-   Jumper wires
-   Breadboard or perfboard for prototyping
-   Raspberry Pi (for hosting Homebridge)

## Prerequisites

Before setting up the controller, make sure you have the following prerequisites:

1.  Raspberry Pi: Install Homebridge on your Raspberry Pi by following the instructions provided in the [Homebridge Wiki](https://github.com/homebridge/homebridge/wiki/Install-Homebridge-on-Raspbian). Homebridge will serve as the HomeKit host for the AC controller.
    
2.  Homebridge Plugins: Install the following Homebridge plugins on your Raspberry Pi:
    
    -   [Homebridge Http Temperature Sensor](https://github.com/KraigM/homebridge-http-temperature-sensor): This plugin allows Homebridge to communicate with the ESP8266 to retrieve the current temperature readings.
        
    -   [Homebridge Web Thermostat](https://github.com/Supereg/homebridge-web-thermostat): This plugin enables Homebridge to control the AC by sending commands to the ESP8266.
    
## Configuration

1.  Modify the pin configuration in the `settings.h` file located in the `sketch` directory. This file contains the necessary settings for the ESP8266 board, including the baud rate, IR transmitter pin, temperature sensor pin, and Wi-Fi credentials. Update the following values according to your setup:
    

```cpp
/* Pin Setup */
#define ESP_BAUD              9600
#define IR_TRANSMITTER_PIN    D7
#define TEMP_SENSOR_PIN       D3

/* Wi-Fi Settings */
#define WIFI_SSID             "your-wifi-ssid"
#define WIFI_PASSWORD         "your-wifi-password"

```


2.  Upload the `thermostat.ino` file to your ESP8266 board using the Arduino IDE or your preferred method.
    
3.  Connect the DS18B20 temperature sensor and IR transmitter module to the appropriate GPIO pins on the ESP8266 board. Refer to the pin configuration in the `settings.h` file.
    
4.  Power on the ESP8266 board and ensure that it connects to your Wi-Fi network.
    
5.  Edit the `config.json` file in the repository to configure your Homebridge settings. Update the accessory name, port, and any other relevant settings. You may need to refer to the documentation of the Homebridge plugins for more detailed configuration instructions.
    
6.  Start Homebridge on your Raspberry Pi. Get ready to unleash the magic of your smart AC controller!

## Usage

Once the setup is complete, open the Home app on your iOS device and behold the power of HomeKit ESP8266 Panasonic AC Controller. From the palm of your hand, you can now control your air conditioner with just a few taps.

Adjust the target temperature, turn the AC on or off, and revel in the coolness of your smart home oasis. Say goodbye to sweaty summer days and hello to comfort at your fingertips!

And don't forget to test the range of your IR transmitter. Start by pretending to be a Jedi, waving your hand in front of the AC unit, and watching the magic happen. Experiment with different distances and angles to find that perfect sweet spot.

Remember, with great power comes great responsibility (and a whole lot of coolness).

## Contributing

Contributions to this project are welcome! If you find any issues or have suggestions for improvements, feel free to open an issue or submit a pull request.