#include <mcp_can.h>
#include <SPI.h>
//#include <Arduino.h>

MCP_CAN CAN0(10);
bool x = false;

void setup() {
  Serial.begin(115200);
  if(CAN0.begin(CAN_500KBPS, MCP_8MHz) == CAN_OK) x = true;
  else Serial.print("Can init fail!!\r\n");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(x);
  unsigned int val1 = map(analogRead(A0), 0, 1023, 0, 4999);
  unsigned int val2 = map(analogRead(A1), 0, 1023, 0, 4999);
  unsigned int val3 = map(analogRead(A2), 0, 1023, 0, 4999);
  unsigned int val4 = map(analogRead(A3), 0, 1023, 0, 4999);
  unsigned int val5 = map(analogRead(A6), 0, 1023, 0, 4999);
  unsigned int val6 = map(analogRead(A7), 0, 1023, 0, 4999);
  unsigned char buf1[6] = {(unsigned char)((val1 >> 8) & 0xFF), (unsigned char)((val1) & 0xFF), (unsigned char)((val2 >> 8) & 0xFF), (unsigned char)((val2) & 0xFF), (unsigned char)((val3 >> 8) & 0xFF), (unsigned char)((val3) & 0xFF)};
  unsigned char buf2[6] = {(unsigned char)((val4 >> 8) & 0xFF), (unsigned char)((val4) & 0xFF), (unsigned char)((val5 >> 8) & 0xFF), (unsigned char)((val5) & 0xFF), (unsigned char)((val6 >> 8) & 0xFF), (unsigned char)((val6) & 0xFF)};
  CAN0.sendMsgBuf(0x14, 0, 6, buf1);
  CAN0.sendMsgBuf(0x15, 0, 6, buf2);
  delay(5);

}
