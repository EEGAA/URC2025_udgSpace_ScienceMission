#include <Arduino.h>
class BTN{
private:
    int pin;
    bool state;
public:
    BTN(int x){
        pin = x;
        pinMode(pin, OUTPUT);
        state = false;
    }
    void setState(bool bnd){
        state = bnd;
    }
    bool getState(){
        return state;
    }
    int getPin(){
        return pin;
    }
};
