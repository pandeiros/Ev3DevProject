#include "Sensor.h"
#include "Utils.h"

using namespace ev3;

Sensor::Sensor(ev3dev::sensor sensor, SensorType type)
: _sensor(sensor), _type(type) { }

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

Sensor::SensorType Sensor::getType()
{
    return _type;
}

StringVector Sensor::prepareMessage(SensorValue value, SensorType type)
{
    StringVector result;
    result.push_back(std::to_string(type));
    for (auto & v : value)
    {
        result.push_back(std::to_string(v.first));
        result.push_back(std::to_string(v.second));
    }
    
    return result;
}






