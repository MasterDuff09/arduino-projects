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
