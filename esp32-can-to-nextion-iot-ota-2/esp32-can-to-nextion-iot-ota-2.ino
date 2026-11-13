#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
#include <CAN.h>
#include <WiFi.h>


//#define DEBUG1
#define DISPLAY_SWITCH 19 //pin associato al mosfet che accende il display
//#define RST_PIN 21
#define RX1_PIN 22 // pin rx_esp - tx_disp per comunicazione con il display
#define TX1_PIN 23 // pin tx_esp - rx_disp per comunicazione con il display
#define TX_GPIO_NUM   25  // Connects to CTX
#define RX_GPIO_NUM   26  // Connects to CRX


#ifdef DEBUG1
  #define SER Serial
#else
  #define SER Serial1
#endif

typedef struct {
  float I_Batt = 0;
  unsigned int V_Batt = 0;
  int LV_Sys = 0;
  int SOC = 0;
  int vel = 0;
  int T_Max_Cell = 0, T_Inv = 0, T_Mot = 0;
} DataFrame;

typedef struct {
  int size = 0;
  int id = 0x00;
  byte data[8];
} CanMessage;

//Functions declaration

void SetupCan();
CanMessage CANMessageReceive();
void CANMessageHandler(CanMessage mess, DataFrame* D);

void WIFI_CONFIG_DISPLAY(void);
String getIP(long ip);
void display_temp_mess(String mess);
void UpdateTXTCMD(String txt, String str);
void UpdateValCMD(String txt, unsigned long val);
void UpdateSOC(int SOC);

void onCurrVoltChange();
void onTPackInvMotChange();
void onLvChange();
void onSocChange();
void onSpeedChange();
void initProperties(void);

// Global variables
const char DEVICE_LOGIN_NAME[]  = "dev_log_n";

#ifdef DEBUG1
const char SSID[]               = "SSID";
const char PASS[]               = "PWD";
#else
const char SSID[]               = "";
const char PASS[]               = "";
#endif

const char DEVICE_KEY[]         = "dev_key";

String curr_volt;
String t_pack_inv_mot;
int lv;
int soc;
int speed;

bool can_is_setup = false;
bool wifi_is_setup = false;
bool wifi_connected = false;
unsigned long mill = 0;
unsigned long mill_display_wifi = 0;

DataFrame CarData;

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);


// Setup and loop functions
void setup(){  

  #ifndef DEBUG1
  Serial1.begin(115200, SERIAL_8N1, RX1_PIN, TX1_PIN);
  #else
  Serial.begin(115200);
  #endif
  
  pinMode(DISPLAY_SWITCH, OUTPUT);
  digitalWrite(DISPLAY_SWITCH, LOW);
  //digitalWrite(RST_PIN, HIGH);

  //delay(200);
  //pinMode(RST_PIN, OUTPUT);
  //delay(200);
  delay(2000);
  SetupCan();
}

void loop(){
  
  CanMessage message;
  if (can_is_setup){
    message = CANMessageReceive();
    if (message.size > 0) CANMessageHandler(message, &CarData);
  } else {  
    display_temp_mess("CANBUS ERROR");
  }

  if (wifi_is_setup) ArduinoCloud.update();
  if (WiFi.status() == WL_CONNECTED){
    if ((millis()- mill_display_wifi)> 2000){
      WIFI_CONFIG_DISPLAY();
      mill_display_wifi =  millis();
    }
    display_temp_mess("CONNECTED TO WIFI - Str:" + String(int(WiFi.RSSI())));
    if ((millis() - mill) > 300 && (int(WiFi.RSSI()) > -100)) {
      curr_volt = String(CarData.V_Batt) + " V -- " + String(CarData.I_Batt) + " A";
      t_pack_inv_mot = String(CarData.T_Max_Cell) + " °C -- " + String(CarData.T_Inv) + " °C -- " + String(CarData.T_Mot) + " °C";
      lv = CarData.LV_Sys;
      soc = CarData.SOC;
      speed = CarData.vel;
      mill =  millis();
      ArduinoCloud.update();
    }
  } else {
    if (wifi_connected){
      wifi_connected = false;
      SER.write(0xff);
      SER.write(0xff);
      SER.write(0xff);
      delay(50);
      SER.print("wifi_stat=0");
      SER.write(0xff);
      SER.write(0xff);
      SER.write(0xff);
    }
  }
  
  
  String cmd = "";
  if (SER.available()) {
    while (SER.available()) {
      cmd += char(SER.read());
      if (cmd.equals("Reset")){
        UpdateValCMD("tm0.en=", 0);
        UpdateTXTCMD("b2.txt=", "Restarting ESP-32");
        delay(500);
        digitalWrite(DISPLAY_SWITCH, HIGH);
        ESP.restart();
        break;


      } else if (cmd.equals("Connect")){
        UpdateValCMD("tm1.en=", 0);
        WiFi.mode(WIFI_STA);
        WiFi.disconnect();
        int n = WiFi.scanNetworks();
        for (int i = 0; i < n; ++i) {
          if (WiFi.SSID(i).c_str() == SSID) {
            delay(1000);
            initProperties();
            ArduinoCloud.begin(ArduinoIoTPreferredConnection);
            wifi_is_setup = true;
            SER.print("wifi=1");
            SER.write(0xff);
            SER.write(0xff);
            SER.write(0xff);
            break;
          }
        }
        break;
      } else if (cmd.equals("Disconnect")){
        UpdateValCMD("tm1.en=", 0);
        WiFi.disconnect();
        wifi_is_setup = false;
        wifi_connected = false;
        SER.print("wifi=0");
        SER.write(0xff);
        SER.write(0xff);
        SER.write(0xff);
        break;


      }
    }
  }
}

