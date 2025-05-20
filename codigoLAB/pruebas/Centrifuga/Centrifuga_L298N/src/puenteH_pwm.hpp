#include <Arduino.h>
class LN928{
private:
  int pines[3], PWM;
  const int freq = 5000;       // Frecuencia PWM (Hz) ~ para motores DC entre 500 y 5000
  const int pwmChannel = 0;    // Canal PWM (0-15)
  const int resolution = 8;    //ps 0 a 255
public:
  LN928(int PWM, int A, int B){
  this->pines[0] = PWM;
  this->pines[1] = A;
  this->pines[2] = B;
  for(int i=0; i<3; i++){
    pinMode(pines[i], OUTPUT);
  }
    
  ledcSetup(pwmChannel, freq, resolution);
  ledcAttachPin(pines[0], pwmChannel);
  }
  void setPWM(int pwm){
  if(pwm>=0 && pwm<=255)
    this->PWM = pwm;
  }
  void setPWMmas(){
  PWM++;
  }
  void setPWMmenos(){
  PWM--;
  }
  void mtrRight(){
  ledcWrite(pwmChannel, PWM);
  digitalWrite(pines[1], LOW);
  digitalWrite(pines[2], HIGH);
  }
  void mtrLeft(){
  ledcWrite(pwmChannel, PWM);
  digitalWrite(pines[1], HIGH);
  digitalWrite(pines[2], LOW);
  }
  void mtrStop(){
  digitalWrite(pines[1], LOW);
  digitalWrite(pines[2], LOW);
  }
  int getPWM(){
    return PWM;
  }
};