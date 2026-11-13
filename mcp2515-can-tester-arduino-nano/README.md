# MCP2515 CAN Tester for Arduino Nano

This project provides a simple CAN tester using an Arduino Nano and the MCP2515 CAN transceiver. It allows you to send and receive CAN messages.

## Table of Contents
1. [Introduction](#introduction)
2. [Dependencies](#dependencies)
3. [Setup](#setup)
4. [Usage](#usage)
5. [Contributing](#contributing)
6. [License](#license)

## Introduction
The MCP2515 CAN Tester for Arduino Nano is designed to facilitate CAN communication testing. It uses the MCP2515 CAN transceiver to send and receive CAN messages, making it useful for debugging and testing CAN-based systems.

## Dependencies
- Arduino IDE
- SPI Library
- MCP2515 Library

You can install the MCP2515 library via the Arduino Library Manager:
1. Open the Arduino IDE.
2. Go to `Sketch` > `Include Library` > `Manage Libraries`.
3. Search for `MCP2515` and install it.

## Setup
1. Connect the MCP2515 CAN transceiver to your Arduino Nano according to the following pinout:
   - VCC to 5V
   - GND to GND
   - CS to D10
   - SCK to D13
   - MISO to D12
   - MOSI to D11
   - INT to D2 (optional, for interrupt handling)

2. Upload the code to your Arduino Nano.

## Usage
1. Open the Serial Monitor in the Arduino IDE.
2. The code will send predefined CAN messages at startup.
3. You can modify the `canMsg1`, `canMsg2`, and `canMsg3` structures in the code to send different messages.
4. The received CAN messages will be printed to the Serial Monitor.

## Contributing
Contributions are welcome! Please fork the repository and submit a pull request.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.