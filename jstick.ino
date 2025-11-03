int xPin=A0, yPin=A1; //js X and Y pins
int xVal, yVal; //joystick readings
const int DEADZONE=200, CENTER=512; //ignore joystick move near center
char lastDir='N'; //last direction sent
const int buzzerPin=2; //buzzer pin
int incomingByte=0; 

void setup() {
  Serial.begin(9600); //serial connection
}

void loop() {
  xVal=analogRead(xPin); //X value
  yVal=analogRead(yPin); //Y value
    int dx=xVal-CENTER, dy=yVal-CENTER; //distance from center
    char dir='N'; //no direction
      pinMode(buzzerPin, OUTPUT); 
      digitalWrite(buzzerPin, LOW); 

  if(abs(dx)> abs(dy)) { //check which axis moves more
    if(dx>DEADZONE) dir='R'; //right
      else if(dx< -DEADZONE) dir='L'; //left
  } else { 
    if(dy>DEADZONE) dir='D'; //down
        else if(dy<-DEADZONE) dir='U'; //up
  }

  if(dir!=lastDir && dir!='N') { //send only when direction changes
    Serial.println(dir); 
      lastDir=dir; //update direction
  }

  if(abs(dx)<DEADZONE &&abs(dy)<DEADZONE) lastDir='N'; //reset 
  delay(200); 

  if(Serial.available()>0) { 
  incomingByte=Serial.read(); 
    if(incomingByte=='E') { //if snake eat apple
        digitalWrite(buzzerPin, HIGH); //turn buzzer on
          delay(100); 
            digitalWrite(buzzerPin, LOW); //turn buzzer off
    }
  }
}