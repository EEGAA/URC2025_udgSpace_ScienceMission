#include <Arduino.h>
#include <ESP32Servo.h>
Servo miServo;
#define pinServo 14
char caracter;
int angulo;
void setup(){
  Serial.begin(115200);
  miServo.setPeriodHertz(50);
  miServo.attach(pinServo, 500, 2400);
  angulo = 90;
  miServo.write(angulo);
}
void loop(){
  if(Serial.available() > 0){
    caracter = Serial.read();
    Serial.println(caracter);
    switch (tolower(caracter))
    {
    case 'w':
      miServo.write(angulo);
      break;
    case 'q':
      if(angulo > 0)
        angulo--;
      Serial.println(angulo);
      break;
    case 'e':
      if(angulo < 180)
        angulo++;
      Serial.println(angulo);
      break;
    case '1':
      angulo = 10;
      miServo.write(angulo);
      Serial.println(angulo);
      break;
    case '2':
      angulo = 40;
      miServo.write(angulo);
      Serial.println(angulo);
      break;
    case '3':
      angulo = 80;
      miServo.write(angulo);
      Serial.println(angulo);
      break;
    case '4':
      angulo = 120;
      miServo.write(angulo);
      Serial.println(angulo);
      break;
    case '5':
      angulo = 160;
      miServo.write(angulo);
      Serial.println(angulo);
      break;
    case '6':
      angulo = 180;
      miServo.write(angulo);
      Serial.println(angulo);
      break;
    default:
      break;
    }
  }
  delay(30);
}