#include <Arduino.h>
#include <SPI.h>

// Definición de pines
const int SO_PIN = 6;   // Pin SO (MISO)
const int SCK_PIN = 7;   // Pin SCK (reloj)
const int CS_PIN = 5;    // Pin CS (selección de chip)

// Inicialización del módulo MAX6675
void setup() {
  Serial.begin(9600);
  pinMode(CS_PIN, OUTPUT);
  pinMode(SCK_PIN, OUTPUT);
  pinMode(SO_PIN, INPUT);
  
  digitalWrite(CS_PIN, HIGH); // Desactivar el módulo inicialmente
  
  Serial.println("Inicializando termopar tipo K con MAX6675");
  delay(500); // Pequeña pausa para estabilización
}

// Función para leer la temperatura
float readThermocouple() {
  uint16_t rawData = 0;
  float temperature;
  
  // Iniciar la comunicación
  digitalWrite(CS_PIN, LOW);
  delayMicroseconds(1);
  
  // Leer los 16 bits de datos
  rawData = 0;
  for (int i = 15; i >= 0; i--) {
    digitalWrite(SCK_PIN, LOW);
    delayMicroseconds(1);
    
    if (digitalRead(SO_PIN)) {
      rawData |= (1 << i); // Setear el bit si SO está en HIGH
    }
    
    digitalWrite(SCK_PIN, HIGH);
    delayMicroseconds(1);
  }
  
  digitalWrite(CS_PIN, HIGH);
  
  // Verificar si hay conexión del termopar
  if (rawData & 0x4) {
    // Bit 2 indica circuito abierto (sin termopar conectado)
    Serial.println("ERROR: Termopar no conectado o circuito abierto!");
    return NAN;
  }
  
  // El bit 15 es el bit de signo (no usado en MAX6675)
  // Los bits 14-3 contienen la temperatura en formato 12 bits (0.25°C por bit)
  rawData >>= 3;
  temperature = rawData * 0.25;
  
  return temperature;
}

void loop() {
  float temp = readThermocouple();
  
  if (!isnan(temp)) {
    Serial.print("Temperatura: ");
    Serial.print(temp);
    Serial.println(" °C");
  }
  
  delay(1000); // Esperar 1 segundo entre lecturas
}