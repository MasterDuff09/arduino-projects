
#include "thingProperties.h"


#define REPORTING_PERIOD_MS     100 // frequenza di refresh 100 ms

long tsLastReport = 0;

void setup() {
  // Initialize serial and wait for port to open:

  
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(600);
  
  //////////////////////////////////////////// procedura di avvio, vedi accendersi sull'arduino tre volte il led giallo
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 
  esp.resetSettings(); // ogni volta che accendiamo l'esp si resettano le reti salvate. Nel caso devi sempre riconnettere l'arduino
  esp.setConfigPortalTimeout(30); // se non vogliamo connetterci a internet, non ci colleghiamo alla rete dell'arduino nei 30 secondi
  esp.setConnectTimeout(15); // durata tentativo connessione. impostazione che, SE CI VOGLIAMO COLLEGARE ma l'arduino non riesce a collegarsi alle reti salvate in 15 secondi, abortisce
  esp.setConnectRetries(1); // numero tentativi connessione. Prova una volta sola a collegarsi alle reti salvati (durata tentativo 15 sec), altrimenti abortisce

  if (!esp.autoConnect("Arduino-ESP32", "Password123")) {
    Serial.println("Failed to connect");
    //ESP.restart();
    WiFi.mode(WIFI_OFF); // se non si collega, spegne wifi
    onConnect(); // accende sensore (vedi in fondo funzione onConnect())
  } else {
    wifiSetup(); // setta credenziali wifi
    initProperties(); // apre comunicazione con server
    delay(1000);
    ArduinoCloud.addCallback(ArduinoIoTCloudEvent::CONNECT, onConnect); // accende sensore solo dopo aver assicurato comunicazione con server per non creare problemi di sincronizzazione
  }
  /////////////////////////////////////////////////////////////////////fine setup/////////////////////////////////////////////////////////////////////
  digitalWrite(LED_BUILTIN, LOW);
  
  Serial.println("Starting loop");
}

void loop() {

  
  if (WiFi.status() == WL_CONNECTED) {ArduinoCloud.update();} // aggiorna il server solo e solo se collegato.

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // aggiornamento dal sensore
  
  if (maxEnabled) { 
    pox.update();
    if ((millis() - tsLastReport) > REPORTING_PERIOD_MS) {
      heartRate = pox.getHeartRate();
      Serial.print("Heart rate:");
      Serial.print(heartRate);
      Serial.print("bpm / SpO2:");
      o2 = pox.getSpO2();
      Serial.print(o2);
      Serial.println("%");
      tsLastReport = millis();
    }
  }
  //
}

void initI2C() {
////////////////////////////////////////////////////////////////////// accensione sensore/////////////////////////
  Serial.print("Initializing pulse oximeter..");

  if (!pox.begin()) {
    // se non viene inizializzato vedi sequenza di accensione/spegnimento del led giallo. altrimenti tutto a posto e si dovrebbe accendere il sensore
    Serial.println("FAILED");
    maxEnabled = false;
    
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
    
    delay(500);
    
    return;
    
  } else {
    Serial.println("SUCCESS");
    maxEnabled = true;
  }
}

void onConnect() {
  Serial.println("Enabling i2c device!");
  initI2C(); // vedi funzione sopra initI2C();
}
