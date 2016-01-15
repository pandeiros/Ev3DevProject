#include "Sensor.h"

using namespace ev3;

Sensor::Sensor(ev3dev::sensor sensor)
: _sensor(sensor) { }

ev3dev::sensor Sensor::getSensor()
{
    return _sensor;
}

int Sensor::getValue(unsigned int n)
{
    return _sensor.value(n);
}

int Sensor::getDecimals()
{
    return _sensor.decimals();
}

float Sensor::getValueF(unsigned int n)
{
    return _sensor.float_value(n);
}

unsigned int Sensor::getNumValues()
{
    return _sensor.num_values();
}




