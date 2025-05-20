#include <ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/UInt8.h>
//#include <std_msgs/UInt16MultiArray.h>
#include "myNema.hpp"
#include "Excavadora.hpp"
//las objetos NEMA, se incializan con los pines necesarios para el driver A4988
//   mtrN = {dir, step, enable};
NEMA mtr1 = {4, 5, 6},
     mtr2 = {7, 15, 16},
     mtr3 = {17, 18, 8},
     mtr4 = {3, 46, 9},
     mtr5 = {10, 11, 12},
     mtr6 = {42, 2, 1};
EXCAVA excA = {80, 80}; //Velocidad inicial n/126, pos 1 GUSANO, pos 2 BROCA
int myDelay = 600;
uint8_t vGus = 80, vBro = 80;
//CallBacks
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
void exStop(const std_msgs::Bool& bnd);
void gusDir(const std_msgs::Bool& direccion);
void broDir(const std_msgs::Bool& direccion);
void gusVel(const std_msgs::UInt8& velocidad);
void broVel(const std_msgs::UInt8& velocidad);
//void nema1CallBack(const std_msgs::UInt16MultiArray& msg);

//Mi nodo se llama node
ros::NodeHandle node;


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

//ros::Subscriber<std_msgs::UInt16MultiArray> nema1Sub("nema1", &nema1CallBack);


//Funciones callBacks
void nema1R(const std_msgs::UInt16& pasos){
    mtr1.nemaMoveMicro(pasos.data, true, myDelay);
}
void nema1L(const std_msgs::UInt16& pasos){
    mtr1.nemaMoveMicro(pasos.data, false, myDelay);
}
void nema2R(const std_msgs::UInt16& pasos){
    mtr2.nemaMoveMicro(pasos.data, true, myDelay*2);
}
void nema2L(const std_msgs::UInt16& pasos){
    mtr2.nemaMoveMicro(pasos.data, false, myDelay*2);
}
void nema3R(const std_msgs::UInt16& pasos){
    mtr3.nemaMoveMicro(pasos.data, true, myDelay);
}
void nema3L(const std_msgs::UInt16& pasos){
    mtr3.nemaMoveMicro(pasos.data, false, myDelay);
}
void nema4R(const std_msgs::UInt16& pasos){
    mtr4.nemaMoveMicro(pasos.data, true, myDelay);
}
void nema4L(const std_msgs::UInt16& pasos){
    mtr4.nemaMoveMicro(pasos.data, false, myDelay);
}
void nema5R(const std_msgs::UInt16& pasos){
    mtr5.nemaMoveMicro(pasos.data, true, myDelay);
}
void nema5L(const std_msgs::UInt16& pasos){
    mtr5.nemaMoveMicro(pasos.data, false, myDelay);
}
void nema6R(const std_msgs::UInt16& pasos){
    mtr6.nemaMoveMicro(pasos.data, true, myDelay);
}
void nema6L(const std_msgs::UInt16& pasos){
    mtr6.nemaMoveMicro(pasos.data, false, myDelay);
}
void exStop(const std_msgs::Bool& bnd){
    if(bnd.data)
        excA.stop();
}
void gusDir(const std_msgs::Bool& direccion){
    excA.setVelG(myDelay);
    excA.gusa(direccion.data);
}
void broDir(const std_msgs::Bool& direccion){
    excA.setVelB(myDelay);
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
/*void nema1CallBack(const std_msgs::UInt16MultiArray& msg){
    if(msg.data_length == 0) {
        node.logwarn("Array vacío recibido");
        return;
    }
    for(unsigned int i = 0; i < msg.data_length; i++) {
        //Serial.print("Valor "); Serial.println(i);
        Serial.println(msg.data[i]);
    }
}*/

void rosSetup(){
    Serial.begin(115200);
    excavadoraSetup();
    node.initNode();

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
    node.subscribe(subVelBro);
    node.subscribe(subVelGus);
    //node.subscribe(nema1Sub);
}
void rosLoop(){
    node.spinOnce();
}