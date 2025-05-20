#include <Arduino.h>
class NEMA{
private:
    uint16_t dir, step_, i, myTime = 800;
public:
    NEMA(uint16_t vala, uint16_t valb): dir(vala), step_(valb){
        pinMode(this->dir, OUTPUT);
        pinMode(this->step_, OUTPUT);
    }
    void nemaMove(uint16_t pasos, bool bnd){
        digitalWrite(dir, bnd);
        for(i=0;i<pasos;i++){
            digitalWrite(step_, HIGH);
            delayMicroseconds(myTime);
            digitalWrite(step_, LOW);
            delayMicroseconds(myTime);
        }
    }
};