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
         * 
         * @param sensor
         * @param type
         */
        Sensor(ev3dev::sensor sensor, SensorType type);

        /**
         * 
         * @return 
         */
        ev3dev::sensor getSensor();
        
        /**
         * 
         * @param n
         * @return 
         */
        int getValue(unsigned int n);
        
        /**
         * 
         * @param n
         * @return 
         */
        float getValueF(unsigned int n);
        
        /**
         * 
         * @return 
         */
        int getDecimals();
        
        /**
         * 
         * @return 
         */
        unsigned int getNumValues();
        
        /**
         * 
         * @return 
         */
        SensorType getType();
        
        /**
         * 
         * @param value
         * @param type
         * @return 
         */
        static StringVector prepareMessage(SensorValue value, SensorType type);

    private:
        ///
        SensorType _type;
        
        ///
        ev3dev::sensor _sensor;

    };
}
