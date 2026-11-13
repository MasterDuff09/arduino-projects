# OTA-Tester

## Overview

The `ota-tester.ino` sketch is a simple web server running on an ESP32 microcontroller. It allows users to log in via a web interface and perform over-the-air (OTA) firmware updates. The server provides a login page for authentication and an update page for uploading and applying new firmware.

## Features

1. **Web Interface**:
   - **Login Page**: Users can log in using a username and password.
   - **Update Page**: Users can upload a new firmware file and initiate an OTA update.

2. **OTA Updates**:
   - The server handles the upload of a new firmware file and applies it to the ESP32.
   - Progress of the update is displayed on the web page.

3. **Blink LED**:
   - The ESP32 blinks an LED connected to GPIO 2 (LED_BUILTIN) to indicate its operational status.

## Hardware Requirements

- ESP32 Development Board
- LED (optional, for blinking)
- Jumper wires

## Software Requirements

- Arduino IDE
- ESP32 Board Support Package (installed via the Boards Manager)

## Installation

1. **Install ESP32 Board Support Package**:
   - Open the Arduino IDE.
   - Go to `File` > `Preferences`.
   - In the `Additional Board Manager URLs` field, add the following URL:
     ```
     https://dl.espressif.com/dl/package_esp32_index.json
     ```
   - Go to `Tools` > `Board` > `Boards Manager`.
   - Search for `esp32` and install the package.

2. **Upload the Code**:
   - Open the `ota-tester.ino` file in the Arduino IDE.
   - Select the correct board and port from the `Tools` menu.
   - Click the `Upload` button to upload the code to your ESP32.

## Configuration

- **WiFi Credentials**:
  - The code is configured to connect to a WiFi network with the SSID `ESP-32` and password `Password!`.
  - You can change these credentials by modifying the `ssid` and `password` variables in the code.

- **LED Pin**:
  - The LED is connected to GPIO 2 (LED_BUILTIN) by default.
  - You can change the LED pin by modifying the `pinMode` and `digitalWrite` calls in the `setup` function.

## Usage

1. **Connect to the Web Server**:
   - Once the code is uploaded, open a web browser and navigate to `http://esp32.local`.
   - You should see the login page.

2. **Log In**:
   - Enter the username `admin` and password `admin` to log in.

3. **Perform an OTA Update**:
   - Click on the "Update" button and select a new firmware file to upload.
   - The progress of the update will be displayed on the web page.

4. **Blink LED**:
   - The LED connected to GPIO 2 will blink every second to indicate that the ESP32 is operational.

## Troubleshooting

- **MDNS Resolution**:
  - If the ESP32 fails to start the mDNS responder, you may need to check the network settings or try a different network.

- **OTA Update Issues**:
  - If the OTA update fails, check the serial output for error messages.
  - Ensure that the firmware file is compatible with the ESP32 and is not corrupted.

## Contributing

Contributions are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.
