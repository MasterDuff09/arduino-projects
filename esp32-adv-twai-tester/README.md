# ESP32 Advanced TWAI Tester

## Overview

The ESP32 Advanced TWAI Tester is a project designed to facilitate testing and debugging of the TWAI (Controller Area Network) protocol on an ESP32 microcontroller. This project includes a main program (`esp32-adv-twai-tester.ino`), a formatter library (`formatter.h`), an operator library (`operator.h`), and a simulator library (`simulator.h`). The project is structured to handle various TWAI message types, including normal messages, loopback messages, and remote transmission request messages.

## Features

1. **TWAI Driver Initialization**: The main program initializes the TWAI driver with the necessary configuration, including GPIO pins, baud rate, and message queues.
2. **Message Handling**: The project includes functions to handle both received and transmitted messages. Messages can be formatted in different ways, such as hexadecimal strings or human-readable text.
3. **Message Simulation**: The simulator library provides functions to simulate different types of TWAI messages, which can be used for testing and debugging purposes.
4. **Alert Handling**: The main program checks for various TWAI alerts, such as error passive, bus errors, and RX queue full, and logs them to the serial monitor.

## Installation

To use the ESP32 Advanced TWAI Tester, you will need to have the ESP32 development environment set up. The project is compatible with the Arduino IDE or PlatformIO.

### Dependencies

- ESP32 Arduino Core
- ESP-IDF (optional, for advanced features)

### Libraries

- `driver/twai.h`: TWAI driver library for ESP32.
- `formatter.h`: Helper functions for formatting TWAI messages.
- `operator.h`: Functions for handling TWAI messages.
- `simulator.h`: Functions for simulating TWAI messages.

## Usage

### Main Program (`esp32-adv-twai-tester.ino`)

The main program initializes the TWAI driver, handles incoming messages, and simulates outgoing messages. It also checks for and logs various TWAI alerts.

```cpp
#include <driver/twai.h>
#include "formatter.h"
#include "operator.h"
#include "simulator.h"

// GPIOs utilized to connect to the CAN bus transceived
#define RX_GPIO_PIN               GPIO_NUM_5
#define TX_GPIO_PIN               GPIO_NUM_2

// Interval
#define DEFULT_INTERVAL           1000

enum MessageCategories
{
  normal = 0,
  loopback,
  remote_tranmission_request
};

static bool driver_installed      = false;
enum MessageCategories category   = normal;

void setup()
{
  Serial.begin(115200);
  
  twai_general_config_t general_config = TWAI_GENERAL_CONFIG_DEFAULT(TX_GPIO_PIN, RX_GPIO_PIN, TWAI_MODE_NORMAL);

  general_config.tx_queue_len = 0;
  general_config.rx_queue_len = 1000;

  // Depends on the baud rate of can bus on the vehicle
  twai_timing_config_t timing_config = TWAI_TIMING_CONFIG_500KBITS();

  // Transparent transmission
  twai_filter_config_t filter_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

  // Install the TWAI driver
  if (twai_driver_install(&general_config, &timing_config, &filter_config) == ESP_OK)
  {
    Serial.println("Driver installed");

    // Start the TWAI driver
    if (twai_start() == ESP_OK)
    {
      Serial.println("Driver started");
      uint32_t alerts_to_enable = TWAI_ALERT_RX_DATA | TWAI_ALERT_ERR_PASS | TWAI_ALERT_BUS_ERROR | TWAI_ALERT_RX_QUEUE_FULL;

      if (twai_reconfigure_alerts(alerts_to_enable, NULL) == ESP_OK)
      {
        Serial.println("CAN alerts reconfigured");

        // TWAI driver is installed and started
        driver_installed = true;
      }
      else
        Serial.println("Failed to reconfigure alerts");
    }
    else
      Serial.println("Failed to start driver");
  }
  else
   Serial.println("Failed to install driver");
}

void loop()
{
  simulate_normal_message();
  // put your main code here, to run repeatedly:
  if (driver_installed)
  {
    uint32_t alerts_triggered;
    twai_status_info_t status_info;

    // Check if alert triggered
    twai_read_alerts(&alerts_triggered, pdMS_TO_TICKS(DEFULT_INTERVAL));
    twai_get_status_info(&status_info);

    // Handle the alerts
    if (alerts_triggered & TWAI_ALERT_ERR_PASS)
      Serial.println("Alert: TWAI controller has become error passive.");
    else if (alerts_triggered & TWAI_ALERT_BUS_ERROR)
    {
      Serial.println("Alert: A (Bit, Stuff, CRC, Form, ACK) error has occurred on the bus.");
      Serial.printf("Bus error count: %d\n", status_info.bus_error_count);
    }
    else if (alerts_triggered & TWAI_ALERT_RX_QUEUE_FULL)
    {
      Serial.println("Alert: the RX queue is full causing received frames to be lost.");
      Serial.printf("RX buffered: %d\t", status_info.msgs_to_rx);
      Serial.printf("RX miussed: %d\n", status_info.rx_missed_count);
      Serial.printf("RX overrun %d\n", status_info.rx_overrun_count);
    }
    else if (alerts_triggered & TWAI_ALERT_RX_DATA)
    {
       // New message(s) received
       // One or more message received, handle all
       twai_message_t message;

       while (twai_receive(&message, 0) == ESP_OK)
        handle_rx_message(message);     
    }
    else
    {
      // Uncomment in the case of Loopback message
      // simulate_loop_back_message_transmission()

      switch (category)
      {
        case normal:
          // Normal message
          simulate_normal_message();
          category = loopback;
          break;   

        case loopback:
          // Loopback message
          simulate_loop_back_message();
          category = remote_tranmission_request;
          break;

          case remote_tranmission_request:
          // Remote Tranmission Request message
          simulate_remote_transmission_request_message();
          category = normal;
          break;           
      }

      delay(DEFULT_INTERVAL);
    }
  }
  else
    delay(DEFULT_INTERVAL);
}
```

