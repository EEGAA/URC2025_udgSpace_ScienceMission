#include <ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/UInt8.h>
#include <ESP32Servo.h>
//#include <std_msgs/UInt16MultiArray.h>
#include "myNema.hpp"
#include "Excavadora.hpp"
#define pinServo 14
Servo miServo;
char caracter;
int angulo;
//las objetos NEMA, se incializan con los pines necesarios para el driver A4988
//   mtrN = {dir, step, enable};
NEMA mtr1 = {4, 5, 6},
     mtr2 = {7, 15, 16},
     mtr3 = {17, 18, 8},
     mtr4 = {3, 46, 9},
     mtr5 = {10, 11, 12},
     mtr6 = {42, 2, 1};
EXCAVA excA = {80, 80}; //Velocidad inicial n/126, pos 1 GUSANO, pos 2 BROCA

int myNemaSpeed = 600;
uint8_t vGus = 80, vBro = 80;
//CallBacks nemas
void nema1R(const std_msgs::UInt16& pasos);
void nema1L(const std_msgs::UInt16& pasos);
void nema2R(const std_msgs::UInt16& pasos);
void nema2L(const std_msgs::UInt16& pasos);
void nema3R(const std_msgs::UInt16& pasos);
void nema3L(const std_msgs::UInt16& pasos);
void nema4R(const std_msgs::UInt16& pasos);
void nema4L(const std_msgs::UInt16& pasos);
void nema5R(const std_msgs::UInt16& pasos);
void nema5L(const std_msgs::UInt16& pasos);
void nema6R(const std_msgs::UInt16& pasos);
void nema6L(const std_msgs::UInt16& pasos);
//CallBacks Excavadora (Gusano y Broca)
void exStop(const std_msgs::Bool& bnd);
void gusDir(const std_msgs::Bool& direccion);
void broDir(const std_msgs::Bool& direccion);
void gusVel(const std_msgs::UInt8& velocidad);
void broVel(const std_msgs::UInt8& velocidad);
void excavando(const std_msgs::Bool& decision);//con 1 entra y saca tierra, con 0 vuelve al origen
void excavaJuego(const std_msgs::Bool& decision);
//CallBacks Recolectora (servo 180°)
void servoReco(const std_msgs::Bool& decision);//Recoleccion o dispensacion recibe 1 o 0, 1 recolectar 0 dispensar
void setAngulo(const std_msgs::UInt8& angulo_);//Angulos cualquiera, recibe del 0 al 180


//Mi nodo se llama node
ros::NodeHandle node;
ros::Time timer;

//Subscriptores
ros::Subscriber <std_msgs::UInt16> nema1Rsub("nema1R", &nema1R);
ros::Subscriber <std_msgs::UInt16> nema1Lsub("nema1L", &nema1L);
ros::Subscriber <std_msgs::UInt16> nema2Rsub("nema2R", &nema2R);
ros::Subscriber <std_msgs::UInt16> nema2Lsub("nema2L", &nema2L);
ros::Subscriber <std_msgs::UInt16> nema3Rsub("nema3R", &nema3R);
ros::Subscriber <std_msgs::UInt16> nema3Lsub("nema3L", &nema3L);
ros::Subscriber <std_msgs::UInt16> nema4Rsub("nema4R", &nema4R);
ros::Subscriber <std_msgs::UInt16> nema4Lsub("nema4L", &nema4L);
ros::Subscriber <std_msgs::UInt16> nema5Rsub("nema5R", &nema5R);
ros::Subscriber <std_msgs::UInt16> nema5Lsub("nema5L", &nema5L);
ros::Subscriber <std_msgs::UInt16> nema6Rsub("nema6R", &nema6R);
ros::Subscriber <std_msgs::UInt16> nema6Lsub("nema6L", &nema6L);

ros::Subscriber <std_msgs::Bool> subGusD("Dgus", &gusDir);
ros::Subscriber <std_msgs::Bool> subBroD("Dbro", &broDir);
ros::Subscriber <std_msgs::Bool> subStopExc("STOP", &exStop);
ros::Subscriber <std_msgs::UInt8> subVelGus("setGvel", &gusVel);
ros::Subscriber <std_msgs::UInt8> subVelBro("setBvel", &broVel);
ros::Subscriber <std_msgs::Bool> subExcavando("excava", &excavando);
ros::Subscriber <std_msgs::Bool> subJuego("juego", &excavaJuego);
ros::Subscriber <std_msgs::Bool> subRec("srvRec", &servoReco);
ros::Subscriber <std_msgs::UInt8> subAng("srvAng", &setAngulo);
//ros::Subscriber<std_msgs::UInt16MultiArray> nema1Sub("nema1", &nema1CallBack);


