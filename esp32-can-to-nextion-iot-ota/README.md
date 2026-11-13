# ESP32-CAN-to-Nextion-IoT-OTA

This project is designed to integrate an ESP32 microcontroller with a CAN bus for data transmission and a Nextion display for user interaction. It also includes over-the-air (OTA) firmware updates for seamless software upgrades.

## Table of Contents
1. [Features](#features)
2. [Hardware Requirements](#hardware-requirements)
3. [Software Requirements](#software-requirements)
4. [Setup](#setup)
5. [Usage](#usage)
6. [OTA Updates](#ota-updates)
7. [Contributing](#contributing)
8. [License](#license)

## Features
- **CAN Bus Integration**: Communicates with devices on a CAN bus.
- **Nextion Display**: Provides a user interface for controlling the device.
- **Over-the-Air (OTA) Updates**: Allows firmware updates without physical access.

## Hardware Requirements
- ESP32 Development Board
- CAN Bus Shield
- Nextion Display
- Various CAN Bus devices (optional)

## Software Requirements
- Arduino IDE
- ESP32 Board Manager
- Nextion Editor

## Setup
1. **Install ESP32 Board Manager**:
   - Open Arduino IDE.
   - Go to `File` > `Preferences`.
   - In the `Additional Board Manager URLs` field, add `https://dl.espressif.com/dl/package_esp32_index.json`.
   - Go to `Tools` > `Board` > `Boards Manager`.
   - Search for `esp32` and install it.

2. **Install Nextion Editor**:
   - Download and install the Nextion Editor from [Nextion Technology](https://nextion.tech/nextion-editor/#_section1).

3. **Connect Hardware**:
   - Connect the ESP32 to the CAN Bus Shield.
   - Connect the Nextion Display to the ESP32.

4. **Upload Code**:
   - Open the `esp32-can-to-nextion-iot-ota.ino` file in Arduino IDE.
   - Select the correct board and port.
   - Upload the code to the ESP32.

## Usage
1. **Start Connection**:
   - Press the "start connection" button on the Nextion display.
   - The ESP32 will attempt to connect to the WiFi network.
   - If successful, it will initialize properties and start OTA updates.

2. **Interrupt Connection**:
   - Press the "interrupted connection" button to stop the connection process.

## OTA Updates
- The ESP32 supports OTA updates, allowing you to update the firmware without physical access.
- The `OTAFlash.h` file contains the necessary functions for handling OTA updates.

## Contributing
Contributions are welcome! Please fork the repository and submit a pull request.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
``