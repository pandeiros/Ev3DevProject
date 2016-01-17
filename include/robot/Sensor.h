#pragma once

#include "ev3dev.h"

namespace ev3
{

    class Sensor
    {
    public:
        Sensor(ev3dev::sensor sensor);
        
        ev3dev::sensor getSensor();
        int getValue(unsigned int n);
        float getValueF(unsigned int n);
        int getDecimals();
        unsigned int getNumValues();

    private:
        ev3dev::sensor _sensor;

    };
}
