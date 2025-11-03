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

 

// buzzer off 

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

  // --- Tilt detection logic ---
  char dir = 'N';
  float T = 0.25;  // tilt threshold (~0.25g)

  if (fabs(ax) > fabs(ay)) {
    if (ax > T) dir = 'R';
    else if (ax < -T) dir = 'L';
  } else {
    if (ay > T) dir = 'U';
    else if (ay < -T) dir = 'D';
  }

  // Send new direction only when it changes
  if (dir != 'N' && dir != lastDir) {
    Serial.println(dir);
    lastDir = dir;
  }

  // Reset when board returns flat
  if (fabs(ax) < T && fabs(ay) < T) lastDir = 'N';

  delay(200);  // update rate (about 5× per second)
  ///
    // read from the Serial port:
  if (Serial.available() > 0) {
  incomingByte = Serial.read();
  // Serial.println(incomingByte);   // optional debug print

  if (incomingByte == 'E') {
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
  }
}

}