//Funciones callBacks
void nema1R(const std_msgs::UInt16& pasos){
    mtr1.nemaMoveMicro(pasos.data, true, myNemaSpeed);
}
void nema1L(const std_msgs::UInt16& pasos){
    mtr1.nemaMoveMicro(pasos.data, false, myNemaSpeed);
}
void nema2R(const std_msgs::UInt16& pasos){
    mtr2.nemaMoveMicro(pasos.data, true, myNemaSpeed*2);
}
void nema2L(const std_msgs::UInt16& pasos){
    mtr2.nemaMoveMicro(pasos.data, false, myNemaSpeed*2);
}
void nema3R(const std_msgs::UInt16& pasos){
    mtr3.nemaMoveMicro(pasos.data, true, myNemaSpeed);
}
void nema3L(const std_msgs::UInt16& pasos){
    mtr3.nemaMoveMicro(pasos.data, false, myNemaSpeed);
}
void nema4R(const std_msgs::UInt16& pasos){
    mtr4.nemaMoveMicro(pasos.data, true, myNemaSpeed);
}
void nema4L(const std_msgs::UInt16& pasos){
    mtr4.nemaMoveMili(pasos.data, false, 10);
}
void nema5R(const std_msgs::UInt16& pasos){
    mtr5.nemaMoveMicro(pasos.data, true, myNemaSpeed);
}
void nema5L(const std_msgs::UInt16& pasos){
    mtr5.nemaMoveMili(pasos.data, false, 10);
}
void nema6R(const std_msgs::UInt16& pasos){
    mtr6.nemaMoveMicro(pasos.data, true, myNemaSpeed);
}
void nema6L(const std_msgs::UInt16& pasos){
    mtr6.nemaMoveMicro(pasos.data, false, myNemaSpeed);
}
void exStop(const std_msgs::Bool& bnd){
    if(bnd.data)
        excA.stop();
}
void gusDir(const std_msgs::Bool& direccion){
    excA.setVelG(myNemaSpeed);
    excA.gusa(direccion.data);
}
void broDir(const std_msgs::Bool& direccion){
    excA.setVelB(myNemaSpeed);
    excA.broc(direccion.data);
}
void gusVel(const std_msgs::UInt8& velocidad){
    if(velocidad.data >= 0 && velocidad.data <=126){
        excA.setVelG(velocidad.data);
        excA.gusa(true);
    }
}
void broVel(const std_msgs::UInt8& velocidad){
    if(velocidad.data >= 0 && velocidad.data <=126){
        excA.setVelB(velocidad.data);
        excA.broc(true);
    }
}
void servoReco(const std_msgs::Bool& decison){
    if(decison.data)
        angulo = 10;
    else
        angulo = 120;
    miServo.write(angulo);
    Serial.println(angulo);
}
void setAngulo(const std_msgs::UInt8& angulo_){
    angulo = angulo_.data;
    miServo.write(angulo);
    Serial.println(angulo);
}
void excavando(const std_msgs::Bool& decision){
    if(decision.data){
        excA.setVelG(126);
        excA.gusa(true);
        delay(12000);
        excA.stopGus();
        excA.gusa(true);
        delay(200);
        excA.stopGus();
        excA.setVelB(126);
        excA.broc(true);
        for(int i=0;i<20;i++){
            excA.gusa(false);
            delay(900);
            excA.gusa(true);
            delay(1000);
        }
        excA.stopGus();
        delay(20000);
        excA.stopBro();
    }else{
        excA.stopBro();
        excA.gusa(false);
        delay(8000);
        excA.stopGus();
    }
}
void excavaJuego(const std_msgs::Bool& decision){
    excA.setVelB(126);
    excA.broc(true);
    excA.setVelG(126);
    for(int i=0;i<10;i++){
            excA.gusa(false);
            delay(900);
            excA.gusa(true);
            delay(1000);
        }
    excA.stop();
}

void rosSetup(){
    node.initNode();
    Serial.begin(115200);
    excavadoraSetup();
    
    miServo.setPeriodHertz(50);
    miServo.attach(pinServo, 500, 2400);
    angulo = 90;
    miServo.write(angulo);

    node.subscribe(nema1Rsub);
    node.subscribe(nema1Lsub);
    node.subscribe(nema2Rsub);
    node.subscribe(nema2Lsub);
    node.subscribe(nema3Rsub);
    node.subscribe(nema3Lsub);
    node.subscribe(nema4Rsub);
    node.subscribe(nema4Lsub);
    node.subscribe(nema5Rsub);
    node.subscribe(nema5Lsub);
    node.subscribe(nema6Rsub);
    node.subscribe(nema6Lsub);
    node.subscribe(subStopExc);
    node.subscribe(subGusD);
    node.subscribe(subBroD);
    node.subscribe(subExcavando);
    node.subscribe(subJuego);
    node.subscribe(subVelBro);
    node.subscribe(subVelGus);

    node.subscribe(subRec);
    node.subscribe(subAng);
    //node.subscribe(nema1Sub);

}
void rosLoop(){
    node.spinOnce();
}