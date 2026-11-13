# Aero-Rake-ADC-CAN

## Overview

The `aero-rake-adc-can.ino` sketch is designed to interface with an Arduino board and communicate over a CAN bus using the MCP2515 CAN controller. The sketch reads analog values from multiple ADC inputs and transmits these values over the CAN bus.

## Hardware Requirements

- Arduino board (e.g., Arduino Uno, Mega)
- MCP2515 CAN controller module
- CAN transceiver module (e.g., MCP2551)
- Analog sensors (e.g., potentiometers, voltage dividers)
- Breadboard and jumper wires

## Wiring

1. Connect the MCP2515 CAN controller module to the Arduino board:
   - VCC to 5V
   - GND to GND
   - CS to D10
   - SCK to D13
   - MISO to D12
   - MOSI to D11
   - INT to D2 (optional, for interrupt-driven communication)

2. Connect the CAN transceiver module to the MCP2515:
   - VCC to 5V
   - GND to GND
   - CAN_H to CAN_H on the transceiver
   - CAN_L to CAN_L on the transceiver

3. Connect the analog sensors to the Arduino board:
   - A0 to sensor 1
   - A1 to sensor 2
   - A2 to sensor 3
   - A3 to sensor 4
   - A6 to sensor 5
   - A7 to sensor 6

## Software Requirements

- Arduino IDE (version 1.8.13 or later)
- MCP_CAN library (version 2.1.4 or later)

## Installation

1. Open the Arduino IDE and navigate to `Sketch > Include Library > Manage Libraries`.
2. Search for "MCP_CAN" and install the library by clicking "Install".

## Usage

1. Upload the `aero-rake-adc-can.ino` sketch to your Arduino board.
2. Open the Serial Monitor (Tools > Serial Monitor) at a baud rate of 115200.
3. The sketch will print the status of the CAN initialization and the analog values being transmitted over the CAN bus.

## Code Explanation

```cpp
#include <mcp_can.h>
#include <SPI.h>

MCP_CAN CAN0(10); // MCP2515 CS pin
bool x = false;   // CAN initialization status

void setup() {
  Serial.begin(115200);
  if (CAN0.begin(CAN_500KBPS, MCP_8MHz) == CAN_OK) x = true;
  else Serial.print("Can init fail!!\r\n");
}

void loop() {
  Serial.println(x); // Print CAN initialization status
  unsigned int val1 = map(analogRead(A0), 0, 1023, 0, 4999);
  unsigned int val2 = map(analogRead(A1), 0, 1023, 0, 4999);
  unsigned int val3 = map(analogRead(A2), 0, 1023, 0, 4999);
  unsigned int val4 = map(analogRead(A3), 0, 1023, 0, 4999);
  unsigned int val5 = map(analogRead(A6), 0, 1023, 0, 4999);
  unsigned int val6 = map(analogRead(A7), 0, 1023, 0, 4999);
  unsigned char buf1[6] = {(unsigned char)((val1 >> 8) & 0xFF), (unsigned char)((val1) & 0xFF), (unsigned char)((val2 >> 8) & 0xFF), (unsigned char)((val2) & 0xFF), (unsigned char)((val3 >> 8) & 0xFF), (unsigned char)((val3) & 0xFF)};
  unsigned char buf2[6] = {(unsigned char)((val4 >> 8) & 0xFF), (unsigned char)((val4) & 0xFF), (unsigned char)((val5 >> 8) & 0xFF), (unsigned char)((val5) & 0xFF), (unsigned char)((val6 >> 8) & 0xFF), (unsigned char)((val6) & 0xFF)};
  CAN0.sendMsgBuf(0x14, 0, 6, buf1);
  CAN0.sendMsgBuf(0x15, 0, 6, buf2);
  delay(5);
}
```

- **MCP_CAN CAN0(10);**: Initializes the MCP2515 CAN controller on pin 10.
- **bool x = false;**: Variable to store the CAN initialization status.
- **setup()**: Initializes the serial communication and attempts to initialize the CAN bus.
- **loop()**: Continuously reads analog values from the sensors, maps them to a 12-bit range, and sends them over the CAN bus using message IDs 0x14 and 0x15.

## Notes

- Ensure proper wiring and power supply to avoid damage to the hardware.
- Adjust the CAN bus speed and other parameters as needed for your specific application.
- The sketch assumes the use of a 12-bit ADC resolution. Adjust the mapping function if using a different resolution.