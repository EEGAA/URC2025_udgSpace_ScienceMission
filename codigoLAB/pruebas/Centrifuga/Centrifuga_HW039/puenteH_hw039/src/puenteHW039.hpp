#include <Arduino.h>
class HW039{
private:
    int pines[4], PWM;//pines[] = {enbR, enbL, pwmR, pwmL}
    const int freq = 2500;       // Frecuencia PWM (Hz) ~ para motores DC entre 500 y 5000
    const int pwmChannel1 = 0;    // Canal PWM (0-15)
    const int pwmChannel2 = 1;    // Canal PWM (0-15)
    const int resolution = 8;    //ps 0 a 255
public:
    HW039(int enR, int enL, int pwmR, int pwmL){
    this->pines[0] = enR;
    this->pines[1] = enL;
    this->pines[2] = pwmR;
    this->pines[3] = pwmL;
    for(int i=0; i<4; i++){
      pinMode(pines[i], OUTPUT);
    }
      
    ledcSetup(pwmChannel1, freq, resolution);
    ledcAttachPin(pines[2], pwmChannel1);
    ledcSetup(pwmChannel2, freq, resolution);
    ledcAttachPin(pines[3], pwmChannel2);
    }
    void setPWM(int pwm){
        if(pwm>=0 && pwm<=255)
          this->PWM = pwm;
        }
    void setPWMmas(){
        if(PWM < 255)
            PWM++;
    }
    void setPWMmenos(){
        if(PWM > 0)
            PWM--;
    }
    int getPWM(){
        return PWM;
    }
    void mtrStop(){
        digitalWrite(pines[0], LOW);
        digitalWrite(pines[1], LOW);
        ledcWrite(pwmChannel1, 0);
        ledcWrite(pwmChannel2, 0);
    }
    void moveR(){
        digitalWrite(pines[0], HIGH);
        digitalWrite(pines[1], LOW);
        ledcWrite(pwmChannel1, PWM);
        ledcWrite(pwmChannel2, 0);
    }
    void moveL(){
        digitalWrite(pines[0], LOW);
        digitalWrite(pines[1], HIGH);
        ledcWrite(pwmChannel1, 0);
        ledcWrite(pwmChannel2, PWM);
    }
};