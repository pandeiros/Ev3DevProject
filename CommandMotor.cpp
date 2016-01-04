#include "CommandMotor.h"
#include "Action.h"

#include <string>

using namespace ev3;

CommandMotor::CommandMotor(ev3dev::motor & m) : _m(m) { }

void CommandMotor::printDebug()
{
    std::cout << "[MOTOR] " << _debugInfo << "\n";
}

CommandMotorReset::CommandMotorReset(ev3dev::motor & m) : CommandMotor(m)
{
    this->_debugInfo = "Reset";
}

void CommandMotorReset::execute()
{
    this->_m.reset();
}

CommandMotorRunForever::CommandMotorRunForever(ev3dev::motor & m) : CommandMotor(m)
{
    this->_debugInfo = "Run forever";
}

void CommandMotorRunForever::execute()
{
    this->_m.run_forever();
}

CommandMotorStop::CommandMotorStop(ev3dev::motor & m) : CommandMotor(m)
{
    this->_debugInfo = "Stop";
}

void CommandMotorStop::execute()
{
    this->_m.stop();
}

CommandMotorSetSpeedRegEnabled::CommandMotorSetSpeedRegEnabled(ev3dev::motor & m, bool value) :
CommandMotor(m), _value(value)
{
    this->_debugInfo = "Set speed regulation : " + (_value ? SPEED_REGULATION_ON : SPEED_REGULATION_OFF);
}

void CommandMotorSetSpeedRegEnabled::execute()
{
    this->_m.set_speed_regulation_enabled(_value ? SPEED_REGULATION_ON : SPEED_REGULATION_OFF);
}

CommandMotorSetSpeed::CommandMotorSetSpeed(ev3dev::motor & m, int value) :
CommandMotor(m), _value(value)
{
    this->_debugInfo = "Set speed : " + std::to_string(_value);
}

void CommandMotorSetSpeed::execute()
{
    this->_m.set_speed_sp(_value);
}