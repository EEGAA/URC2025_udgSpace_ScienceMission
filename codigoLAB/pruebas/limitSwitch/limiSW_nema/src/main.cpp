#include <Arduino.h>
#include "myNema.hpp"
NEMA myMotor = {17, 18};
#define pinSW 4
bool stateSW;
void setup(){
  Serial.begin(115200);
  pinMode(pinSW, INPUT);
}
void loop(){
  stateSW = digitalRead(pinSW);
  Serial.println(stateSW);
  if(stateSW){
    myMotor.nemaMove(1000, HIGH);
    //delay(1000);
  }
  delay(10000);
}