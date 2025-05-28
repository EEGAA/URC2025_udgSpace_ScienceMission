/* Funcionamiento de la   E X C A V A D O R A
Este programa es una prueba en la que se busca integrar en un proyecto el funcionamiento de la 
ROBOCLAW utilizando ROS para manipular 2 motores:
Principal:
  Gusano

Secundario:
  Broca
*/
#include <Arduino.h>
#include "myROSsetup.hpp"
void setup(){
  rosSetup();
}

void loop(){
  rosLoop();
  delay(100);
}