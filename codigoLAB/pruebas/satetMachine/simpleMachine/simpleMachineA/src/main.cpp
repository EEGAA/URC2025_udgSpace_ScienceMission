#include <ros.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/Int8.h>
#include <Arduino.h>
#define pinLED 33
int myTime;
// Pines para limit switches
#define LIMIT_FORWARD_PIN 3  // NC
#define LIMIT_REVERSE_PIN 8  // NO

ros::NodeHandle nh;

std_msgs::UInt8 limit_msg;
ros::Publisher limit_pub("/limit_switches", &limit_msg);

void motorCmdCallback(const std_msgs::Int8& cmd_msg) {
    switch(cmd_msg.data){
      case -1:
        myTime = 250;
      break;
      case 1:
        myTime = 500;
      break;
      case 0:
        myTime = 1000;
      break;
      default:
        myTime = 2000;
      break;
    }
    for(int x=0; x<20; x++){
      digitalWrite(pinLED, HIGH);
      delay(myTime);
      digitalWrite(pinLED, LOW);
      delay(myTime);
      
    }
    // Implementar control del motor basado en cmd_msg.data
    // -1: reversa, 0: stop, 1: adelante
    // Aquí iría tu código para controlar el driver del motor NEMA
}

ros::Subscriber<std_msgs::Int8> motor_sub("/motor_cmd", &motorCmdCallback);

void setup() {
    // Inicializar pines
    pinMode(LIMIT_FORWARD_PIN, INPUT_PULLUP);
    pinMode(LIMIT_REVERSE_PIN, INPUT_PULLUP);
    pinMode(pinLED, OUTPUT);
    // Inicializar ROS
    nh.initNode();
    nh.advertise(limit_pub);
    nh.subscribe(motor_sub);
}

void loop() {
    // Leer estado de los limit switches
    uint8_t limit_state = 0;
    if (digitalRead(LIMIT_FORWARD_PIN)) limit_state |= 0x01; // Bit 0: forward
    if (digitalRead(LIMIT_REVERSE_PIN)) limit_state |= 0x02; // Bit 1: reverse
    
    // Publicar estado
    limit_msg.data = limit_state;
    limit_pub.publish(&limit_msg);
    
    nh.spinOnce();
    delay(10);
}