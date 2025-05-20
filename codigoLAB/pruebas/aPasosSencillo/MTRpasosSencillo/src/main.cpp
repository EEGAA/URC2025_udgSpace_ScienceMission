#include <Arduino.h>
 //DECLARACIONES
//DEFINICIONES
int bobina[]={3,46,9,10};

int retraso=2;
int i,j=0;

int fase[4][4]={  {1,0,0,0},    //valor 0
                  {0,1,0,0},    //valor 1
                  {0,0,1,0},    //valor 2
                  {0,0,0,1}  }; //valor 3

//FUNCIONES
void paso(int valor){
  for(j=0;j<4;j++){
    digitalWrite(bobina[j], fase[valor][j]);
  }
}

//CONFIGURACIONES
void setup() {
  for(i=0;i<4;i++){
    pinMode(bobina[i], OUTPUT);
  }  
}

//PRINCIPAL
void loop() {
  for(i=0;i<4;i++){
    paso(i);
    delay(retraso);
  }
}