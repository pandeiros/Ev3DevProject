#pragma once

#include "ev3dev.h"
#include "Utils.h"

namespace ev3
{

    class Sensor
    {
    public:
        enum SensorType {
            TOUCH,
            COLOR,
            ULTRASONIC,
            GYRO,
            INFRARED,
            SOUND,
            LIGHT
        };
        
        Sensor(ev3dev::sensor sensor, SensorType type);

        ev3dev::sensor getSensor();
        int getValue(unsigned int n);
        float getValueF(unsigned int n);
        int getDecimals();
        unsigned int getNumValues();
        SensorType getType();
        
        static StringVector prepareMessage(SensorValue value);

    private:
        SensorType _type;
        ev3dev::sensor _sensor;

    };
}
