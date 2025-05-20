#include <Arduino.h>
#include "puenteH_pwm.hpp"
#include "limiSwitchCONT.hpp"

LN928 myMTR = {4, 5, 6}; //pwm digitalA digitalB
limitSW limitA = {8}; //pin del limit

char caracter;
bool control;
void setup(){
  Serial.begin(115200);
  myMTR.setPWM(100);
  control = true;
}

void loop(){
  if(Serial.available() > 0){
    caracter = Serial.read();
    Serial.print("caracter: ");
    Serial.println(caracter);
    switch (tolower(caracter))
    {
    case 'e':
      if(myMTR.getPWM() < 255)
        myMTR.setPWMmas();
      Serial.print("aumenta uno: ");
      Serial.println(myMTR.getPWM());
      break;
    case 'q':
      if(myMTR.getPWM() > 0)
        myMTR.setPWMmenos();
      Serial.print("disminuye uno: ");
      Serial.println(myMTR.getPWM());
      break;
    case 's':
      myMTR.mtrStop();
      Serial.println("Detiene Motor");
      break;
    case 'r':
      control = !control;
      Serial.println("Cambio de sentido");
      if(control)
        Serial.println("Horario");
      else
        Serial.println("Antihorario");
    break;
    case 'c':
      Serial.println("Reinicia contador");
      limitA.setCero();
      Serial.println(myMTR.getPWM());
    break;
    default:
      break;
    }
  }
  if(control){
    myMTR.mtrRight();
  }else{
    myMTR.mtrLeft();
  }
  if(digitalRead(limitA.getPin())){
    limitA.addCont();
    Serial.print("cont limitA: ");
    Serial.println(limitA.getCont());
    delay(300);
  }
}