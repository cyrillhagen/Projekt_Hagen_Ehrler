#include <Arduino.h>  //Import der Klassen
#include <Servo.h>
#include "Belueftungsklappe.h"
#include "Ventilator.h"
#include "SimulatedESP8266.h"
#include "AirSensor.h"  

#define PIN_BELUEFTUNGSKLAPPE 3   //definieren der PINs

#define PIN_EN 5
#define PIN_IN1 7
#define PIN_IN2 6


AirSensor airSensor1;   //Deklaration Objekte (initialisierung ohne Startwert)
Servo klappe1;

Belueftungsklappe belueftungsklappe1{PIN_BELUEFTUNGSKLAPPE, klappe1} ;
Ventilator ventilator1{PIN_EN,PIN_IN1,PIN_IN2};


void setup() {
  Serial.begin(9600);
  klappe1.attach(PIN_BELUEFTUNGSKLAPPE);    //PIN Belueftungsklappe setzen
}

void loop() {
  float quality=airSensor1.getAirQuality();   //Auslesen Luftqualität
  belueftungsklappe1.setPositionBelueftungsklappe(quality);   //Position Belueftungsklappe initialisieren
  ventilator1.setVentilatorSpeed(quality);    //Ventilator Geschwindigkeit initialisieren
}
