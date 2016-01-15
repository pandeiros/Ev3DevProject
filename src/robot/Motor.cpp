#include "Motor.h"

using namespace ev3;

Motor::Motor(ev3dev::motor motor)
: _motor(motor) { }

ev3dev::motor Motor::getMotor()
{
    return _motor;
}

