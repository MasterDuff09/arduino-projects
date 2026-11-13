
# CameraWebServer

CameraWebServer is a project designed to provide a web-based interface for controlling and viewing camera feeds from an ESP32-based device. This project utilizes the ESP32 camera module to capture images and stream them via a web server.

## Features

- **Web Interface**: Access camera feeds through a web browser.
- **Image Capture**: Capture images directly from the camera.
- **Filtering**: Apply real-time filters to the camera feed.
- **PSRAM Support**: Optimized for high-resolution images and high JPEG quality.

## Prerequisites

- ESP32 development board with PSRAM
- ESP32 camera module
- Arduino IDE
- ESP32 board support in Arduino IDE

## Setup

1. **Install ESP32 Board Support**:
   - Open Arduino IDE.
   - Go to `File` > `Preferences`.
   - In the `Additional Board Manager URLs` field, add the following URL:
     ```
     https://dl.espressif.com/dl/package_esp32_index.json
     ```
   - Go to `Tools` > `Board` > `Boards Manager`.
   - Search for `esp32` and install the latest version.

2. **Select Board and Port**:
   - Go to `Tools` > `Board` and select the appropriate ESP32 board (e.g., `AI Thinker ESP32 Camera Module`).
   - Go to `Tools` > `Port` and select the correct COM port for your ESP32.

3. **Upload Code**:
   - Open the `CameraWebServer.ino` file in the Arduino IDE.
   - Click the `Upload` button to upload the code to your ESP32.

4. **Configure WiFi**:
   - Once the code is uploaded, open the Serial Monitor (Tools > Serial Monitor).
   - Enter your WiFi SSID and password when prompted.

5. **Access Web Interface**:
   - Open a web browser and navigate to `http://<ESP32_IP_ADDRESS>`.
   - Replace `<ESP32_IP_ADDRESS>` with the actual IP address of your ESP32.

## Configuration

- **Camera Model**: Select the appropriate camera model in the `CameraWebServer.ino` file.
- **PSRAM**: Ensure PSRAM is enabled for high-resolution images and high JPEG quality.

## Troubleshooting

- **No Image**: Ensure PSRAM is enabled and the camera module is properly connected.
- **Connection Issues**: Verify the WiFi credentials and IP address.

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request.

## License

This project is licensed under the MIT License.