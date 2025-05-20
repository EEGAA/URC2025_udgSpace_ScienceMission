#include <Arduino.h>
/*Este programa promedia la lectura del PHmetro con el fin 
de obtener un resultado mas cerrado*/
class phMetro{
  //Se supondra un comportamiento lineal
  //si Y es ph, tiene un valor entre 0 y 14
  //y X es Voltaje, con un valor de 0 a 5 volts...
 //Se encuentra esta ecuacion
    //  Y = m*X + b
  //donde m y b son los parametros constantes a definir,,,
private:
  const int espera = 20, promedio = 30, pin = 13;//aqui meromero cawamero escoge el pin
  const float m = -6.976, b = 25.696;

  float volt, PH;
  int i, cont;
public:
  int getPin(){ return pin; }
  float getPH(){
    cont = 0;
    for(i=0; i<promedio; i++){
      cont = cont + analogRead(pin);
      delay(espera);
    }
    cont = cont/(i+1);
    Serial.print(cont);
    Serial.println("adc");
    
    float volt = float(cont)/4096 * 3.3;
    Serial.print(volt);
    Serial.println(" volts");
    PH = m * volt + b;
    return PH;
  }
}obj;

void setup(){
  Serial.begin(115200);
  pinMode(obj.getPin(), INPUT);
}

void loop(){
  float aux = obj.getPH();
  Serial.println(aux);
  Serial.println(" ");
  delay(100);
}