#include "GY521.h"
// FILE: GY521_test_1.ino 
// AUTHOR: Rob Tillaart 
// PURPOSE: minimal demo to test working of the sensor. 
// URL: https://github.com/RobTillaart/GY521
GY521 sensor(0x68);

uint32_t counter = 0;
char lastDir = 'N';
const int buzzerPin = 2; 
int incomingByte = 0;

 


void setup() {
  
  Serial.begin(9600);
  Wire.begin();
pinMode(buzzerPin, OUTPUT);
digitalWrite(buzzerPin, LOW);
  delay(100);
  while (sensor.wakeup() == false) {
    Serial.println("Could not connect to GY521 at 0x68");
    delay(1000);
  }

  sensor.setAccelSensitivity(0);  // ±2g
  sensor.setGyroSensitivity(0);   // ±250°/s
  sensor.setThrottle();

  // calibration values (optional)
  sensor.axe = sensor.aye = sensor.aze = 0;
  sensor.gxe = sensor.gye = sensor.gze = 0;

  Serial.println("READY");
}

void loop() {
  sensor.read();
  float ax = sensor.getAccelX();
  float ay = sensor.getAccelY();
  float az = sensor.getAccelZ();

  //Tilt detection logic
  char dir = 'N';
  float T = 0.25;  // tilt max at 0.25g

  if (fabs(ax)>fabs(ay)) {//absolute value using if statements
    if (ax >T) dir = 'R';   //for x if has greater degree turns right
        else if (ax <-T) dir ='L'; //for x if has greater degree turns left
  }       else {
      if (ay >T) dir ='U';//for x if has greater degree goes up
          else if (ay <-T) dir ='D'; //for x if has greater degree goes down
  }

  
  if (dir !='N' && dir !=lastDir) { //new direction after changing tilting
      Serial.println(dir);
      lastDir =dir;
  }

  
  if (fabs(ax) <T && fabs(ay) <T) lastDir ='N'; //board is flat it will resit

      delay(200);  //delay
  
    
  if (Serial.available() >0) { //check for messages and read for buzzer
      incomingByte =Serial.read();
  
  if (incomingByte =='E') { //buzzer when eat apple
    digitalWrite(buzzerPin, HIGH); //turn buzzer on
    delay(100);
    digitalWrite(buzzerPin, LOW); //turn buzzer off
  }
}

}

