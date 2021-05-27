//Ventilator.h

#include "AirSensor.h"      //Import der Klassenbibliotheken
#include "SimulatedESP8266.h"

#ifndef VENTILATOR_H
#define VENTILATOR_H        //Wenn noch nicht definiert dann definieren

class Ventilator        //KLassendeklaration
{
public:     //Variablen die beim Verwenden eines Objektes dieser Klasse sichtbar sind
    Ventilator(const int PIN_EN, const int PIN_IN1, const int PIN_IN2);
    void setVentilatorSpeed(float quality);

private:        //Variablen die nur innerhalb diser Klasse sichtbar sind
    int speed;
    int PIN_EN;
    const int PIN_IN1;
    const int PIN_IN2;
};

#endif //VENTILATOR_H