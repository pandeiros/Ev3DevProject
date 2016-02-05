#include "CommandSensor.h"
#include "Action.h"

#include <string>

using namespace ev3;

/* COMMAND SENSOR */
CommandSensor::CommandSensor(Sensor & sensor) : _sensor(sensor) { }

Sensor CommandSensor::getSensor()
{
    return _sensor;
}