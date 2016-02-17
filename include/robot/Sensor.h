#pragma once

#include "ev3dev.h"
#include "Utils.h"

namespace ev3
{
    /**
     * @class Sensor 
     * Encapsulates ev3dev::sensor. Can provide additional logic.
     */
    class Sensor
    {
    public:
        /**
         * Sensor type.
         */
        enum SensorType {
            TOUCH,      /**< Touch sensor. */
            COLOR,      /**< Color sensor. */
            ULTRASONIC, /**< Ultrasonic sensor. */
            GYRO,       /**< Gyroscope sensor. */
            INFRARED,   /**< Infrared sensor. */
            SOUND,      /**< Sound sensor. */
            LIGHT       /**< Light sensor. */
        };
        
        /**
         * Constructor with sensor object and type.
         * @param sensor ev3dev sensor object.
         * @param type Sensor type value.
         */
        Sensor(ev3dev::sensor sensor, SensorType type);

        /**
         * Sensor getter.
         * @return Stored ev3dev::sensor object.
         */
        ev3dev::sensor getSensor();
        
        /**
         * Value getter.
         * @param n Id of the value desired.
         * @return Integer with Sensor's value.
         */
        int getValue(unsigned int n);
        
        /**
         * Float value getter.
         * @param n Id of the value desired.
         * @return Float with Sensor's value.
         */
        float getValueF(unsigned int n);
        
        /**
         * Number of decimal places getter.
         * @return Integer with number of places that a true Sensor value has.
         */
        int getDecimals();
        
        /**
         * Number of different values getter.
         * @return Integer with number of different measurements available.
         */
        unsigned int getNumValues();
        
        /**
         * Sensor type getter.
         * @return SensorType value.
         */
        SensorType getType();
        
        /**
         * Prepare vector of parameters for Message object.
         * @param value Measured values.
         * @param type Used Sensor type.
         * @return Vector with Sensor values as strings.
         */
        static StringVector prepareMessage(SensorValue value, SensorType type);

    private:
        /// This Sensor type.
        SensorType _type;
        
        /// Stored motor.
        ev3dev::sensor _sensor;

    };
}
