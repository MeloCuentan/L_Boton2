#include "L_Boton2.h"

Boton::Boton(uint8_t pin, uint32_t tiempoPulsoLargo) {
  _botonPin = pin;
  _tiempoPulsoLargo = tiempoPulsoLargo;
  _intervaloPulsaciones = 0; // Valor por defecto, no usado si no se llama a variasPulsaciones
  _tiempoPresionado = 0;
  _tiempoUltimaPulsacion = 0;
  _estadoAnteriorBoton = LOW;
  _accionBoton = _SIN_PULSAR;
  _estadoActual = _ESPERANDO;
  _contadorPulsaciones = 0;
  _maxPulsaciones = 1;
  _variasPulsacionesActivado = false;

  pinMode(_botonPin, INPUT_PULLUP);
}

void Boton::variasPulsaciones(uint32_t intervaloPulsaciones, uint8_t maxPulsaciones) {
  if (maxPulsaciones == 0) return;
  if (maxPulsaciones > 7) maxPulsaciones = 7;
  _intervaloPulsaciones = intervaloPulsaciones;
  _maxPulsaciones = maxPulsaciones;
  _variasPulsacionesActivado = true;
}

void Boton::actualizar() {
  uint32_t _tiempoActual = millis();
  bool _estadoBoton;
  
  if (_tiempoActual - _tiempoDebounce >= _intervaloDebounce) {
    _tiempoDebounce = _tiempoActual;
    _estadoBoton = digitalRead(_botonPin);
  }

  switch (_estadoActual) {
    case _ESPERANDO:
      if (_estadoBoton == LOW && _estadoAnteriorBoton == HIGH) {  // El botón acaba de ser presionado
        _tiempoPresionado = _tiempoActual;
        _estadoActual = _DETECTANDO_PULSO;
      }
      break;

    case _DETECTANDO_PULSO:
      if (_estadoBoton == HIGH && _estadoAnteriorBoton == LOW) {  // El botón acaba de ser liberado
        if (_tiempoActual - _tiempoPresionado < _tiempoPulsoLargo) {  // Es un pulso corto
          if (_variasPulsacionesActivado) {
            _contadorPulsaciones++;
            _tiempoUltimaPulsacion = _tiempoActual;
            if (_contadorPulsaciones > _maxPulsaciones) {
              _accionBoton = _SIN_PULSAR; // No asignar acción si se supera el máximo de pulsaciones
              _contadorPulsaciones = 0;
              _estadoActual = _ESPERANDO;
            } else {
              _estadoActual = _DETECTANDO_PULSACIONES;
            }
          } else {
            _accionBoton = _PULSO_1;
            _estadoActual = _ESPERANDO;
            _tiempoPresionado = _tiempoActual;
          }
        } else {  // Es un pulso largo
          _accionBoton = _PULSO_LARGO;
          _estadoActual = _ESPERANDO;
        }
      } else if (_estadoBoton == LOW && (_tiempoActual - _tiempoPresionado >= _tiempoPulsoLargo)) {  // Es un pulso largo
        _accionBoton = _PULSO_LARGO;
        _estadoActual = _ESPERANDO;
        _tiempoPresionado = _tiempoActual;
      }
      break;

    case _DETECTANDO_PULSACIONES:
      if (_estadoBoton == LOW && _estadoAnteriorBoton == HIGH) {  // Otra pulsación detectada
        _tiempoPresionado = _tiempoActual;
        _estadoActual = _DETECTANDO_PULSO;
      } else if (_tiempoActual - _tiempoUltimaPulsacion > _intervaloPulsaciones) {  // Se acabó el tiempo para detectar pulsaciones múltiples
        if (_contadorPulsaciones <= _maxPulsaciones) {
          _accionBoton = _contadorPulsaciones;
        } else {
          _accionBoton = _SIN_PULSAR; // No asignar acción si se supera el máximo de pulsaciones
        }
        _contadorPulsaciones = 0;
        _estadoActual = _ESPERANDO;
      }
      break;
  }
  _estadoAnteriorBoton = _estadoBoton;
}

uint8_t Boton::leerEstado() {
  uint8_t _accion = _accionBoton;
  _accionBoton = _SIN_PULSAR;  // Resetea la acción después de ser leída
  return _accion;
}