////////////////////////////////////////////////////////////////


 
// Display functions//////////////////////////////////////////////////////////////// 
void WIFI_CONFIG_DISPLAY() {
    if (!wifi_connected){
      SER.write(0xff);
      SER.write(0xff);
      SER.write(0xff);
      delay(50);
      SER.print("wifi_stat=1");
      SER.write(0xff);
      SER.write(0xff);
      SER.write(0xff);
      wifi_connected = true;
    }
    UpdateTXTCMD("g1.txt=", String(SSID));
    UpdateTXTCMD("g2.txt=", String(PASS));
    UpdateTXTCMD("g3.txt=", getIP(WiFi.localIP()));
}

String getIP(long ip) { //
  byte byte1 = ip >> 24;
  byte byte2 = ip >> 16;
  byte byte3 = ip >> 8;
  byte byte4 = ip & 0xff;
  return String(byte4) + "." + String(byte3) + "." + String(byte2) + "." + String(byte1);
}

void display_temp_mess(String mess) {
  SER.print("g0.txt=" + String("\"") + mess + String("\""));
  SER.write(0xff);
  SER.write(0xff);
  SER.write(0xff);
}

void UpdateTXTCMD(String txt, String str) {
    SER.print(txt + "\"" + str + "\"");
    SER.write(0xff);
    SER.write(0xff);
    SER.write(0xff);
}

void UpdateValCMD(String txt, unsigned long val) {
  SER.print(txt + String(val));
  SER.write(0xff);
  SER.write(0xff);
  SER.write(0xff);
}

void UpdateSOC(int SOC) {
  UpdateValCMD("j11.val=", SOC);
  if (SOC < 100) {
    if (SOC < 20) {
      UpdateValCMD("p2.aph=", 127);
    } else UpdateValCMD("p2.aph=", 0);
    int decine = (SOC / 10) % 10;
    int unita = SOC - (decine*10);
    int val_ultima_barra = unita * 10;
    for (int i = 10; i >= 0; i--) {
      if (i > decine) UpdateValCMD("j" + String(i) + ".val=", 0);
      else if (i == decine)UpdateValCMD("j" + String(i) + ".val=", val_ultima_barra);
      else UpdateValCMD("j" + String(i) + ".val=", 100);
    }
  }
}




// CAN functions////////////////////////////////////////////////////////////////
void SetupCan() {
  String can_setup_mess = "";
  CAN.setPins (RX_GPIO_NUM, TX_GPIO_NUM);
  if (!CAN.begin (500E3)) {  ////////////////////bitrate del can bus
    can_setup_mess = "Failed to setup CANBUS";
  } else {
    can_setup_mess = "SETUP CANBUS";
    can_is_setup = true;
    SER.write(0xff);
    SER.write(0xff);
    SER.write(0xff);
    delay(50);
    SER.print("can_stat=1");
    SER.write(0xff);
    SER.write(0xff);
    SER.write(0xff);
  }
  display_temp_mess(can_setup_mess);
}

CanMessage CANMessageReceive(){
  CanMessage can_msg;
  int packetSize = CAN.parsePacket();
  if (packetSize) {
    if ((!CAN.packetRtr()) && (CAN.packetId() == 0x421 || CAN.packetId() == 0x422)) {
      can_msg.size = packetSize;
      can_msg.id = CAN.packetId();
      for (int i = 0; (i < packetSize) && CAN.available(); i++) {
        can_msg.data[i] = CAN.read();
      }
    }
  }
  return can_msg;
}

void CANMessageHandler(CanMessage mess, DataFrame* D){
  switch (mess.id) {
    case (0x422):
      (*D).I_Batt = (mess.data[0]|(mess.data[1] << 8))/100;
      UpdateValCMD("n3.val=", int( ( (*D).I_Batt)*100));
      (*D).LV_Sys = mess.data[2];
      UpdateValCMD("n7.val=", (*D).LV_Sys);
      (*D).V_Batt = mess.data[3] | (mess.data[4] << 8);
      UpdateValCMD("n8.val=", (*D).V_Batt);
      //D->SOC da sistemare messaggio can per la SOC
      UpdateValCMD("n0.val=", (*D).SOC);
      UpdateSOC((*D).SOC);
      break;
    case (0x421):
      (*D).vel = mess.data[0];
      UpdateValCMD("n2.val=", (*D).vel);
      (*D).T_Max_Cell = mess.data[1];
      UpdateValCMD("n5.val=", (*D).T_Max_Cell);
      (*D).T_Inv = mess.data[2];
      UpdateValCMD("n6.val=", (*D).T_Inv);
      (*D).T_Mot = mess.data[3];
      UpdateValCMD("n4.val=", (*D).T_Mot);
      break;
    default:
      break;
  }
}

// Arduino Cloud functions////////////////////////////////////////////////////////////////
void initProperties(){

  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(curr_volt, READWRITE, ON_CHANGE, onCurrVoltChange);
  ArduinoCloud.addProperty(t_pack_inv_mot, READWRITE, ON_CHANGE, onTPackInvMotChange);
  ArduinoCloud.addProperty(lv, READWRITE, ON_CHANGE, onLvChange);
  ArduinoCloud.addProperty(soc, READWRITE, ON_CHANGE, onSocChange);
  ArduinoCloud.addProperty(speed, READWRITE, ON_CHANGE, onSpeedChange);

}
void onLvChange()  {}
void onSocChange()  {}
void onSpeedChange()  {}
void onCurrVoltChange()  {}
void onTPackInvMotChange()  {}
