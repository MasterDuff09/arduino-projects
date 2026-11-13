# Pulse Oximeter Test

This Arduino sketch demonstrates how to use the MAX30100 pulse oximeter sensor with an Arduino board. The sensor measures heart rate and SpO2 (oxygen saturation in blood).

## Features

- **Heart Rate Measurement**: The sketch continuously measures and reports heart rate in beats per minute (bpm).
- **SpO2 Measurement**: The sketch also measures and reports the oxygen saturation level in the blood.
- **Beat Detection**: Optionally, you can enable beat detection and receive a callback when a beat is detected.

## Hardware Requirements

- Arduino board (e.g., Arduino Uno, Mega)
- MAX30100 pulse oximeter sensor
- I2C interface (SDA and SCL pins)

## Wiring

1. Connect the VCC pin of the MAX30100 to the 5V pin of the Arduino.
2. Connect the GND pin of the MAX30100 to a ground pin of the Arduino.
3. Connect the SDA pin of the MAX30100 to the A4 (SDA) pin of the Arduino.
4. Connect the SCL pin of the MAX30100 to the A5 (SCL) pin of the Arduino.

## Installation

1. Install the Arduino IDE if you haven't already.
2. Open the Arduino IDE and go to `Sketch` > `Include Library` > `Manage Libraries`.
3. Search for `MAX30100_PulseOximeter` and install the library.

## Usage

1. Open the `pulseoximeter-test.ino` file in the Arduino IDE.
2. Upload the sketch to your Arduino board.
3. Open the Serial Monitor (Tools > Serial Monitor) at a baud rate of 115200.
4. You should see the heart rate and SpO2 levels printed every 100 milliseconds.

## Configuration

- **Reporting Period**: The `REPORTING_PERIOD_MS` variable determines how often the heart rate and SpO2 levels are reported. You can change this value to adjust the reporting frequency.
- **Beat Detection**: The `onBeatDetected` function is commented out by default. Uncomment it if you want to enable beat detection.

## License

This project is licensed under the GNU General Public License v3.0. See the [LICENSE](LICENSE) file for more details.
