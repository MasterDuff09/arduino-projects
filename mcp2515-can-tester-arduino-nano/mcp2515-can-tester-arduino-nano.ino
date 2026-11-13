#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg1;
struct can_frame canMsg2;
struct can_frame canMsg3;
struct can_frame canMsg4;
MCP2515 mcp2515(10);

void setup() {
  canMsg1.can_id  = 0x422;
  canMsg1.can_dlc = 6;
  canMsg1.data[0] = 0x00;
  canMsg1.data[1] = 0x00;
  canMsg1.data[2] = 0x18;
  canMsg1.data[3] = 0x00;
  canMsg1.data[4] = 0x00;
  canMsg1.data[5] = 0x00;

  canMsg2.can_id  = 0x421;
  canMsg2.can_dlc = 4;
  canMsg2.data[0] = 0x32;
  canMsg2.data[1] = 0x32;
  canMsg2.data[2] = 0x32;
  canMsg2.data[3] = 0x32;

  canMsg3.can_id  = 0x422;
  canMsg3.can_dlc = 6;
  canMsg3.data[0] = 0x00;
  canMsg3.data[1] = 0x00;
  canMsg3.data[2] = 0x32;
  canMsg3.data[3] = 0x00;
  canMsg3.data[4] = 0x00;
  canMsg3.data[5] = 0x00;

  canMsg4.can_id  = 0x421;
  canMsg4.can_dlc = 4;
  canMsg4.data[0] = 0x18;
  canMsg4.data[1] = 0x18;
  canMsg4.data[2] = 0x18;
  canMsg4.data[3] = 0x18;
  
  while (!Serial);
  Serial.begin(115200);
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
}

void loop() {
  mcp2515.sendMessage(&canMsg1);
  delay(500);
  mcp2515.sendMessage(&canMsg2);
  delay(5000);
  mcp2515.sendMessage(&canMsg3);
  delay(500);
  mcp2515.sendMessage(&canMsg4);

  Serial.println("Messages sent");
  delay(5000);
}
