#include "CommandMotor.h"
#include "Action.h"

#include <string>

using namespace ev3;

CommandMotor::CommandMotor(Motor & motor) : _motor(motor) { }

void CommandMotor::printDebug()
{
    std::cout << "[MOTOR] " << _debugInfo << "\n";
}

CommandMotorReset::CommandMotorReset(Motor & motor) : CommandMotor(motor)
{
    this->_debugInfo = "Reset";
}

void CommandMotorReset::execute()
{
    this->_motor.getMotor().reset();
}

CommandMotorRunForever::CommandMotorRunForever(Motor & motor) : CommandMotor(motor)
{
    this->_debugInfo = "Run forever";
}

void CommandMotorRunForever::execute()
{
    this->_motor.getMotor().run_forever();
}

CommandMotorStop::CommandMotorStop(Motor & motor) : CommandMotor(motor)
{
    this->_debugInfo = "Stop";
}

void CommandMotorStop::execute()
{
    this->_motor.getMotor().stop();
}

CommandMotorSetSpeedRegEnabled::CommandMotorSetSpeedRegEnabled(Motor & motor, bool value) :
CommandMotor(motor), _value(value)
{
    this->_debugInfo = "Set speed regulation : " + (_value ? SPEED_REGULATION_ON : SPEED_REGULATION_OFF);
}

void CommandMotorSetSpeedRegEnabled::execute()
{
    this->_motor.getMotor().set_speed_regulation_enabled(_value ? SPEED_REGULATION_ON : SPEED_REGULATION_OFF);
}

CommandMotorSetSpeed::CommandMotorSetSpeed(Motor & motor, int value) :
CommandMotor(motor), _value(value)
{
    this->_debugInfo = "Set speed : " + std::to_string(_value);
}

void CommandMotorSetSpeed::execute()
{
    this->_motor.getMotor().set_speed_sp(_value);
}