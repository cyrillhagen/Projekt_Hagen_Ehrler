/**
 * @file SimulatedESP8266.h
 * @author Samuel Helbling (samuel.helbling@ost.ch)
 * @brief 
 * @version 0.1
 * @date 2021-04-29
 * 
 * @copyright Copyright (c) 2021
 **/

#include "Arduino.h"
#include <SoftwareSerial.h> //Software Serial library

#ifndef SIMULATEDESP8266
#define SIMULATEDESP8266

class SimulatedESP8266 {

public:
    SimulatedESP8266(int rxPin, int txPin);
    void setup();
    String httpGet(String host, String endpoint, String protocol = "80");
    String httpPost(String host, String endpoint, String payload, String protocol = "80");

private:
    int txPin;
    int rxPin;
    String espData(String command, long timeout, boolean debug);
    SoftwareSerial espSerial = SoftwareSerial(rxPin,txPin);
};

#endif
