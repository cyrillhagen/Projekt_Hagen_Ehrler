/**
 * @file AirSensor.cpp
 * @author Samuel Helbling (samuel.helbling@ost.ch)
 * @brief 
 * @version 0.1
 * @date 2021-04-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Arduino.h"
#include "AirSensor.h"

AirSensor::AirSensor()
{
    Serial.begin(9600);
};

float AirSensor::getAirQuality()
{
    if (millis() - timeSinceUpdate > 1000)
    {
        if (airQuality <= 0)
        {
            goDown = false;
        }
        if (airQuality >= 100)
        {
            goDown = true;
        }
        if (goDown)
        {
            airQuality = airQuality - random(3);
        }
        else
        {
            airQuality = airQuality + random(3);
        }
        timeSinceUpdate = millis();
    }
    Serial.print("Airquality: ");
    Serial.println(airQuality);
    return airQuality/100.0;
}
