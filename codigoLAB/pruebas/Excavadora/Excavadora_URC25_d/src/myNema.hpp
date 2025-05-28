#include <Arduino.h>
class NEMA{
private:
    uint16_t enable, dir, step_, i;
public:
    NEMA(uint16_t vala, uint16_t valb, uint16_t valc): dir(vala), step_(valb), enable(valc){
        pinMode(this->dir, OUTPUT);
        pinMode(this->step_, OUTPUT);
        pinMode(this->enable, OUTPUT);
        digitalWrite(enable, LOW);
        //enable se activa con 0, y desactiva con 1
    }
    void nemaMoveMicro(uint16_t pasos, bool direccion, uint16_t myTime){
        digitalWrite(dir, direccion);
        for(i=0;i<pasos;i++){
            digitalWrite(step_, HIGH);
            delayMicroseconds(myTime);
            digitalWrite(step_, LOW);
            delayMicroseconds(myTime);
        }
    }
    void nemaMoveMili(uint16_t pasos, bool direccion, uint16_t myTime){
        digitalWrite(dir, direccion);
        for(i=0;i<pasos;i++){
            digitalWrite(step_, HIGH);
            delay(myTime);
            digitalWrite(step_, LOW);
            delay(myTime);
        }
    }
    void setEnable(bool bnd){
        if(bnd)
            digitalWrite(enable, LOW);
        else
            digitalWrite(enable, HIGH);
    }
};