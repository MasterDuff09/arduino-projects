# CAN-H-TJA1051-Tester-ESP32

This project is a simple CAN receiver tester using an ESP32 microcontroller. It is designed to receive CAN messages on a TJA1051 CAN transceiver and print the details of the received messages to the serial monitor.

## Features

- Receives CAN messages on the TJA1051 CAN transceiver.
- Prints the ID, type (standard or extended), and length of the received messages to the serial monitor.
- Handles remote transmission requests (RTR).

## Hardware Requirements

- ESP32 microcontroller
- TJA1051 CAN transceiver
- CAN bus termination resistors (if required)
- Breadboard and jumper wires

## Wiring

1. Connect the TJA1051 CAN transceiver to the ESP32 as follows:
   - CTX (CAN Transmitter) to GPIO 25
   - CRX (CAN Receiver) to GPIO 26
   - VCC to 3.3V
   - GND to GND

2. Connect the CAN bus termination resistors (if required) to the CAN_H and CAN_L pins of the TJA1051 transceiver.

## Software Requirements

- Arduino IDE
- ESP32 board support in Arduino IDE

## Installation

1. Open the Arduino IDE.
2. Go to `File` > `Preferences` and add the following URL to the Additional Board Manager URLs:
   ```
   https://dl.espressif.com/dl/package_esp32_index.json
   ```
3. Go to `Tools` > `Board` > `Boards Manager` and search for `esp32`. Install the ESP32 board support.
4. Open the `can-h-tja1051-tester-esp32.ino` file in the Arduino IDE.
5. Select the correct board and port from the `Tools` menu.
6. Upload the code to the ESP32.

## Usage

1. Open the serial monitor by clicking the magnifying glass icon in the Arduino IDE or by going to `Tools` > `Serial Monitor`.
2. Set the baud rate to 115200.
3. Observe the received CAN messages in the serial monitor.

## Code Explanation

The code is a simple Arduino sketch that initializes the CAN bus and reads incoming CAN messages. Here is a breakdown of the key functions:

- `setup()`: Initializes the serial communication, sets the CAN pins, and starts the CAN bus at 500 kbps.
- `loop()`: Calls the `canReceiver()` function to read incoming CAN messages.
- `canReceiver()`: Parses incoming CAN messages and prints their details to the serial monitor.

## Troubleshooting

- If the CAN bus does not initialize, check the wiring and ensure that the TJA1051 transceiver is properly connected.
- If the CAN messages are not being received, check the CAN bus termination resistors (if used) and ensure that they are connected correctly.
- If the serial monitor does not display any output, ensure that the baud rate is set to 115200.

## Contributing

Contributions are welcome! If you find a bug or have a feature request, please open an issue or submit a pull request.

## License

This project is licensed under the MIT License. See the `LICENSE` file for more information.