#include <Arduino.h>
#define pinSWopen 8
//#define pinSWclose 3

void setup(){
  Serial.begin(115200);
  pinMode(pinSWopen, INPUT);
  //pinMode(pinSWclose, INPUT);

}
void loop(){
  Serial.print("NO: ");
  Serial.println(digitalRead(pinSWopen));
  //Serial.print("NC: ");
  //Serial.println(digitalRead(pinSWclose));
  Serial.println(" ");
  delay(50);
}