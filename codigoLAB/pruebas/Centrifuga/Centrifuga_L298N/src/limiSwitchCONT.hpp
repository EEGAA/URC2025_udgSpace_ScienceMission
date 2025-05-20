#include <Arduino.h>
class limitSW{
private:
    int cont, pin;
public:
    limitSW(int a){
        this->pin = a;
        cont = 0;
        pinMode(pin, INPUT);
    }
    void setCero(){
        cont = 0;
    }
    void addCont(){
       cont++; 
    }
    int getPin(){
        return pin;
    }
    int getCont(){
        return cont;
    }
};