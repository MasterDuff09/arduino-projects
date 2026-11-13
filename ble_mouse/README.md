# BLE Mouse Example for ESP32

This example turns an ESP32 into a Bluetooth Low Energy (BLE) mouse that continuously moves the mouse based on the gyroscope data from an MPU6050 sensor.

## Features

- **Bluetooth LE Mouse**: The ESP32 acts as a BLE mouse, allowing you to control the mouse using the gyroscope data.
- **Gyroscope Data**: The MPU6050 sensor provides gyroscope data, which is used to determine the mouse movement.
- **Sensitivity Adjustment**: The sensitivity of the mouse movement can be adjusted using the `Sensitivity` variable.

## Hardware Requirements

- ESP32 Development Board
- MPU6050 Gyroscope Sensor
- Breadboard and Jumper Wires

## Wiring

1. Connect the MPU6050 sensor to the ESP32 as follows:
   - VCC to 3.3V
   - GND to GND
   - SDA to GPIO21
   - SCL to GPIO22

## Installation

1. Install the required libraries:
   - `BleMouse`
   - `MPU6050_tockn`

   You can install these libraries using the Arduino Library Manager.

2. Open the `ble_mouse.ino` file in the Arduino IDE and upload it to your ESP32.

## Configuration

The `Sensitivity` variable controls the sensitivity of the mouse movement. You can adjust this value to make the mouse move faster or slower.

```cpp
int Sensitivity = 300;
```

## Usage

1. Upload the code to your ESP32.
2. Open the Serial Monitor at a baud rate of 115200.
3. The ESP32 will start advertising as a BLE mouse.
4. Connect to the BLE mouse from your computer or mobile device.
5. The mouse will start moving based on the gyroscope data from the MPU6050 sensor.

## Troubleshooting

- If the mouse does not move, check the wiring connections.
- Ensure that the MPU6050 sensor is properly calibrated.
- Adjust the `Sensitivity` variable if the mouse movement is too slow or too fast.

## Contributing

Contributions are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.

## License

This project is licensed under the MIT License. See the `LICENSE` file for more information.