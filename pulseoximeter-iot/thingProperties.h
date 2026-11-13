#include <WiFiManager.h>

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

#include "MAX30100_PulseOximeter.h"

bool maxEnabled = false;

WiFiManager esp;
char ssid[32]; // SSID char limit
char pass[63];


char SSID[32];
char PASS[63];
const char DEVICE_LOGIN_NAME[]  = "929afcc6-c975-4165-b6d6-030f409c3421";
const char DEVICE_KEY[]  = "6?9FR3Wiy6XX9sePXn3bJQ5N!";    // Secret device password


PulseOximeter pox;


float heartRate = 0.0;
float o2 = 0.0;

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);


void initProperties() {

  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(heartRate, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(o2, READ, ON_CHANGE, NULL);

  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}




void wifiSetup() {
  String str_ssid = esp.getWiFiSSID(false);
  int len = str_ssid.length() + 1;
  str_ssid.toCharArray(ssid, len);
  String str_pass = esp.getWiFiPass(false);
  len = str_pass.length() + 1;
  str_pass.toCharArray(pass, len);
  Serial.println("CONNECTED TO WIFI");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  strcpy(SSID, ssid);
  strcpy(PASS, pass);
}
