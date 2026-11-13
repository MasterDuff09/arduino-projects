#include <driver/twai.h>

#define RX_GPIO_PIN               GPIO_NUM_3
#define TX_GPIO_PIN               GPIO_NUM_2
#define DEFULT_INTERVAL           1000

enum MessageCategories
{
  normal = 0,
  loopback,
  remote_tranmission_request
};

const char SEPARATOR              = ',';
const char TERMINATOR             = '\n';

static bool driver_installed      = false;
enum MessageCategories category   = normal;
long i = 0;



void setup() {
  Serial.begin(115200);
  
  twai_general_config_t general_config = TWAI_GENERAL_CONFIG_DEFAULT(TX_GPIO_PIN, RX_GPIO_PIN, TWAI_MODE_NORMAL);

  general_config.tx_queue_len = 0;
  general_config.rx_queue_len = 1000;

  // Depends on the baud rate of can bus on the vehicle
  twai_timing_config_t timing_config = TWAI_TIMING_CONFIG_500KBITS();

  twai_filter_config_t filter_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

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

void loop() {
  if (driver_installed)
  {

    //simulate_normal_message();
    i++;
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
     delay(DEFULT_INTERVAL);
    
  }
  else
    delay(DEFULT_INTERVAL);

}

void write_hex(long digits)
{
  if ( digits < 0x10 )
    Serial.print("0");

  Serial.print(digits, HEX);
}


void write_to_serial(twai_message_t& message)
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


void handle_tx_message(twai_message_t message)
{
  String string = "Data with ID [###] will be transmitted: ";
  string.replace("###", String(message.identifier, HEX));

  Serial.print(string);
  Serial.print("message no. ");
  Serial.println(i);

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


void handle_rx_message(twai_message_t& message)
{
  #undef WRITE_TO_CAN_DRIVE

  #ifdef WRITE_TO_CAN_DRIVE
    format_to_can_drive(message);
  #else
    write_to_serial(message);
  #endif
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


void simulate_normal_message()
{
  uint8_t data[] = {0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10};

  transmit_normal_message(0x00, data);
}
