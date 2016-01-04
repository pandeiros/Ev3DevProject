#pragma once

#include "Command.h"

namespace ev3
{

    class CommandMotor : public Command
    {
    public:
        CommandMotor(ev3dev::motor & m);
        virtual void printDebug() override;
    protected:
        const std::string SPEED_REGULATION_ON = "on";
        const std::string SPEED_REGULATION_OFF = "off";
        ev3dev::motor _m;
    };

    class CommandMotorReset : public CommandMotor
    {
    public:
        CommandMotorReset(ev3dev::motor & m);
        void execute() override;
    };

    class CommandMotorRunForever : public CommandMotor
    {
    public:
        CommandMotorRunForever(ev3dev::motor & m);
        void execute() override;
    };

    class CommandMotorStop : public CommandMotor
    {
    public:
        CommandMotorStop(ev3dev::motor & m);
        void execute() override;
    };

    class CommandMotorSetSpeedRegEnabled : public CommandMotor
    {
    public:
        CommandMotorSetSpeedRegEnabled(ev3dev::motor & m, bool value);
        void execute() override;

    private:
        bool _value;
    };

    class CommandMotorSetSpeed : public CommandMotor
    {
    public:
        CommandMotorSetSpeed(ev3dev::motor & m, int value);
        void execute() override;

    private:
        int _value;
    };
}