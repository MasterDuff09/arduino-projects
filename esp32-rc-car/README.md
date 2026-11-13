# ESP32 RC Car Project

This project consists of several Arduino sketches designed to control an RC car using different input devices. Below is a brief overview of each sketch and how to use them.

## Project Structure

- **analog-joystick-tester/analog-joystick-tester.ino**: Controls an RC car using an analog joystick.
- **esp-ps4-controller-tester/esp-ps4-controller-tester.ino**: Tests and reads data from a PS4 controller.
- **esp32-mac-addr/ESP32-MAC.ino**: Prints the MAC address of the ESP32.

## Dependencies

- **analog-joystick-tester**: No external libraries required.
- **esp-ps4-controller-tester**: Requires the `ps4` library. You can install it via the Arduino Library Manager.
- **esp32-mac-addr**: No external libraries required.

## Setup

1. **Install Libraries**:
   - For the PS4 controller, install the `ps4` library from the Arduino Library Manager.

2. **Upload Sketches**:
   - Open each `.ino` file in the Arduino IDE.
   - Select the correct board and port.
   - Click the "Upload" button to upload the sketch to your ESP32.

## Usage

### Analog Joystick Tester

1. Connect the analog joystick to your ESP32.
2. Upload the `analog-joystick-tester.ino` sketch.
3. Open the Serial Monitor (9600 baud rate).
4. Move the joystick to see the corresponding output on the Serial Monitor.

### PS4 Controller Tester

1. Connect the PS4 controller to your ESP32 via Bluetooth.
2. Upload the `esp-ps4-controller-tester.ino` sketch.
3. Open the Serial Monitor (9600 baud rate).
4. Press buttons and move sticks to see the corresponding output on the Serial Monitor.

### ESP32 MAC Address

1. Upload the `esp32-mac-addr/ESP32-MAC.ino` sketch.
2. Open the Serial Monitor (115200 baud rate).
3. The MAC address of your ESP32 will be printed to the Serial Monitor.

## Troubleshooting

- **Joystick Not Working**: Ensure the joystick is properly connected and the pins are correctly defined in the code.
- **PS4 Controller Not Connecting**: Ensure the controller is in pairing mode and the ESP32 is within Bluetooth range.
- **Serial Monitor Issues**: Check the baud rate settings in the Arduino IDE and the Serial Monitor.

For more detailed information on each sketch, refer to the comments within the code files.

## Contributing

Contributions are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
