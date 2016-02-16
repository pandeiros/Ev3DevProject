#pragma once

#include "Action.h"
#include "Sensor.h"
#include "Utils.h"

namespace ev3
{
    /**
     * @class Event
     * Base class for all Event classes.
     * Triggered when certain events occur during the robot's main
     * loop execution.
     */
    class Event
    {
    public:

        /**
         * Event type.
         */
        enum EventType
        {
            EMPTY,              /**< Empty event, no meaning. */
            BEHAVIOUR_START,    /**< Behaviour was started. */
            BEHAVIOUR_STOP,     /**< Behaviour was stopped. */
            SENSOR_WATCH,       /**< Value was measured from sensor. */
            OBSTACLE_DETECTED,  /**< Robot hit an obstacle. */
            PROXIMITY_ALERT,    /**< Distance sensor triggered alert. */
            ACTION_FINISHED,    /**< Triggered when action was properly executed. */
            ACTION_INTERR       /**< Triggered when action was interrupted.*/
        };

        /**
         * Default constructor.
         */
        Event();
        
        /**
         * Constructor with Event type parameter.
         * @param type Type of the event triggered.
         */
        Event(EventType type);

        /**
         * Event type getter.
         * @return EventType value.
         */
        EventType getType();

        /**
         * Get human-readable Event name.
         * @return String with Event name.
         */
        std::string getStringType();

    private:
        /// Event type value.
        EventType _type;
    };

    /**
     * @class EventSensorWatch
     * Triggered when measurement of certain Sensor occured.
     */
    class EventSensorWatch : public Event
    {
    public:
        /**
         * Constructor with sensor type and measured value.
         * @param type Value identifying sensor type.
         * @param value Vector with all measurements.
         */
        EventSensorWatch(Sensor::SensorType type, SensorValue value);
        
        /**
         * Stored sensor value getter.
         * @return Vector with certain Sensor measurements.
         */
        SensorValue getValue();
        
        /**
         * Stored Sensor type getter.
         * @return Sensor type value.
         */
        Sensor::SensorType getType();

    private:
        /// Sensor type this event concerns.
        Sensor::SensorType _sensorType;
        
        /// Measured values.
        SensorValue _sensorValue;
    };

    /**
     * @class EventAction
     * Event class triggered when something happened with Action. 
     */
    class EventAction : public Event
    {
    public:
        /**
         * Constructor with Event type and Action type.
         * @param eventType One of Event types concerning actions.
         * @param actionType Type of Action this event concerns.
         */
        EventAction(EventType eventType, Action::ActionType actionType);
        
        /**
         * Action type getter.
         * @return Stored type of Action.
         */
        Action::ActionType getActionType();

    private:
        /// Stored Action type.
        Action::ActionType _actionType;
    };
}

