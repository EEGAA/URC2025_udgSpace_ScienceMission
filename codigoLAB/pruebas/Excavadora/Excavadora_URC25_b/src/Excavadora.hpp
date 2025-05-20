#include <Arduino.h>
#include <RoboClaw.h>

#define pinTx 39
#define pinRx 40


//Dgus = 1      significa entrar
#define RBW_SERIAL Serial2 //roboclaw_serial
#define RBW_BAUD 38400 //roboclaw_baudios

RoboClaw roboclaw(&RBW_SERIAL, 10000);

#define MTR1_ADDRESS 0x80  //Gusano
#define MTR2_ADDRESS 0x80 //Broca

void excavadoraSetup(){
    RBW_SERIAL.begin(RBW_BAUD, SERIAL_8N1, pinTx, pinRx);
    roboclaw.begin(RBW_BAUD);
    //roboclaw.SetConfig();
}
class EXCAVA{
private:
    uint8_t velG, velB;
public:
    EXCAVA(uint8_t x, uint8_t y){
        this->velG = x;
        this->velB = y;
    }
    void setVelG(uint8_t vel_){
        this->velG = vel_;
    }
    void setVelB(uint8_t vel_){
        this->velB = vel_;
    }
    void intro(){
        roboclaw.ForwardM1(MTR1_ADDRESS, velG);
        roboclaw.ForwardM2(MTR2_ADDRESS, velB);
    }
    void extra(){
        roboclaw.BackwardM1(MTR1_ADDRESS, velG);
        roboclaw.BackwardM2(MTR2_ADDRESS, velB);
    }
    void stop(){
        roboclaw.ForwardM1(MTR1_ADDRESS, 0);
        roboclaw.ForwardM2(MTR2_ADDRESS, 0);
    }
    void gusa(bool aux){
        if(aux)
            roboclaw.ForwardM1(MTR1_ADDRESS, velG);
        else
            roboclaw.BackwardM1(MTR1_ADDRESS, velG);
    }
    void broc(bool aux){
        if(aux)
            roboclaw.ForwardM2(MTR2_ADDRESS, velB);
        else
            roboclaw.BackwardM2(MTR2_ADDRESS, velB);
    }
};