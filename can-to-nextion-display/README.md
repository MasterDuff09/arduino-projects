# CAN-to-Nextion-Display

## Overview

The `can-to-nextion-display` project is a firmware designed to read data from a CAN bus and display it on a Nextion display. This project is intended to be used in automotive or industrial applications where real-time data visualization is required.

## Features

- **CAN Bus Integration**: The firmware reads data from a CAN bus using the MCP2515 CAN controller.
- **Data Decoding**: It decodes specific CAN messages and extracts relevant data such as voltage, current, temperature, and battery status.
- **Nextion Display Support**: The data is then sent to a Nextion display for real-time visualization.

## Hardware Requirements

- **Arduino Board**: Any Arduino board that supports the SPI interface (e.g., Arduino Uno, Mega).
- **MCP2515 CAN Controller**: A CAN controller module.
- **Nextion Display**: A Nextion display for data visualization.
- **CAN Bus**: A CAN bus network for data transmission.

## Software Requirements

- **Arduino IDE**: Version 1.8.13 or later.
- **SPI Library**: This library is included by default in the Arduino IDE.
- **MCP2515 Library**: You can install this library via the Arduino Library Manager.

## Installation

1. **Install the MCP2515 Library**:
   - Open the Arduino IDE.
   - Go to `Sketch` > `Include Library` > `Manage Libraries`.
   - Search for `MCP2515` and install the library.

2. **Upload the Firmware**:
   - Connect your Arduino board to your computer via USB.
   - Open the `can-to-nextion-display.ino` file in the Arduino IDE.
   - Select the correct board and port from the `Tools` menu.
   - Click the `Upload` button to upload the firmware to your Arduino board.

## Configuration

- **CAN Bus Settings**: The CAN bus settings (e.g., bitrate) are configured in the `setup()` function.
- **Nextion Display Settings**: The baud rate for the Nextion display is set to 115200 in the `setup()` function.

## Usage

1. **Connect the Hardware**:
   - Connect the MCP2515 CAN controller to the Arduino board.
   - Connect the Nextion display to the Arduino board.
   - Connect the CAN bus to the MCP2515 controller.

2. **Power Up the System**:
   - Power up the Arduino board and the CAN bus network.
   - The firmware will start reading data from the CAN bus and displaying it on the Nextion display.

## Troubleshooting

- **No Data Displayed**: Ensure that the CAN bus is correctly configured and that the CAN messages are being transmitted.
- **Display Issues**: Check the baud rate settings for the Nextion display and ensure they match the firmware settings.

## Contributing

Contributions are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.

## License

This project is licensed under the MIT License. See the `LICENSE` file for more details.

---