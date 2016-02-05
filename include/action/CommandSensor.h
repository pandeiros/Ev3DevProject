#pragma once

#include "Command.h"
#include "Sensor.h"

namespace ev3
{
    /**
     * @class CommandSensor
     * Base class for all sensor controlling commands.
     * @see ev3dev::sensor
     */
    class CommandSensor : public Command
    {
    public:
        /**
         * Constructor with ev3dev::sensor parameter.
         * @param sensor Sensor to execute CommandSensor on.
         */
        CommandSensor(Sensor & sensor);
        
        /**
         * Get sensor associated with Command.
         * @return Sensor class object.
         */
        Sensor getSensor();

    protected:        
        /// Sensor on which this CommandSensor will be executed.
        Sensor _sensor;
    };
}