#pragma once

#include "ev3dev.h"

namespace ev3
{

    class Motor
    {
    public:
        Motor(ev3dev::motor motor);
        
        ev3dev::motor getMotor();
    private:
        ev3dev::motor _motor;
    };

}