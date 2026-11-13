# TWAI Driver Tester for ESP32

This project is a simple TWAI (Controller Area Network) driver tester for the ESP32 microcontroller. It demonstrates how to initialize the TWAI driver, handle incoming messages, and transmit messages using the TWAI protocol.

## Features

- **TWAI Driver Initialization**: Configures and starts the TWAI driver with default settings.
- **Message Handling**: Handles incoming messages and logs relevant information.
- **Message Transmission**: Allows transmitting messages with customizable identifiers and data.
- **Alert Handling**: Monitors and logs various TWAI alerts such as error pass, bus errors, and queue overruns.

## Hardware Requirements

- ESP32 Development Board
- CAN Bus Transceiver Module (e.g., MCP2515)
- CAN Bus Shield or Custom PCB with CAN Bus connections

## Wiring

Connect the CAN Bus Transceiver Module to the ESP32 according to the following pinout:

- **TX**: GPIO2
- **RX**: GPIO3
- **GND**: GND
- **VCC**: 3.3V

## Installation

1. **Install Arduino IDE**: Ensure you have the Arduino IDE installed on your computer.
2. **Install ESP32 Board Support**:
   - Open the Arduino IDE.
   - Go to `File` > `Preferences`.
   - In the `Additional Board Manager URLs` field, add the following URL: `https://dl.espressif.com/dl/package_esp32_index.json`.
   - Go to `Tools` > `Board` > `Boards Manager`.
   - Search for `esp32` and install the latest version.
3. **Open the Project**:
   - Open the `twai-driver-tester-esp32.ino` file in the Arduino IDE.
   - Select the correct board and port from the `Tools` menu.

## Usage

1. **Upload the Code**:
   - Connect your ESP32 board to your computer via USB.
   - Click the `Upload` button in the Arduino IDE to upload the code to the ESP32.
2. **Monitor Serial Output**:
   - Open the Serial Monitor from the Arduino IDE (`Tools` > `Serial Monitor`).
   - Set the baud rate to 115200.
   - Observe the output to see the TWAI driver initialization, message handling, and transmission logs.

## Code Explanation

The code is divided into several functions to handle different aspects of the TWAI driver:

- **`setup()`**: Initializes the TWAI driver, sets up the serial communication, and configures the TWAI driver.
- **`loop()`**: Continuously checks for TWAI alerts and handles incoming messages.
- **`write_hex()`**: Helper function to print hexadecimal values.
- **`write_to_serial()`**: Handles the display of received messages on the serial monitor.
- **`transmit_normal_message()`**: Transmits a normal message with a specified identifier and data.
- **`handle_tx_message()`**: Handles the transmission of a message and logs the status.
- **`handle_rx_message()`**: Handles the reception of a message and logs the details.
- **`format_to_can_drive()`**: Formats the received message into a specific string format for further processing.
- **`simulate_normal_message()`**: Simulates a normal message transmission for testing purposes.

## Contributing

Contributions are welcome! Feel free to open issues or submit pull requests to improve the project.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
