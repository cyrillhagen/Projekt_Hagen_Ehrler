/**
 * @file SimulatedESP8266.cpp
 * @author Samuel Helbling (samuel.helbling@ost.ch)
 * @brief 
 * @version 0.1
 * @date 2021-04-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Arduino.h"
#include "SimulatedESP8266.h"

#define DEBUG false // set to TRUE to get more informations during runtime
uint8_t m_responseBuffer[300] = {0};

SimulatedESP8266::SimulatedESP8266(int rxPin, int txPin) : rxPin{rxPin}, txPin{txPin}
{
}

void SimulatedESP8266::setup()
{
  espSerial.begin(115200);

  espData("AT+RST", 10, DEBUG);                     //Reset the ESP8266 module
  espData("AT+CWMODE=1", 10, DEBUG);                //Set the ESP mode as station mode
  espData("AT+CWJAP=\"VBB\",\"12345\"", 10, DEBUG); //Connect to WiFi network
  Serial.println("ESP ready");
}

String SimulatedESP8266::httpGet(String host, String endpoint, String protocol = "80")
{
  Serial.println("Sending HTTP Get-Request");
  String sendData = "GET " + endpoint;
  espData("AT+CIPMUX=1", 10, DEBUG); //Allow multiple connections
  espData("AT+CIPSTART=0,\"TCP\",\"" + host + "\"," + protocol, 10, DEBUG);
  espData("AT+CIPSEND=0," + String(sendData.length() + 4), 10, DEBUG);
  espSerial.find('>');
  String response = espData(sendData, 10, DEBUG);
  espData("AT+CIPCLOSE=0", 10, DEBUG);
  return response;
}

String SimulatedESP8266::httpPost(String host, String endpoint, String payload, String protocol = "80")
{
  Serial.println("Sending HTTP Post-Request");
  String sendData = "POST " + endpoint +" HTTP/1.1\r"
  + "Host: " + host + "\r"
  + "Content-Type: text/plain\r"
  + "Content-Length: " + payload.length() + "\r\r"
  + payload;
  espData("AT+CIPMUX=1", 10, DEBUG); //Allow multiple connections
  espData("AT+CIPSTART=0,\"TCP\",\"" + host + "\"," + protocol, 10, DEBUG);
  espData("AT+CIPSEND=0," + String(sendData.length() + 4), 10, DEBUG);
  espSerial.find('>');
  String response = espData(sendData, 10, DEBUG);
  espData("AT+CIPCLOSE=0", 10, DEBUG);
  return response;
}

String SimulatedESP8266::espData(String command, long timeout, boolean debug)
{
  String response = "";
  espSerial.println(command);
  long time = millis();
  while ((time + timeout) > millis())
  {
    while (espSerial.available())
    {
      char c = espSerial.read();
      response += c;
    }
  }
  return response;
}

