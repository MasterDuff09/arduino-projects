/**
   This example turns the ESP32 into a Bluetooth LE mouse that continuously moves the mouse.
*/
#include <BleMouse.h>
#include <MPU6050_tockn.h>
#include <Wire.h>

BleMouse bleMouse;
MPU6050 mpu6050(Wire);

int Sensitivity = 300;
int delta = 20;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  Serial.println("Starting BLE work!");
  bleMouse.begin();
}

unsigned long currTime = millis();

void loop() {
  if ((millis() - currTime) > delta) {
    mpu6050.update();
    uint16_t gX = mpu6050.getRawGyroX() / Sensitivity / 1.1  * -1;
    uint16_t gZ = mpu6050.getRawGyroZ() / Sensitivity  * -1;

    if (bleMouse.isConnected()) {
      Serial.print(gX);
      Serial.print("   ");
      Serial.print(gZ);
      Serial.print("\r\n");
      bleMouse.move(gZ, -gX);
    }
    currTime = millis();
  }

}
