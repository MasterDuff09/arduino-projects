
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <WiFiManager.h>


#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "USER"
#define AIO_KEY         "PASS"


WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Publish channel1_send = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/channel1");
Adafruit_MQTT_Subscribe channel1_get = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/channel1");

void MQTT_connect();

void setup() {
  Serial.begin(115200);
  WiFiManager esp;

  //esp.resetSettings();
  bool res;
  // res = esp.autoConnect(); // auto generated AP name from chipid
  // res = esp.autoConnect("AutoConnectAP"); // anonymous ap
  res = esp.autoConnect("AutoConnectAP","password"); // password protected ap

  if(!res) {
        Serial.println("Failed to connect");
        // ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("CONNECTED TO WIFI");
    }

  
  mqtt.subscribe(&channel1_get);
}


void loop() {
  MQTT_connect();

  if (! channel1_send.publish("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &channel1_get) {
      Serial.print(F("Got: "));
      Serial.println((char *)channel1_get.lastread);
    }
  }
}


void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
