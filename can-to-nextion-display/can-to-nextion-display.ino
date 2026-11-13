

#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg;
struct can_frame canMsg1;
unsigned long corrente;
unsigned long tensione;
unsigned int SOC;
int T_max, temp_inv, temp_motor;
unsigned int apps1, apps2, brk_ang, fbp; // analog 1
unsigned int steer, potfr, potfl; // analog 2
unsigned int accx, accy, accz, yaw; // analog 3
unsigned int potrl, potrr; // analog 4
unsigned int v_min_cell;
unsigned int energy;

MCP2515 mcp2515(10);


void setup() {
  Serial.begin(115200); //BoudRate del Nextion
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();

}

void loop() {

  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) { //lettura messaggi CAN
    //--------------------------------------------------------------------------------Lettura e decodifica messaggi BMS-------------------------------------------------------------------
    /*  ID:0x621 DLC:8 T.pacco(3° byte)
     *  ID:0x622 DLC:6 corrente(0-31)tensione(32-48)
     *  ID:0x624 DLC:2 SOC
    */
    if(canMsg.can_id == 0x622){ //ID:0x622 DLC:6 corrente(0-31)tensione(32-48)

        corrente = (canMsg.data[3]<<24)|(canMsg.data[2]<<16)|(canMsg.data[1]<<8)|(canMsg.data[0]);
        corrente = corrente/100;
        Serial.print("x1.val=" + String(corrente)); //Corrente
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
  
        tensione = (canMsg.data[5]<<8)|(canMsg.data[4]);
        Serial.print("n4.val="+ String(tensione)); //Tensione
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
    }
    
    if(canMsg.can_id == 0x624){ //SOC Pacco

        SOC = (canMsg.data[1]<<8)|(canMsg.data[0]);
        SOC = SOC/100;
        Serial.print("n5.val="+String(SOC));
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        
        Serial.print("j1.val="+String(SOC));
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        
        if(SOC<=15){
        Serial.print("j1.pco=RED");
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        }else{
        Serial.print("j1.pco=GREEN");
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
      }
    }
    
    if(canMsg.can_id == 0x621){ //Temp. Pacco
      
        T_max = canMsg.data[3];
        Serial.print("n8.val="+String(T_max));
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
    }

    if (canMsg.can_id == 0x623) {

        v_min_cell = (canMsg.data[0]<<8)|(canMsg.data[1]);
        v_min_cell = v_min_cell/10;
        Serial.print("t14.txt=\""+String(v_min_cell)+" mV\"");
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        
      }

    if (canMsg.can_id == 0x42) {

        energy = (canMsg.data[1]<<8)|(canMsg.data[0]);
        Serial.print("t13.txt=\""+String(v_min_cell)+" Wh\"");
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
      }
    //-------------------------------------------------------------Lettura e decodifica messaggi centralina(INVERTER)--------------------------------------------------------------------
    if(canMsg.can_id == 0x100){ //Mex. centralina 
       /*  ID:0x100 DLC:5 1°-2° byte rpm,3°byte velocità,4°byte Temp.inv,5°byte Temp.Motor
    */
        temp_inv = canMsg.data[3];
        Serial.print("n0.val="+String(temp_inv));
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        temp_motor = canMsg.data[4];
        Serial.print("n1.val="+String(temp_motor));
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
    }
    
    if(canMsg.can_id == 0xE4614){
      
        apps1 = (canMsg.data[7]<<8)|(canMsg.data[6]);
        apps2 = (canMsg.data[5]<<8)|(canMsg.data[4]);
        brk_ang = (canMsg.data[0]<<8)|(canMsg.data[1]);
        fbp = (canMsg.data[2]<<8)|(canMsg.data[3]);
        Serial.print("an1.txt=\"APPS1="+String(apps1)+"mV\rAPPS2="+String(apps2)+"mV\rBRK_ANG="+String(brk_ang)+"mV\rFBP="+String(fbp)+"mV\"");
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
    }

    if(canMsg.can_id == 0xE4714){
      
        potfl = (canMsg.data[7]<<8)|(canMsg.data[6]);
        potfr = (canMsg.data[5]<<8)|(canMsg.data[4]);
        steer = (canMsg.data[2]<<8)|(canMsg.data[3]);
        Serial.print("an2.txt=\"POT_FL="+String(potfl)+"mV\rPOT_FR="+String(potfr)+"mV\rSTEER="+String(steer)+"mV\"");
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
    }

    if(canMsg.can_id == 0xE4814){
      
        accz = (canMsg.data[7]<<8)|(canMsg.data[6]);
        accy = (canMsg.data[5]<<8)|(canMsg.data[4]);
        yaw = (canMsg.data[0]<<8)|(canMsg.data[1]);
        accx = (canMsg.data[2]<<8)|(canMsg.data[3]);
        Serial.print("an3.txt=\"ACC_X="+String(accx)+"mV\rACC_Y="+String(accy)+"mV\rACC_Z="+String(accz)+"mV\rYAW="+String(yaw)+"mV\"");
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
    }

    if(canMsg.can_id == 0xE4914){
      
        potrl = (canMsg.data[0]<<8)|(canMsg.data[1]);
        potrr = (canMsg.data[2]<<8)|(canMsg.data[3]);
        Serial.print("an4.txt=\"POT_RL="+String(potrl)+"mV\rPOT_RR="+String(potrr)+"mV\"");
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
    }
  }
  
  if(Serial.read() == 01){
    canMsg1.can_id  = 0x001;
    
    canMsg1.can_dlc = 1;
    canMsg1.data[0] = 0x01;
    mcp2515.sendMessage(&canMsg1);
  }
    
}



         
  
   
