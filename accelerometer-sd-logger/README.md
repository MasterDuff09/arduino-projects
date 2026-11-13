# Accelerometer SD Logger

## Overview

The `accelerometer-sd-logger.ino` sketch is designed to log accelerometer, magnetometer, and gyroscope data from an Adafruit_LSM303 sensor to an SD card. This data can be used for various applications such as motion tracking, data analysis, or logging environmental conditions.

## Hardware Requirements

- Arduino board (Uno, Mega, etc.)
- Adafruit_LSM303 sensor
- SD card module
- Breadboard and jumper wires

## Wiring

1. Connect the Adafruit_LSM303 sensor to the Arduino board according to the Adafruit documentation.
2. Connect the SD card module to the Arduino board. Typically, this involves connecting the SD card's MOSI, MISO, SCK, and CS pins to the Arduino's corresponding pins (e.g., MOSI to pin 11, MISO to pin 12, SCK to pin 13, and CS to pin 5).

## Software Requirements

- Arduino IDE (version 1.8.13 or later)
- Adafruit Unified Sensor library
- Adafruit LSM303 library
- Adafruit L3GD20 library

## Installation

1. Open the Arduino IDE.
2. Go to `Sketch` > `Include Library` > `Manage Libraries`.
3. Search for and install the following libraries:
   - Adafruit Unified Sensor
   - Adafruit LSM303
   - Adafruit L3GD20

## Usage

1. Upload the `accelerometer-sd-logger.ino` sketch to your Arduino board.
2. Once the sketch is running, it will initialize the sensors and start logging data to an SD card.
3. The data will be saved in a file named `dati_sensore.txt` on the SD card.

## Data Format

The data is logged in the following format:

```
AXEL [m/s^2]         MAG [ut]         GYRO [rad/s]    
```

Each line represents a data point with the following values:
- Accelerometer data (x, y, z) in meters per second squared (m/s^2)
- Magnetometer data (x, y, z) in microteslas (ut)
- Gyroscope data (x, y, z) in radians per second (rad/s)

## Notes

- Ensure that the SD card is properly formatted before running the sketch.
- The SD card module should be connected to the correct pins on the Arduino board.
- The sketch uses the `O_APPEND` flag when opening the file, so new data will be added to the end of the file.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.