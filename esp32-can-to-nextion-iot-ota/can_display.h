

#include <CAN.h>

#define TX_GPIO_NUM   21  // Connects to CTX
#define RX_GPIO_NUM   22  // Connects to CRX
#define LIMIT_TEMP    65



typedef struct {
  int size = 0;
  int id;
  byte data[8];
  String error = "";
} CanMessage;

typedef struct {
  unsigned long I_Batt = 0;
  unsigned long V_Batt = 0;
  unsigned long V_Min_Cell = 0;
  unsigned long SOC = 0;
  unsigned long Energy = 0, vel = 0;
  unsigned long T_Max_Cell = 0, T_Inv = 0, T_Mot = 0;
  unsigned long Apps1 = 0, Apps2 = 0, Brk_Ang = 0, FBP = 0; // analog 1
  unsigned long Steer_Ang = 0, POTFR = 0, POTFL = 0; // analog 2
  unsigned long AccX = 0, AccY = 0, AccZ = 0, Yaw = 0; // analog 3
  unsigned long POTRL = 0, POTRR = 0; // analog 4
} DataFrame;


DataFrame CarData;

void display_temp_mess(String mess) {
  Serial.print("g0.txt=" + String("\"") + mess + String("\""));
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
}

String getDisplayCMD() {
  String displayCMD = "";
  while (Serial.available()) {
    displayCMD += char(Serial.read());
  }
  return displayCMD;
}

void UpdateValCMD(String txt, unsigned long val) {
  Serial.print(txt + String(val));
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
}

void UpdateTXTCMD(String txt, String str) {
  Serial.print(txt + "\"" + str + "\"");
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
}

void UpdateSOC(unsigned long SOC) {
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

void UpdateTemp(DataFrame *D) {
  if ( ((*D).T_Max_Cell) > LIMIT_TEMP || ((*D).T_Inv) > LIMIT_TEMP || ((*D).T_Mot) > LIMIT_TEMP) UpdateValCMD("p0.aph=", 127);
  else UpdateValCMD("p0.aph=", 0);
  return;
}

void ParseCANMessage_New_1(CanMessage message, DataFrame* D) {
  switch (message.id) {
    case (0x622):
      (*D).I_Batt = ((message.data[3] << 24) | (message.data[2] << 16) | (message.data[1] << 8) | (message.data[0])) / 100;
      UpdateValCMD("n3.val=", (*D).I_Batt);
      (*D).V_Batt = (message.data[5] << 8) | (message.data[4]);
      UpdateValCMD("n8.val=", (*D).V_Batt);
      break;
    case (0x624):
      (*D).SOC = ((message.data[1] << 8) | (message.data[0])) / 100;
      UpdateValCMD("n0.val=", (*D).SOC);
      UpdateSOC((*D).SOC);
      break;
    case (0x621):
      (*D).T_Max_Cell = message.data[3];
      UpdateValCMD("n5.val=", (*D).T_Max_Cell);
      UpdateTemp(D);
      break;
    case (0x623):
      (*D).V_Min_Cell = ((message.data[0] << 8) | (message.data[1])) / 10;
      UpdateValCMD("n7.val=", (*D).V_Min_Cell);
      break;
    case (0x100):
      (*D).vel = message.data[2];
      UpdateValCMD("n2.val=", (*D).vel);
      (*D).T_Inv = message.data[3];
      UpdateValCMD("n6.val=", (*D).T_Inv);
      (*D).T_Mot = message.data[4];
      UpdateValCMD("n4.val=", (*D).T_Mot);
      UpdateTemp(D);
      break;
    case (0xE4614):
      (*D).Apps1 = (message.data[7] << 8) | (message.data[6]);
      (*D).Apps2 = (message.data[5] << 8) | (message.data[4]);
      (*D).Brk_Ang = (message.data[1] << 8) | (message.data[0]);
      (*D).FBP = (message.data[2] << 8) | (message.data[3]);
      break;
    case (0xE4714):
      (*D).POTFL = (message.data[7] << 8) | (message.data[6]);
      (*D).POTFR = (message.data[5] << 8) | (message.data[4]);
      (*D).Steer_Ang = (message.data[3] << 8) | (message.data[2]);
      break;
    case (0xE4814):
      (*D).Yaw = (message.data[0] << 8) | (message.data[1]);
      (*D).AccX = (message.data[2] << 8) | (message.data[3]);
      (*D).AccY = (message.data[5] << 8) | (message.data[4]);
      (*D).AccZ = (message.data[7] << 8) | (message.data[6]);
      break;
    case (0xE4914):
      (*D).POTRL = (message.data[0] << 8) | (message.data[1]);
      (*D).POTRR = (message.data[2] << 8) | (message.data[3]);
      break;
    case (0x42):
      (*D).Energy = (message.data[0] << 8) | (message.data[1]);
      UpdateValCMD("n1.val=", (*D).Energy);
      break;
    default:
      break;
  }
}
