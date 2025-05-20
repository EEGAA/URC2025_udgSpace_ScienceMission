#include <Arduino.h>

#define pinADC 13
float lecADC, volt;
void setup(){
  Serial.begin(115200);
  lecADC = 0;
}
void loop(){
  lecADC = analogRead(pinADC);
  Serial.print("ADC: "); Serial.println(lecADC);
  volt = float(lecADC)/4096 * 5;
  Serial.print(volt);
  Serial.println(" volts");
  delay(1000);
}