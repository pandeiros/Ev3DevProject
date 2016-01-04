#include "RobotModelA.h"

//#include <iostream>
//#include "ev3dev.h"

using namespace ev3;

RobotModelA::RobotModelA()
: Robot({
    {ev3dev::OUTPUT_B, ev3dev::large_motor::motor_large},
    {ev3dev::OUTPUT_C, ev3dev::large_motor::motor_large},
    {PORT_ANY, ev3dev::sensor::custom_ultrasonic}
},
{

    Action::DRIVE_DISTANCE,
            Action::STOP
})
{
    //    this->_pulsePerUnitRatio = 1.f * COUNT_PER_ROT / (M_PI * 2 * this->_wheelRadius * UNITS_PER_CENTIMETER);
    this->_pulsePerUnitRatio = COUNT_PER_ROT / (M_PI * 2 * this->_wheelRadius * UNITS_PER_CENTIMETER);
}

RobotModelA::~RobotModelA() { }

