# esp32-can-to-nextion-iot-ota-2

This project is designed to integrate an ESP32 with a CAN bus and a Nextion display, enabling real-time data visualization and IoT capabilities. The system supports over-the-air (OTA) updates, making it easy to maintain and update firmware remotely.

## Features

- **CAN Bus Integration**: Reads data from a CAN bus and processes it.
- **Nextion Display**: Displays the processed data in a user-friendly interface.
- **WiFi Connectivity**: Connects to a WiFi network for data transmission and OTA updates.
- **Over-the-Air (OTA) Updates**: Allows firmware updates without physical access to the device.

## Hardware Requirements

- ESP32 Development Board
- CAN Bus Shield
- Nextion Display (e.g., Nextion HMI-3.2)
- WiFi Module (if not using built-in WiFi)

## Software Requirements

- Arduino IDE
- ESP32 Board Manager
- Nextion Editor

## Installation

1. **Install ESP32 Board Manager**:
   - Open Arduino IDE.
   - Go to `File` > `Preferences`.
   - In the `Additional Board Manager URLs` field, add: `https://dl.espressif.com/dl/package_esp32_index.json`.
   - Go to `Tools` > `Board` > `Boards Manager`.
   - Search for `esp32` and install the latest version.

2. **Install Nextion Editor**:
   - Download and install the Nextion Editor from the [Nextion official website](https://www.nextion.com/en/software/nextion-editor).

## Configuration

1. **WiFi Credentials**:
   - Open the `esp32-can-to-nextion-iot-ota-2.ino` file.
   - Set the `SSID` and `PASS` variables to your WiFi network credentials.

2. **CAN Bus Configuration**:
   - Configure the CAN bus settings in the `esp32-can-to-nextion-iot-ota-2.ino` file.

3. **Nextion Display Configuration**:
   - Open the Nextion Editor.
   - Create a new project and set the display dimensions.
   - Add the necessary components (e.g., labels, buttons) and assign them unique IDs.
   - Save the project and export the binary file.

4. **Upload Binary to Nextion Display**:
   - Connect the Nextion display to the ESP32 via UART.
   - Open the Nextion Editor.
   - Select the `File` > `Upload Binary` option and choose the exported binary file.

## Usage

1. **Upload Code to ESP32**:
   - Connect the ESP32 to your computer via USB.
   - Open the `esp32-can-to-nextion-iot-ota-2.ino` file in Arduino IDE.
   - Select the correct board and port.
   - Click the `Upload` button to upload the code to the ESP32.

2. **Connect CAN Bus**:
   - Connect the CAN bus shield to the ESP32.
   - Connect the CAN bus to your CAN network.

3. **Connect WiFi**:
   - Ensure the ESP32 is connected to your WiFi network.

4. **View Data on Nextion Display**:
   - Power on the Nextion display.
   - The display should show the data from the CAN bus.

## OTA Updates

1. **Prepare OTA Update**:
   - Modify the `esp32-can-to-nextion-iot-ota-2.ino` file as needed.
   - Upload the modified code to the ESP32.

2. **Trigger OTA Update**:
   - The ESP32 will automatically check for updates and apply them if available.

## Troubleshooting

- **WiFi Connection Issues**: Ensure the WiFi credentials are correct and the ESP32 is within range of the router.
- **CAN Bus Issues**: Check the CAN bus connections and ensure the CAN network is functioning correctly.
- **Display Issues**: Ensure the Nextion display is properly connected and the binary file is correctly uploaded.

For more detailed information, refer to the [ESP32 documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/) and the [Nextion documentation](https://nextion.tech/nextion-editor/#_section1).

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