### Formatter Library (`formatter.h`)

The formatter library provides functions to format TWAI messages in different ways.

```cpp
const char SEPARATOR              = ',';
const char TERMINATOR             = '\n';

/*
  Helper Functions for Receive Message
*/

static void write_hex(long digits);

static void write_to_serial(twai_message_t& message)
{
  // Handle received message

  Serial.print("Received New Message: ");

  if (message.extd)
    Serial.print("Message is in Extended Format, ");
  else
    Serial.print("Message is in Standard Format, ");

  Serial.printf("ID: %x\nBytes: ", message.identifier);

  if (!message.rtr)
  {
    for (int i = 0; i < message.data_length_code; i++)
      Serial.printf("data[%d] = %02x, ", i, message.data[i]);

    Serial.println("\n..................................................\n");
  }  
}
void format_to_can_drive(twai_message_t& message)
{
  // packet format (hex string): [ID],[RTR],[IDE],[DATABYTES 0..8B]\n
  // example: 014A,00,00,1A002B003C004D\n

  write_hex(message.identifier);
  Serial.print(SEPARATOR);
  
  write_hex(message.rtr);
  Serial.print(SEPARATOR);

  write_hex(message.extd);
  Serial.print(SEPARATOR);

  // DLC is determinded by number of data bytes, format: [00]
  for (int i = 0; i < message.data_length_code; i++)
    write_hex(message.data[i]);

  Serial.print(TERMINATOR);
}

void write_hex(long digits)
{
  if ( digits < 0x10 )
    Serial.print("0");

  Serial.print(digits, HEX);
}
```

### Operator Library (`operator.h`)

The operator library provides functions to handle both received and transmitted TWAI messages.

```cpp
#ifndef WRITE_TO_CAN_DRIVE
  #define WRITE_TO_CAN_DRIVE
#endif

static void handle_rx_message(twai_message_t& message)
{
  #undef WRITE_TO_CAN_DRIVE

  #ifdef WRITE_TO_CAN_DRIVE
    format_to_can_drive(message);
  #else
    write_to_serial(message);
  #endif
}

void handle_tx_message(twai_message_t message)
{
  String string = "Data with ID [###] will be transmitted: ";
  string.replace("###", String(message.identifier, HEX));

  Serial.print(string);

  for (int i = 0; i < message.data_length_code; i ++)
  {
    printf("data[%d] = %#02x", i, message.data[i]);

    if (i < message.data_length_code)
      printf(", ");
  }
    

  // Queue message for transmission
  esp_err_t result = twai_transmit(&message, portMAX_DELAY);

  if (result == ESP_OK)
    printf("\n%s: Message queued for transmission.\n", esp_err_to_name(result));
  else
    printf("\n%s: Failed to queue the message for transmission.\n", esp_err_to_name(result));

  Serial.println("..................................................\n");
}

/*
Helper Functions for Transmit Message
*/

void transmit_normal_message(uint32_t identifier, uint8_t data[], uint8_t data_length_code = TWAI_FRAME_MAX_DLC)
{
  // configure message to transmit
  twai_message_t message = {
    .identifier = identifier,
    .data_length_code = data_length_code,
  };

  memcpy(message.data, data, data_length_code);

  //Transmit messages using self reception request
  handle_tx_message(message);
}

void transmit_loop_back_message(uint32_t identifier, uint8_t data[], uint8_t data_length_code = TWAI_FRAME_MAX_DLC)
{
  // configure message to transmit
  twai_message_t message = {
    {
      {
        .self = 1,
      }
    },
    .identifier = identifier,
    .data_length_code = data_length_code,
  };

  memcpy(message.data, data, data_length_code);

  //Transmit messages using self reception request
  handle_tx_message(message);
}

void transmit_remote_transmission_request_message(uint32_t identifier, uint8_t data[], uint8_t data_length_code = TWAI_FRAME_MAX_DLC)
{
  // configure message to transmit
  twai_message_t message = {
    {
      {
        .rtr = 1,
      }
    },
    .identifier = identifier,
    .data_length_code = data_length_code,
  };

  memcpy(message.data, data, data_length_code);

  //Transmit messages using self reception request
  handle_tx_message(message);
}
```

### Simulator Library (`simulator.h`)

The simulator library provides functions to simulate different types of TWAI messages.

```cpp
static void simulate_normal_message()
{
  uint8_t data[] = {0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10};

  transmit_normal_message(0x00, data);
}

static void simulate_loop_back_message()
{
  uint8_t data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};

  transmit_loop_back_message(0x01, data);
}

static void simulate_remote_transmission_request_message()
{
  uint8_t data[] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18};

  transmit_remote_transmission_request_message(0x02, data);
}
```

## Contributing

Contributions to the ESP32 Advanced TWAI Tester are welcome. Please fork the repository and submit a pull request with your changes.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.