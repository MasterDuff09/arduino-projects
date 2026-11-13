# ESP32-CAM Project

This project is designed to capture images using an ESP32-CAM module and stream them over a web server. The ESP32-CAM is a popular camera module that integrates a camera sensor and an ESP32 microcontroller, making it ideal for projects that require image capture and processing.

## Features

- **Image Capture**: Captures images using the ESP32-CAM sensor.
- **Web Streaming**: Streams captured images over a web server.
- **Multiple Camera Models**: Supports different camera models like AI Thinker, M5STACK PSRAM, and M5STACK WITHOUT PSRAM.

## Prerequisites

- **ESP32 Development Board**: Ensure you have an ESP32 development board.
- **Camera Module**: ESP32-CAM module.
- **Arduino IDE**: Install the Arduino IDE and add the ESP32 board support.
- **ESP32-CAM Library**: Install the ESP32-CAM library from the Arduino Library Manager.

## Setup

1. **Install ESP32 Board Support**:
   - Open the Arduino IDE.
   - Go to `File` > `Preferences`.
   - In the `Additional Board Manager URLs` field, add the following URL:
     ```
     https://dl.espressif.com/dl/package_esp32_index.json
     ```
   - Go to `Tools` > `Board` > `Boards Manager`.
   - Search for `esp32` and install the `ESP32 by Espressif Systems` package.

2. **Install ESP32-CAM Library**:
   - Go to `Sketch` > `Include Library` > `Manage Libraries`.
   - Search for `esp32-cam` and install the library.

3. **Upload Code to ESP32-CAM**:
   - Connect your ESP32-CAM to your computer via USB.
   - Select the correct board and port in the Arduino IDE:
     - `Tools` > `Board` > `ESP32 Dev Module`
     - `Tools` > `Port` > Select the port corresponding to your ESP32-CAM
   - Copy the code from `esp32-cam.ino` and paste it into the Arduino IDE.
   - Click the `Upload` button to upload the code to your ESP32-CAM.

## Configuration

The `esp32-cam.ino` file includes several configuration options that you can modify to suit your project needs.

### Camera Model

The project supports different camera models. Uncomment the appropriate model definition to select the camera you are using:

```cpp
#define CAMERA_MODEL_AI_THINKER
//#define CAMERA_MODEL_M5STACK_PSRAM
//#define CAMERA_MODEL_M5STACK_WITHOUT_PSRAM
```

### Network Credentials

Update the `ssid` and `password` variables with your Wi-Fi network credentials:

```cpp
const char* ssid = "YourSSID";
const char* password = "YourPassword";
```

### GPIO Pins

The GPIO pin definitions are configured based on the selected camera model. If you are using a different camera model, ensure the GPIO pin definitions are updated accordingly.

## Usage

Once the code is uploaded and the ESP32-CAM is connected to your Wi-Fi network, you can access the web stream by navigating to `http://<ESP32-CAM-IP>/stream` in your web browser. Replace `<ESP32-CAM-IP>` with the IP address of your ESP32-CAM.

## Troubleshooting

- **Camera Capture Failed**: Ensure the camera is properly connected and the power supply is stable.
- **Web Stream Not Working**: Check the IP address and ensure the ESP32-CAM is connected to the same network as your computer.

## Contributing

Contributions are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.

---