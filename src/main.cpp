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

SimulatedESP8266 myESP(3,4);  //PINS definieren!!!!!!!

AirSensor airSensor1;   //Deklaration Objekte (initialisierung ohne Startwert)
Servo klappe1;

Belueftungsklappe belueftungsklappe1{PIN_BELUEFTUNGSKLAPPE, klappe1} ;
Ventilator ventilator1{PIN_EN,PIN_IN1,PIN_IN2};

String host = "104.248.41.20:1885";

void setSpeed(int speed)
{
  analogWrite(PIN_EN, speed);
  }    //PINS!!!!!!!

void setAngle(int angle)
{
  analogWrite(PIN_IN1, angle);  //PINS!!!!!!!
  }

void setup() {
  Serial.begin(9600);
  myESP.setup();
  klappe1.attach(PIN_BELUEFTUNGSKLAPPE);    //PIN Belueftungsklappe setzen
}

void loop() {
  float quality=airSensor1.getAirQuality();   //Auslesen Luftqualität
  belueftungsklappe1.setPositionBelueftungsklappe(quality);   //Position Belueftungsklappe initialisieren
  ventilator1.setVentilatorSpeed(quality);    //Ventilator Geschwindigkeit initialisieren

  int Speed = analogRead(PIN_EN);
  int Angle = analogRead(PIN_IN1);
  int Airquality = analogRead(PIN_IN2);
  
  String payload_speed = "{\"Speed\":" + String(Speed);
  payload_speed = payload_speed + "}";

  String payload_angle = "{\"Angle\":" + String(Angle);
  payload_angle = payload_angle + "}";


  String payload_quality = "{\"Airquality\":" + String(Airquality);
  payload_quality = payload_quality + "}";

  int speed = myESP.httpPost(host, "/Venti/postSpeed", payload_speed).toInt();
  Serial.println(speed);

  int angle = myESP.httpPost(host, "//Klappe/postAngle", payload_angle).toInt();
  Serial.println(angle);

  setSpeed(speed);
  setAngle(angle);

  

  
}
