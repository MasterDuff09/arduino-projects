//CLIENT 1


#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <WiFiManager.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>


#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "USER"
//#define AIO_KEY         

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_ADDR   0x3C

#define PIN_PADDLE 18
#define PIN_SEND 4
#define PIN_POT 34
#define PIN_WARNING 2
#define OUT 17
#define BUZZ 23

void MQTT_connect();
void static_print(const char* msg, int size);
void cleardisplay();
void build_message();
int cursor(int pin);
void cancel_send();

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT);
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Publish channel1_send = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/channel1");
Adafruit_MQTT_Subscribe channel1_get = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/channel1");



unsigned long butt_pr = 0, butt_rls = 0, space_s = 0, space_end = 0;
int bp = 0, br = 0, space_en = 1;
unsigned long send_pr = 0, send_rls = 0;
int sp = 0, sr = 0;
int warning;
int state = 0;
const char send[] = "Cli1:";
const char rec[] = "Cli2:";
String message = "";
String lastReceived = "";


void setup() {
  Serial.begin(115200);
  pinMode(PIN_PADDLE, INPUT_PULLUP);
  pinMode(PIN_SEND, INPUT_PULLUP);
  pinMode(PIN_WARNING, OUTPUT);
  pinMode(OUT, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  WiFiManager esp;
  
  delay(500);
  
  static_print("E-MORSE    v1.0", 2);
  delay (5000);
  
  static_print("Hold the paddle to   reset Wifi settings", 1);
  delay (7000);
  if (!digitalRead(PIN_PADDLE)){
    esp.resetSettings();
    static_print("WIFI RESET DONE", 1);
    delay(5000);
  }

  static_print("WIFI SETUP", 1);
  delay(5000);
  bool res;
  res = esp.autoConnect("AutoConnectAP1","password123"); // password protected ap

  if(!res) {
        static_print("Failed to connect", 1);
        delay(2000);
        // ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        static_print("CONNECTED TO WIFI", 1);
        delay(2000);
    }

  
  mqtt.subscribe(&channel1_get);
  cleardisplay();
}


void loop() {
  MQTT_connect();

  digitalWrite(OUT, LOW); 
  noTone(BUZZ);

  if (message.indexOf("/")==0){
      message = message.substring(1);
    }

  if (message.length()<300){
    build_message();
    state = 0;
    digitalWrite(PIN_WARNING, state);
    warning = 1;
  }
  else {
    if (warning){
      state = 1;
      digitalWrite(PIN_WARNING, state);
      static_print("MAX LENGTH 300", 1);
      delay(3000);
      warning = 0;
    }
  }

  cancel_send();

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, cursor(PIN_POT));
  display.println(String(send)+message);
  display.display();
  
  Serial.println(message.length());

  if (message.length()==0){
    Adafruit_MQTT_Subscribe *subscription;
    while ((subscription = mqtt.readSubscription(50))) {
      if (subscription == &channel1_get && (lastReceived != String((char*)channel1_get.lastread))) {
        lastReceived = String((char*)channel1_get.lastread);
        while(digitalRead(PIN_PADDLE)){
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, cursor(PIN_POT));
        display.println(String(rec)+lastReceived);
        display.display();
        }
      }
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

void static_print(const char* msg, int size){
  display.clearDisplay();
  display.setTextSize(size);
  display.setTextColor(WHITE);
  display.setCursor(0, 20);
  display.println(msg);
  display.display();
}

void cleardisplay(){
  display.clearDisplay();
  display.display();
}

int cursor(int pin){
  int cur = analogRead(pin);
  return map(cur, 0, 4096, 0, -60);
}

void cancel_send(){
  if (!digitalRead(PIN_SEND) && !sp && !sr) {
    sp = !sp;
    send_pr = millis();
    delay(10);
  }

  if (digitalRead(PIN_SEND) && sp && !sr){
    send_rls = millis();
    sr = !sr;
    delay(10);
  }

  if (digitalRead(PIN_SEND) && sp && sr){

    if((send_rls-send_pr)>5 && (send_rls-send_pr)<300){
      int index = message.lastIndexOf("/");
      if (index == -1)message = "";
      else message = message.substring(0, index);
    }

    if ((send_rls-send_pr)>=300){
      if (!channel1_send.publish(message.c_str()) && (message.length()>0)) {
      static_print("FAILED", 1);
    } else {
      static_print("SENT", 1);
      lastReceived = message;
      message = "";
      }
    }
    sp = !sp;
    sr = !sr;
  }
}

void build_message(){
  if (!bp && !digitalRead(PIN_PADDLE) && !br && space_en){
    space_end = millis();
    if ((space_s != 0) && ((space_end - space_s)>300)) message += String("/");
    butt_pr = millis();
    bp = !bp;
    space_en = !space_en;
    delay(10);
    }

  if(!digitalRead(PIN_PADDLE)) {digitalWrite(OUT, HIGH); tone(BUZZ, 1318);}
  else {digitalWrite(OUT, LOW); noTone(BUZZ);}

  if (bp && digitalRead(PIN_PADDLE) && !br){
    butt_rls = millis();
    br = !br;
    delay(10);
    }
  
  if (digitalRead(PIN_PADDLE) && br && bp && !space_en){
    if ((butt_rls - butt_pr)>5 && (butt_rls - butt_pr)<190) message += String(".");
    if ((butt_rls - butt_pr)>= 190) message += String("_");
    space_s = millis();
    br = !br;
    bp = !bp;
    space_en = !space_en;
    }
}
