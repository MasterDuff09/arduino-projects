# PulseOximeter-IoT
A project for a pulse oximeter IoT device

## Overview
This project is designed to connect a pulse oximeter sensor to the internet using a microcontroller (likely an Arduino board). The device measures the oxygen saturation (SpO2) of a patient and sends the data to the cloud.

## Requirements

* Arduino board (e.g., Arduino Uno, Arduino Nano)
* Pulse oximeter sensor (e.g., MAX30100)
* Internet connectivity (e.g., Wi-Fi, Ethernet)
* Cloud account (e.g., Arduino Cloud)

## Installation

1. Clone the repository using Git
2. Install the required libraries:
	* ArduinoCloud
	* ArduinoIoTPreferredConnection
3. Upload the `pulseoximeter-iot.ino` file to your Arduino board
4. Configure your cloud account and device settings in the `thingProperties.h` file

## Usage

1. Connect the pulse oximeter sensor to your Arduino board
2. Upload the `pulseoximeter-iot.ino` file to your Arduino board
3. The device will connect to the cloud and send SpO2 data
4. Use the cloud account to view and analyze the data

## Contributing
Contributions are welcome! Please fork the repository and submit a pull request with your changes.

## License
This project is licensed under the [MIT License](https://opensource.org/licenses/MIT).

## Credits
This project is based on the [Arduino Cloud](https://www.arduino.cc/en/Reference/Cloud) library and the [Arduino IoT](https://www.arduino.cc/en/Reference/IoT) library.