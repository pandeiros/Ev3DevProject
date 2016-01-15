#pragma once

#include "Command.h"
#include "Motor.h"

namespace ev3
{
    /**
     * \class CommandMotor
     * Base class for all motor controlling commands.
     */
    class CommandMotor : public Command
    {
    public:
        /**
         * Constructor with ev3dev::motor parameter.
         * @param m Motor to execute CommandMotor on.
         */
        CommandMotor(Motor & motorotor);
        
        /**
         * Print CommandMotors's readable name.
         * Adds "[MOTOR]" tag in front of the name.
         */
        virtual void printDebug() override;
    protected:
        const std::string SPEED_REGULATION_ON = "on";
        const std::string SPEED_REGULATION_OFF = "off";
        Motor _motor;
    };
    

    /**
     * /class CommandMotorReset
     */
    class CommandMotorReset : public CommandMotor
    {
    public:
        CommandMotorReset(Motor & motor);
        void execute() override;
    };

    class CommandMotorRunForever : public CommandMotor
    {
    public:
        CommandMotorRunForever(Motor & motor);
        void execute() override;
    };

    class CommandMotorStop : public CommandMotor
    {
    public:
        CommandMotorStop(Motor & motor);
        void execute() override;
    };

    class CommandMotorSetSpeedRegEnabled : public CommandMotor
    {
    public:
        CommandMotorSetSpeedRegEnabled(Motor & motor, bool value);
        void execute() override;

    private:
        bool _value;
    };

    class CommandMotorSetSpeed : public CommandMotor
    {
    public:
        CommandMotorSetSpeed(Motor & motor, int value);
        void execute() override;

    private:
        int _value;
    };
}