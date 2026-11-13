#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_10DOF.h>

Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);
Adafruit_L3GD20_Unified       gyro  = Adafruit_L3GD20_Unified(20);

File myFile;

void setup() {
  Serial.begin(9600);
  Serial.println(F("Adafruit 10DOF Tester")); Serial.println("");

  /* Initialise the sensors */
  if(!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println(F("Ooops, no LSM303 detected ... Check your wiring!"));
    while(1);
  }
  if(!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
  
  if(!gyro.begin())
  {
    /* There was a problem detecting the L3GD20 ... check your connections */
    Serial.print("Ooops, no L3GD20 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  if (!SD.begin(5)) {
    Serial.println("initialization failed!");
    while (1);
  } else {
  Serial.println("initialization done.");
  myFile = SD.open("/dati_sensore.txt", O_APPEND);
  }

  myFile.println("Start getting data...");
  /* Display some basic information on this sensor */
  myFile.println("AXEL [m/s^2]         MAG [ut]         GYRO [rad/s]     ");

}

void loop() {
  // put your main code here, to run repeatedly:
  sensors_event_t event;
  
  accel.getEvent(&event);
  myFile.print(event.acceleration.x); myFile.print(" "); myFile.print(event.acceleration.y); myFile.print(" "); myFile.print(event.acceleration.z); myFile.print("    ");

  mag.getEvent(&event);
  myFile.print(event.magnetic.x); myFile.print(" "); myFile.print(event.magnetic.y); myFile.print(" "); myFile.print(event.magnetic.z); myFile.print("    ");

  gyro.getEvent(&event);
  myFile.print(event.gyro.x); myFile.print(" "); myFile.print(event.gyro.y); myFile.print(" "); myFile.print(event.gyro.z); myFile.println("    ");

  delay(20);

}



