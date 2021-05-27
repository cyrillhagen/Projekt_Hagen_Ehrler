/**
 * @file AirSensor.h
 * @author Samuel Helbling (samuel.helbling@ost.ch)
 * @brief 
 * @version 0.1
 * @date 2021-04-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef AIRSENSOR_H
#define AIRSENSOR_H

class AirSensor
{
public:
    /**
    * @brief Construct a new Air Sensor object
    * 
    */
    AirSensor();

    /**
    * @brief Returns air quality. 1.0 = Top air quality, 0.0 = very bad air quality
    * The air quality is calculated only when the function is called and at most once per second.
    * 
    * @return Airquality as float beetween 0.0 and 1.0 
    */
    float getAirQuality();

private:
    int airQuality{100};
    unsigned long timeSinceUpdate{0};
    bool goDown{true};
};

#endif
