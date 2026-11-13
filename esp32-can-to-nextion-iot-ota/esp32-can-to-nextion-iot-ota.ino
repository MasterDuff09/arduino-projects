#include "can_display.h"
#include "wifi_config.h"
#include "OTAFlash.h"


#define DISPLAY_SWITCH 5 //pin associato al mosfet che accende il display
#define RX1_PIN 19 // pin rx_esp - tx_disp per comunicazione con il display
#define TX1_PIN 18 // pin tx_esp - rx_disp per comunicazione con il display


unsigned long mill = 0; // variabile per timeout
bool connection_status = false; // stato se abbiamo AVVIATO TENTATIVO di connessione al wifi
bool can_is_setup = false; // stato setup can


///////////////////////////////////////////////////////////////////////////////////////////////////da valore binario dell'indirizzo ip, viene trasformato in stringa
String getIP(long ip) { // 
  byte byte1 = ip >> 24;
  byte byte2 = ip >> 16;
  byte byte3 = ip >> 8;
  byte byte4 = ip & 0xff;
  return String(byte4) + "." + String(byte3) + "." + String(byte2) + "." + String(byte1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////mostra info wifi nella pagina ESP-32 sul display
void WIFI_CONFIG_DISPLAY() { // 
  UpdateValCMD("t20.pco=", 2024);
  UpdateTXTCMD("g1.txt=", String(esp.getWiFiSSID(false)));
  UpdateTXTCMD("g2.txt=", String(esp.getWiFiPass(false)));
  UpdateTXTCMD("g3.txt=", getIP(WiFi.localIP()));
}

///////////////////////////////////////////////////////////////////////////////////////////////////setup della can
void canSetup() { 
  String can_setup_mess = "";
  CAN.setPins (RX_GPIO_NUM, TX_GPIO_NUM);
  if (!CAN.begin (500E3)) {  ////////////////////bitrate del can bus
    can_setup_mess = "Failed to setup CANBUS";
  } else {
    can_setup_mess = "SETUP CANBUS";
    can_is_setup = true;
  }
  display_temp_mess(can_setup_mess);
}

/////////////////////////////////////////////////////////////////////////////////////////////////// prende i messaggi in entrata
CanMessage CANMessageReceive() {
  CanMessage messageArray;  // vedi struct in can_display.h
  int packetSize = CAN.parsePacket();
  Serial.println(packetSize);
  if (packetSize) {
    if (!(CAN.packetRtr())) {
      messageArray.size = packetSize;
      messageArray.id = CAN.packetId();
      for (int i = 0; (i < packetSize) && CAN.available(); i++) {
        messageArray.data[i] = CAN.read();
      }
    }
  }
  return messageArray;
}

void setup() {
  Serial.begin(115200);
  //Serial1.begin(115200, SERIAL_8N1, RX1_PIN, TX1_PIN); (BAUDRATE, PARITY-STOP-BIT, RX, TX) for nextion communication
  pinMode(DISPLAY_SWITCH, OUTPUT);
  digitalWrite(DISPLAY_SWITCH, LOW);
  //esp.resetSettings();
  esp.setConfigPortalTimeout(120); // setta a 120 secondi il timeout entro il quale, se non ci si collega al sito per configurazione wifi, salta il tentativo
  esp.setConnectTimeout(60); //una volta rilevata la rete, setta a 60 secondi il timeout entro il quale, se non riesce a collegarsi, salta il tentativo
  

  unsigned long temp_millis = millis();
  while ((millis() - temp_millis) < 1000) {} //delay 1000 ms
  
/////////////////////////////////////////////////////////////////////////////////////////////////// prende e gestisce i comandi dal nextion per avviare o no connessione
  String cmd = "";
  while (true) {
    if (Serial.available()) {
      cmd = getDisplayCMD(); // gets commands from nextion display
      if (cmd.equals("start connection")) {
        temp_millis = millis();
        while ((millis() - temp_millis) < 5000) {} //delay 5000 ms
        if (!esp.autoConnect("ESP32", "Password123")) {
          Serial.println("Failed to connect");
          cmd = "interrupted connection";
        } else {
          wifiSetup();
          otaSetup();
          initProperties();
          connection_status = true;
        }
        break;
      }
      else if (cmd.equals("interrupted connection")) break;
    }
  }
  String can_cmd = "";
  while (true) {
    if ((WiFi.status() == WL_CONNECTED) || (cmd.equals("interrupted connection"))) {
      if (Serial.available()) {
        while (Serial.available()) {
          can_cmd += char(Serial.read());
          if (can_cmd.equals("avvia setup can")) {
            delay(500);
            canSetup();
            UpdateValCMD("tm0.en=", 0);
            delay(500);
            break;
          }
        }
        break;
      }
    }
  }


}



void loop() {
  CanMessage message;
  if (can_is_setup) {
    message = CANMessageReceive();
    
    if (message.size > 0) {
      ParseCANMessage_New_1(message, &CarData);
      UpdateValCMD("p1.aph=", 0);
    }
  }
  String cmd = "";
  if (Serial.available()) {
    while (Serial.available()) {
      cmd += char(Serial.read());
      if (cmd.equals("Reset WiFi")) {
        UpdateValCMD("tm1.en=", 0);
        UpdateTXTCMD("b1.txt=", "WiFi reset done");
        delay(500);
        esp.resetSettings();
        break;
      } else if (cmd.equals("Reset ESP-32")) {
        UpdateValCMD("tm0.en=", 0);
        UpdateTXTCMD("b2.txt=", "Restarting ESP-32");
        delay(500);
        ESP.restart();
        //abort();
        break;
      }
      else if (cmd.equals("avvia setup can")) {
        UpdateValCMD("tm0.en=", 0);
        break;
      }
    }
  }

  if (WiFi.status() == WL_CONNECTED && connection_status) {
    WIFI_CONFIG_DISPLAY();
    handleOta();
    display_temp_mess("CONNECTED TO WIFI - Str:" + String(int(WiFi.RSSI())));
    if ((millis() - mill) > 300 && (int(WiFi.RSSI()) > -100)) {
      temp = String(CarData.T_Inv) + " °C ----- " + String(CarData.T_Mot) + " °C ----- " + String(CarData.T_Max_Cell) + " °C";
      volt_curr = String(CarData.V_Batt) + " V -- " + String(CarData.V_Min_Cell) + " mV -- " + String(CarData.I_Batt) + " A";
      energy = CarData.Energy ;
      soc = CarData.SOC;
      speed = CarData.vel;
      mill =  millis();
      ArduinoCloud.update();
    }
  }
  else UpdateValCMD("t20.pco=", 63618);

  if (WiFi.status() != WL_CONNECTED && (connection_status)) {
    display_temp_mess("Trying to connect...");
    }
}
