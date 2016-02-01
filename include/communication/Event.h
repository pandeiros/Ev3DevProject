#pragma once

#include "Action.h"
#include "Sensor.h"
#include "Utils.h"

namespace ev3
{

    class Event
    {
    public:

        enum EventType
        {
            EMPTY,
            BEHAVIOUR_START,
            BEHAVIOUR_STOP,
            SENSOR_WATCH,
            OBSTACLE_DETECTED,
            PROXIMITY_ALERT,
            ACTION_FINISHED,
            ACTION_INTERR
        };

        Event();
        Event(EventType type);

        EventType getType();

        std::string getStringType();

    private:
        EventType _type;
    };

    class EventSensorWatch : public Event
    {
    public:
        EventSensorWatch(Sensor::SensorType type, SensorValue value);
        SensorValue getValue();
        Sensor::SensorType getType();

    private:
        Sensor::SensorType _sensorType;
        SensorValue _sensorValue;
    };

    class EventAction : public Event
    {
    public:
        EventAction(EventType eventType, Action::ActionType actionType);
        
        Action::ActionType getActionType();

    private:
        Action::ActionType _actionType;
    };
}

