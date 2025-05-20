#include <Arduino.h>
#include <Arduino.h>
#define PUMP_PIN 9  // PWM pin connected to the MOSFET gate

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);  // Set baud rate to 9600 (or any other value you prefer)
  
  // Set the pump pin as an output
  pinMode(PUMP_PIN, OUTPUT);

  // Debug message: Setup complete
  Serial.println("Setup complete. Starting pump control loop...");
}

void loop() {
  // Debug message: Starting to increase pump speed
  Serial.println("Increasing pump speed...");

  // Gradually increase pump speed
  //for (int speed = 0; speed <= 255; speed++) {
    analogWrite(PUMP_PIN, 255);  // Set PWM value (0 = off, 255 = full speed)
    delay(2000);  // Wait 20ms between steps

    // Debug message: Print current speed
    //Serial.print("Current speed: ");
    //Serial.println(speed);
  //}

  // Debug message: Pump at full speed
  //Serial.println("Pump at full speed. Waiting for 5 seconds...");

  // Keep the pump running at full speed for 5 seconds
  delay(5000);

  // Debug message: Starting to decrease pump speed
 // Serial.println("Decreasing pump speed...");

  // Gradually decrease pump speed
  //for (int speed = 255; speed >= 0; speed--) {
    analogWrite(PUMP_PIN, 0);  // Set PWM value
    delay(2000);  // Wait 20ms between steps

    // Debug message: Print current speed
    //Serial.print("Current speed: ");
    //Serial.println(speed);
  //}

  // Debug message: Pump stopped
 // Serial.println("Pump stopped. Waiting for 5 seconds...");

  // Stop the pump completely for 5 seconds
  delay(5000);

  // Debug message: Starting new cycle
  Serial.println("Starting new cycle...");
}