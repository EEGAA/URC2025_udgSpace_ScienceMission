#include <Arduino.h>
//Este solo muestra una lectura cada un segundo
//Todo el proceso es mediante la sigueinte biblioteca
#include "MAX6675.h"

const int dtaPin = 9; //SO=Serial Out
const int clckPin = 11; //SCK=Serial Clock Pin
const int selectPin = 10; //CS = chip select CS Pin

MAX6675 thermoCouple(selectPin, dtaPin, clckPin);
int estado;
float temp;
void setup() {
  Serial.begin(115200);
  SPI.begin();

  thermoCouple.begin();
  thermoCouple.setSPIspeed(4000000);
}

void loop() {
  estado = thermoCouple.read();
  temp = thermoCouple.getTemperature();
  Serial.println(estado);
  Serial.print("EST: ");
  Serial.println(temp);
  Serial.println(" ");
  delay(250);

}