//Belueftungsklappe.cpp

#include <Arduino.h>      //Import der Klassenbibliotheken
#include <Servo.h>
#include "Belueftungsklappe.h"
#include "AirSensor.h"
//Initialisiere PIN und Position
Belueftungsklappe::Belueftungsklappe(int pinBelueftungsklappe, Servo belueftungsklappenposition) : pinBelueftungsklappe{pinBelueftungsklappe}, belueftungsklappenposition{belueftungsklappenposition}
{
    pinMode(pinBelueftungsklappe, OUTPUT);
    position = 0;       //Implementierung Konstruktor
}

float Belueftungsklappe::setPositionBelueftungsklappe(float quality)         //Positionsbedingung
{
    if (quality <= 1 && quality >= 0.7)
    {
        position = 600-(600*quality);
    }
    else 
    {
        position = 180;
    }

    belueftungsklappenposition.write(position);

    Serial.println(position);
    

    return position;
    
}