// Belueftungsklappe.h

#include "AirSensor.h"      //Import der Klassenbibliotheken
#include "Servo.h"

#ifndef BELUEFTUNGSKLAPPE_H
#define BELUEFTUNGSKLAPPE_H     //Wenn noch nicht definiert dann definieren

class Belueftungsklappe     //KLassendeklaration
{
public:     //Variablen die beim Verwenden eines Objektes dieser Klasse sichtbar sind
    Belueftungsklappe(int pinBelueftungsklappe, Servo belueftungsklappenposition);      //Dekleration Konstruktor
    float setPositionBelueftungsklappe(float quality);

private:       //Variablen die nur innerhalb diser Klasse sichtbar sind
    int position;
    int pinBelueftungsklappe;
    Servo belueftungsklappenposition;
};

#endif //BELUEFTUNGSKLAPPE_H