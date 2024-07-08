#ifndef L_BOTON2_H
#define L_BOTON2_H

#include <Arduino.h>

class Boton {
  public:
    Boton(uint8_t pin, uint32_t tiempoPulsoLargo);
    void variasPulsaciones(uint32_t intervaloPulsaciones, uint8_t maxPulsaciones);
    void actualizar();
    uint8_t leerEstado();

  private:
    enum estadosMaquina {
      _ESPERANDO,
      _DETECTANDO_PULSO,
      _ESPERANDO_PULSO_LARGO,
      _DETECTANDO_PULSACIONES
    };
    const uint8_t _SIN_PULSAR = 0;
    const uint8_t _PULSO_1 = 1;
    const uint8_t _PULSO_LARGO = 8;

    bool _estadoAnteriorBoton;
    bool _variasPulsacionesActivado;
    uint8_t _botonPin;
    uint8_t _accionBoton;
    uint8_t _estadoActual;
    uint8_t _contadorPulsaciones;
    uint8_t _maxPulsaciones;
    uint32_t _tiempoPulsoLargo;
    uint32_t _intervaloPulsaciones;
    uint32_t _tiempoPresionado;
    uint32_t _tiempoUltimaPulsacion;
    uint32_t _tiempoDebounce;
    uint32_t _intervaloDebounce = 50;
};

#endif
