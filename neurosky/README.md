# Neurosky.ino

This Arduino sketch is designed to interface with a Neurosky headset using the ThinkGear Communications Protocol. It reads data from the headset and controls LEDs based on the attention and meditation levels.

## Features

1. **LED Control**: The sketch controls multiple LEDs based on the attention level.
2. **Checksum Validation**: It validates the data received from the headset using a checksum.
3. **Debug Output**: Optionally outputs debug information via the serial monitor.

## Hardware Requirements

- Arduino board (e.g., ESP32, Arduino Uno)
- Neurosky headset
- LEDs (Green, Yellow, Red)
- Resistors
- Breadboard and jumper wires

## Wiring

1. Connect the TX pin of the Neurosky headset to the RX pin of the Arduino.
2. Connect the GND pin of the Neurosky headset to the GND pin of the Arduino.
3. Connect the LEDs to the digital pins (e.g., 3, 4, 5, 6, 7, 8, 9, 10, 11, 12) with appropriate resistors.

## Setup

1. Open the `neurosky.ino` file in the Arduino IDE.
2. Upload the sketch to your Arduino board.
3. Open the serial monitor at a baud rate of 57600 to view debug output.

## Configuration

- **LED Pins**: The LED pins are defined at the top of the file. You can change these pins as needed.
- **Baud Rate**: The baud rate is set to 57600. This can be changed if necessary.
- **Debug Output**: The `DEBUGOUTPUT` macro controls whether debug information is printed to the serial monitor. Set it to 1 to enable debug output.

## Usage

1. Power on the Neurosky headset.
2. The Arduino will start reading data from the headset.
3. LEDs will change color based on the attention level.

## Troubleshooting

- Ensure the Neurosky headset is properly connected to the Arduino.
- Check the baud rate settings in the Arduino IDE and the headset.
- Verify that the LED pins are correctly connected and that the resistors are properly placed.