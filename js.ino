int xPin=A0, yPin=A1;
int xVal, yVal;
const int DEADZONE=200, CENTER=512;
char lastDir='N';
const int buzzerPin = 2; 
int incomingByte = 0;
void setup() {
  Serial.begin(9600);
}

void loop() {
  xVal=analogRead(xPin);
  yVal=analogRead(yPin);
  int dx=xVal-CENTER, dy=yVal-CENTER;
  char dir='N';
pinMode(buzzerPin, OUTPUT);
digitalWrite(buzzerPin, LOW);
  if(abs(dx)>abs(dy)) {
    if(dx>DEADZONE) dir='R';
    else if(dx<-DEADZONE) dir='L';
  } else {
    if(dy>DEADZONE) dir='D';
    else if(dy<-DEADZONE) dir='U';
  }

  if(dir!=lastDir && dir!='N') {
    Serial.println(dir);
    lastDir=dir;
  }
  if(abs(dx)<DEADZONE && abs(dy)<DEADZONE) lastDir='N';
  delay(200);
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
