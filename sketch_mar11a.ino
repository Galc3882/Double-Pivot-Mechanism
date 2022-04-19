#include <Servo.h>
#include <Smoothed.h>
  
Servo servo1;
Servo servo2;
int joyX = A0;
int joyY = A1;
  
int servoValX;
int servoValY;

int offsetX;
int offsetY;

Smoothed <int> mySensorX;
Smoothed <int> mySensorY;


  
void setup() 
{
  servo1.attach(3);
  servo2.attach(5);

  mySensorX.begin(SMOOTHED_EXPONENTIAL, 5);
  mySensorY.begin(SMOOTHED_EXPONENTIAL, 5);

  servoValX = analogRead(joyX);
  servoValY = analogRead(joyY);
  
  offsetX = servoValX-(1023/2);
  offsetY = servoValY-(1023/2);

  Serial.begin(9600);
}
  
void loop()
{
  
  servoValX = analogRead(joyX) -  offsetX;
  mySensorX.add(servoValX);
  servoValX = map(mySensorX.get(), 0 -  offsetX, 1023 - offsetX, 1, 179);

  servoValY = analogRead(joyY) - offsetY;
  mySensorY.add(servoValY);
  servoValY = map(mySensorY.get(), 0 - offsetY, 1023 - offsetY, 1, 179)-90;
  

  servo1.write(servoValX+(servoValY));
  servo2.write(servoValX-(servoValY));

  Serial.print(servoValX+(servoValY));
  Serial.print(",");
  Serial.println(servoValX-(servoValY));
  
}
