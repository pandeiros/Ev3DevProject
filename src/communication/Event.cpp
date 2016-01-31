#include "Event.h"

using namespace ev3;

Event::Event()
: _type(EMPTY) { }

Event::Event(EventType type)
: _type(type) { }

Event::EventType Event::getType()
{
    return _type;
}

EventSensorWatch::EventSensorWatch(Sensor::SensorType type, SensorValue value)
: Event(SENSOR_WATCH), _sensorType(type), _sensorValue(value) { }

SensorValue EventSensorWatch::getValue()
{
    return _sensorValue;
}


