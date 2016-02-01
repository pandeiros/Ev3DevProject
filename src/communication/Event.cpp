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

Sensor::SensorType EventSensorWatch::getType()
{
    return _sensorType;
}

EventAction::EventAction(EventType eventType, Action::ActionType actionType)
: Event(eventType), _actionType(actionType) { }

Action::ActionType EventAction::getActionType()
{
    return _actionType;
}

std::string Event::getStringType()
{
    switch (_type)
    {
        case ACTION_FINISHED:
            return "ACTION_FINISHED";
        case ACTION_INTERR:
            return "ACTION_INTERR";
        case BEHAVIOUR_START:
            return "BEHAVIOUR_START";
        case BEHAVIOUR_STOP:
            return "BEHAVIOUR_STOP";
        case EMPTY:
            return "EMPTY";
        case OBSTACLE_DETECTED:
            return "OBSTACLE_DETECTED";
        case PROXIMITY_ALERT:
            return "PROXIMITY_ALERT";
        case SENSOR_WATCH:
            return "SENSOR_WATCH";
        default:
            return "???";
    }
}




