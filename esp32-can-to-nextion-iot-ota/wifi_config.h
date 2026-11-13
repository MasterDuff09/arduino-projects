#include <WiFiManager.h>
#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

WiFiManager esp;
char ssid[32]; //temporary string to store wifi's name
char pass[63]; //temporary string to store wifi's password

char SSID[32]; //string to pass as parameter to initialize arduino cloud's wificonnection handler
char PASS[63];
const char DEVICE_KEY[]  = "dev_key";
const char DEVICE_LOGIN_NAME[]  = "dev_log_n";

String temp;
String volt_curr;
int energy;
int soc;
int speed;

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);

void initProperties() {
  
  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(temp, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(volt_curr, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(energy, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(soc, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(speed, READ, ON_CHANGE, NULL);

  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  /*
    setDebugMessageLevel(2);
    ArduinoCloud.printDebugInfo();
  */
}

void wifiSetup() {
  String str_ssid = esp.getWiFiSSID(false);
  int len = str_ssid.length() + 1;
  str_ssid.toCharArray(ssid, len);
  String str_pass = esp.getWiFiPass(false);
  len = str_pass.length() + 1;
  str_pass.toCharArray(pass, len);
  strcpy(SSID, ssid);
  strcpy(PASS, pass);
}
