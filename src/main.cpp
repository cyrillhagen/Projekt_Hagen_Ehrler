#include <Arduino.h>  //Import der Klassen
#include <Servo.h>
#include "Belueftungsklappe.h"
#include "Ventilator.h"
#include "SimulatedESP8266.h"
#include "AirSensor.h"  

#define PIN_BELUEFTUNGSKLAPPE 3   //definieren der PINs

#define PIN_EN 5  //Geschwindigkeit Ventilator
#define PIN_IN1 7  //Richtung, in die der Ventilator dreht
#define PIN_IN2 6  //Richtung, in die der Ventilator dreht

SimulatedESP8266 myESP(12,11);  //PINS anschauen...

AirSensor airSensor1;   //Deklaration Objekte (initialisierung ohne Startwert)
Servo klappe1;

Belueftungsklappe belueftungsklappe1{PIN_BELUEFTUNGSKLAPPE, klappe1} ;
Ventilator ventilator1{PIN_EN,PIN_IN1,PIN_IN2};

String host = "104.248.41.20:1885";

void setup() {
  Serial.begin(9600);
  myESP.setup();
  klappe1.attach(PIN_BELUEFTUNGSKLAPPE);    //PIN Belueftungsklappe setzen
}

void loop() {
  float quality=airSensor1.getAirQuality();   //Auslesen Luftqualität
  belueftungsklappe1.setPositionBelueftungsklappe(quality);   //Position Belueftungsklappe initialisieren
  ventilator1.setVentilatorSpeed(quality);    //Ventilator Geschwindigkeit initialisieren

//  int Speed = analogRead(PIN_EN);
//  int Angle = analogRead(PIN_BELUEFTUNGSKLAPPE);
//  int Airquality = analogRead(quality);
  
//  String payload_speed = "{\"Speed\":" + String(Speed);
//  payload_speed = payload_speed + "}";

//  String payload_angle = "{\"Angle\":" + String(Angle);
//  payload_angle = payload_angle + "}";


//  String payload_quality = "{\"Airquality\":" + String(Airquality);
//  payload_quality = payload_quality + "}";

//  int speedeee = myESP.httpPost(host, "/Venti/postSpeed", payload_speed).toInt();
//  Serial.println(speedeee);

//  int angleeee = myESP.httpPost(host, "//Klappe/postAngle", payload_angle).toInt();
//  Serial.println(angleeee);

//  setSpeed(speedeee);
//  setAngle(angleeee);

//ventilator1.setVentilatorSpeed(quality);

String response = myESP.httpGet(host, "/Data");  
  Serial.println(response);

 String  payload1 = "{\"Airquality\":" + String(airSensor1.getAirQuality()) +
                    ",\"Angle\":" + String(belueftungsklappe1.setPositionBelueftungsklappe(quality)) +
                    ",\"Speed\":" + String(ventilator1.setVentilatorSpeed(quality)) + "}";
//  payload_quality = payload_quality + "}";

myESP.httpPost(host, "/Data", payload1);
  

  
}
