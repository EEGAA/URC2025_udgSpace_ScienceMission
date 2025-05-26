#include <Arduino.h>
#include <ros.h>
#include <std_msgs/Bool.h>

ros::NodeHandle nh;

void ledCallback(const std_msgs::Bool& msg) {
  digitalWrite(3, msg.data ? HIGH : LOW);
}

std_msgs::Bool button_msg;
ros::Publisher button_pub("button_state", &button_msg);
ros::Subscriber<std_msgs::Bool> led_sub("led_command", &ledCallback);

void setup() {
  pinMode(3, OUTPUT);
  pinMode(8, INPUT_PULLUP);
  
  nh.initNode();
  nh.advertise(button_pub);
  nh.subscribe(led_sub);
}

void loop() {
  button_msg.data = (digitalRead(8) == LOW); // Asume que el botón está en pull-up
  button_pub.publish(&button_msg);
  
  nh.spinOnce();
  delay(100);
}