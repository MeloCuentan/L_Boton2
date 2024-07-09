#include "L_Boton2.h"

const uint8_t pinBoton = 2;                 // Pin del pulsador
const uint32_t tiempoPulsoLargo = 1000;     // Tiempo de detección del pulso largo
const uint32_t intervaloPulsaciones = 250;  // Intervalo máximo entre pulsos
const uint8_t numeroPulsaciones = 3;        // Numero de pulsaciones máximas a detectar

// Posibles objetos
// Boton miBoton(pinBoton);  // Objeto básico (por defecto se genera con tiempoPulsoLargo = 2000)
Boton miBoton(pinBoton, tiempoPulsoLargo);  // Objeto con tiempo del pulso largo

void setup() {
  Serial.begin(9600);
  Serial.println("INICIO DEL SISTEMA");
  
  // Si no se llama al siguiente método, solo funcionara como pulso corto y pulso largo
  // miBoton.variasPulsaciones(intervaloPulsaciones, numeroPulsaciones); // Intervalo entre pulsaciones, número máximo de puslaciones a detectar (de 1 a 7)
}

void loop() {
  miBoton.actualizar(); // Actualizamos el estado del botón
  
  uint8_t estadoBoton = miBoton.leerEstado(); // Leemos el estado del botón

  /* 
  miBoton.leerEstado();
  devuelve el número de veces que se ha pulsado
  Si no se ha pulsado devuelve 0
  Si es un pulso largo devuelve 8
  */
  if (estadoBoton != 0) Serial.println(estadoBoton); // si se ha pulsado, muestra el número de pulsaciones
}
