#include <Arduino.h>
#include "puenteHW039.hpp"
#include "limiSwitchCONT.hpp"

HW039 myMTR = {6, 5, 9, 10}; //pines[] = {enbR, enbL, pwmR, pwmL}
limitSW limit6 = {8}, limit1(18);


char caracter;
bool control;
void setup(){
  Serial.begin(115200);
  myMTR.setPWM(10);
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
    case '1':
      myMTR.setPWM(0);
      break;
      case '2':
      myMTR.setPWM(15);
      break;
    case 'c':
      limit6.setCero();
      limit1.setCero();
      break;
    default:
      break;
    }
  }
  if(control){
    myMTR.moveR();
  }else{
    myMTR.moveL();
  }
  if(digitalRead(limit6.getPin())){
    limit6.addCont();
  }
  if(digitalRead(limit1.getPin())){
    limit1.addCont();
  }
}