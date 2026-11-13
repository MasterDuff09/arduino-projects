# Captive Portal Example

This example demonstrates how to create a captive portal using an ESP32 microcontroller. The portal serves a simple HTML page and handles basic authentication.

## Features

- **Captive Portal**: Redirects all incoming requests to a custom HTML page.
- **AsyncWebServer**: Handles HTTP requests asynchronously.
- **DNSServer**: Redirects DNS requests to the ESP32's IP address.

## Setup

1. **Connect to the ESP32 Access Point**:
   - The ESP32 will create an access point named "SSID-ESP32".
   - Connect to this network using any device.

2. **Access the Portal**:
   - Once connected, open a web browser and navigate to `http://192.168.4.1`.
   - You will see a simple HTML page.

## Configuration

The code is designed to be simple and straightforward. You can modify the HTML content by changing the `index_html` variable.

### HTML Content

The `index_html` variable contains the HTML content served by the captive portal. You can edit this variable to customize the page.

```cpp
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Captive Portal</title>
</head>
<body>
  <h1>Welcome to the Captive Portal</h1>
  <p>Please enter your credentials to continue.</p>
  <form action="/" method="get">
    <label for="name">Username:</label>
    <input type="text" id="name" name="name"><br><br>
    <label for="pass">Password:</label>
    <input type="password" id="pass" name="pass"><br><br>
    <input type="submit" value="Submit">
  </form>
</body>
</html>
)rawliteral";
```

### Customizing the HTML

- **Username and Password**: The form collects a username and password, which can be used for authentication.
- **Custom Content**: Modify the HTML content to fit your needs.

## Code Explanation

### `setup()`

- **Serial Communication**: Initializes serial communication for debugging.
- **Access Point**: Sets up the ESP32 as an access point with the SSID "SSID-ESP32".
- **Web Server**: Initializes the AsyncWebServer on port 80.
- **DNS Server**: Initializes the DNSServer to redirect all DNS requests to the ESP32's IP address.
- **Captive Portal Handler**: Adds a handler to serve the captive portal page.

### `loop()`

- **DNS Server**: Continuously processes DNS requests.

## Usage

1. **Upload the Code**: Upload the `captive_portal.ino` code to your ESP32.
2. **Connect to the AP**: Connect to the "SSID-ESP32" network.
3. **Access the Portal**: Open a web browser and navigate to `http://192.168.4.1`.

## Notes

- This example is a basic implementation and can be extended with additional features such as user authentication, logging, and more.
- Ensure that the ESP32 has enough memory to handle the captive portal and other tasks.

This README provides a basic overview of the captive portal example. For more advanced features and customization, refer to the ESP32 and Arduino documentation.