#include "CommandMotor.h"
#include "Action.h"

#include <string>

using namespace ev3;

/* COMMAND MOTOR */
CommandMotor::CommandMotor(Motor & motor) : _motor(motor) { }

Motor CommandMotor::getMotor()
{
    return _motor;
}

/* COMMAND MOTOR RESET */
CommandMotorReset::CommandMotorReset(Motor & motor) : CommandMotor(motor)
{
    _debugInfo = "<Motor> Reset";
}

void CommandMotorReset::execute()
{
    _motor.getMotor().reset();
}

/* COMMAND MOTOR RUN FOREVER */
CommandMotorRunForever::CommandMotorRunForever(Motor & motor) : CommandMotor(motor)
{
    _debugInfo = "<Motor> Run forever";
}

void CommandMotorRunForever::execute()
{
    _motor.getMotor().run_forever();
}

/* COMMAND MOTOR STOP */
CommandMotorStop::CommandMotorStop(Motor & motor) : CommandMotor(motor)
{
    _debugInfo = "<Motor> Stop";
}

void CommandMotorStop::execute()
{
    _motor.getMotor().stop();
}

/* COMMAND MOTOR SET SPEED REGULATION ENABLED */
CommandMotorSetSpeedRegEnabled::CommandMotorSetSpeedRegEnabled(Motor & motor, bool value) :
CommandMotor(motor), _value(value)
{
    _debugInfo = "<Motor> Set speed regulation : " + (_value ? SPEED_REGULATION_ON : SPEED_REGULATION_OFF);
}

void CommandMotorSetSpeedRegEnabled::execute()
{
    _motor.getMotor().set_speed_regulation_enabled(_value ? SPEED_REGULATION_ON : SPEED_REGULATION_OFF);
}

/* COMMAND MOTOR SET SPEED */
CommandMotorSetSpeed::CommandMotorSetSpeed(Motor & motor, int value) :
CommandMotor(motor), _value(value)
{
    _debugInfo = "<Motor> Set speed : " + std::to_string(_value);
}

void CommandMotorSetSpeed::execute()
{
    _motor.getMotor().set_speed_sp(_value);
}

/* COMMAND MOTOR SET STOP MODE */
CommandMotorSetStopMode::CommandMotorSetStopMode(Motor& motor, StopMode mode)
: CommandMotor(motor), _mode(mode) { }

void CommandMotorSetStopMode::execute()
{
    switch (_mode)
    {
        case COAST:
            _motor.getMotor().set_stop_command("coast");
            break;
        case BRAKE:
            _motor.getMotor().set_stop_command("brake");
            break;
        case HOLD:
            _motor.getMotor().set_stop_command("hold");
            break;
        default:
            _motor.getMotor().set_stop_command("coast");
    }
}

