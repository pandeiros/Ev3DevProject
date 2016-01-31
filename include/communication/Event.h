#pragma once

#include "Sensor.h"
#include "Utils.h"

namespace ev3
{

    class Event
    {
    public:
        enum EventType {
            EMPTY,
            BEHAVIOUR_START,
            BEHAVIOUR_STOP,
            SENSOR_WATCH
        };
        
        Event();
        Event(EventType type);
        
        EventType getType();

    private:
        EventType _type;
    };
    
    class EventSensorWatch : public Event 
    {
    public:
        EventSensorWatch(Sensor::SensorType type, SensorValue value);
        SensorValue getValue ();
    private:
        Sensor::SensorType _sensorType;
        SensorValue _sensorValue;
    };
}

