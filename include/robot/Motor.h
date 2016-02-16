#pragma once

#include "ev3dev.h"

namespace ev3
{

    /**
     * @class Motor
     * Encapsulates ev3dev::motor. Can provide additional logic.
     */
    class Motor
    {
    public:
        /**
         * Constructor with Motor.
         * @param motor ev3dev::Motor object.
         */
        Motor(ev3dev::motor motor);

        /**
         * Motor getter.
         * @return Stored ev3dev::motor object.
         */
        ev3dev::motor getMotor();

    private:
        /// Stored motor.
        ev3dev::motor _motor;
    };
}