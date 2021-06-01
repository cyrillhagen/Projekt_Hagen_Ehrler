// Ventilator.cpp

#include <Arduino.h>        //Import der Klassenbibliotheken
#include "Ventilator.h"
#include "AirSensor.h"
//Initialisiere PIN und Geschwindigkeit
Ventilator::Ventilator(const int PIN_EN, const int PIN_IN1, const int PIN_IN2) : PIN_EN{PIN_EN}, PIN_IN1{PIN_IN1}, PIN_IN2{PIN_IN2}
{
    pinMode(PIN_EN, OUTPUT);
    pinMode(PIN_IN1, OUTPUT);
    pinMode(PIN_IN2, OUTPUT);

    digitalWrite(PIN_IN1, HIGH);
    digitalWrite(PIN_IN2, LOW);

    speed = 0;      //Implementierung Konstruktor
}

float Ventilator::setVentilatorSpeed(float quality)      //Geschwindikeitsbedingung
{
    if (quality <= 0.7 && quality >= 0.6)
    {
        speed = 1017-(1270*quality);
    }

    if (quality < 0.6)

    {
        speed = 255;
    }

    else
    {
       speed = 0;
    }
    analogWrite(PIN_EN, speed);
    Serial.println(speed);

    return speed;
}
