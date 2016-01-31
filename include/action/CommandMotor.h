#pragma once

#include "Command.h"
#include "Motor.h"

namespace ev3
{
    /**
     * @class CommandMotor
     * Base class for all motor controlling commands.
     * @see ev3dev::motor
     */
    class CommandMotor : public Command
    {
    public:
        /**
         * Constructor with ev3dev::motor parameter.
         * @param motor Motor to execute CommandMotor on.
         */
        CommandMotor(Motor & motor);

    protected:
        /// Command parameter to turn speed regulation on a Motor on.
        const std::string SPEED_REGULATION_ON = "on";
        
        /// Command parameter to turn speed regulation on a Motor off.
        const std::string SPEED_REGULATION_OFF = "off";
        
        /// Motor on which this CommandMotor will be executed.
        Motor _motor;
    };
    

    /**
     * @class CommandMotorReset
     * Call <CODE>reset()</CODE> method of containing Motor.
     */
    class CommandMotorReset : public CommandMotor
    {
    public:
        /**
         * Constructor with ev3dev::motor parameter.
         * @param motor Motor to execute CommandMotor on.
         */
        CommandMotorReset(Motor & motor);
        
        /**
         * @see Command
         */
        void execute() override;
    };

    /**
     * @class CommandMotorRunForever
     * Call <CODE>run_forever()</CODE> method of containing Motor.
     */
    class CommandMotorRunForever : public CommandMotor
    {
    public:
        /**
         * Constructor with ev3dev::motor parameter.
         * @param motor Motor to execute CommandMotor on.
         */
        CommandMotorRunForever(Motor & motor);
        
        /**
         * @see Command
         */
        void execute() override;
    };

    /**
     * @class CommandMotorStop
     * Call <CODE>stop()</CODE> method of containing Motor.
     */
    class CommandMotorStop : public CommandMotor
    {
    public:
        /**
         * Constructor with ev3dev::motor parameter.
         * @param motor Motor to execute CommandMotor on.
         */
        CommandMotorStop(Motor & motor);
        
        /**
         * @see Command
         */        
        void execute() override;
    };

    /**
     * @class CommandMotorSetSpeedRegEnabled
     * Call <CODE>set_speed_regulation_enabled()</CODE> method of containing Motor.
     */
    class CommandMotorSetSpeedRegEnabled : public CommandMotor
    {
    public:
        /**
         * Constructor with ev3dev::motor parameter.
         * @param motor Motor to execute CommandMotor on.
         * @param value If true, turn speed regulation on, false to turn it off.
         */
        CommandMotorSetSpeedRegEnabled(Motor & motor, bool value);
        
        /**
         * @see Command
         */
        void execute() override;

    private:
        /// True value sets speed regulation enabled, false disables it.
        bool _value;
    };

    /**
     * @class CommandMotorSetSpeed
     * Call <CODE>set_speed_sp()</CODE> method of containing Motor.
     */
    class CommandMotorSetSpeed : public CommandMotor
    {
    public:
        /**
         * Constructor with ev3dev::motor parameter.
         * @param motor Motor to execute CommandMotor on.
         * @param value Speed value in tacho pulses per second.
         * @warning Speed regulation must be turned on for this to take effect.
         * @see CommandMotorSetSpeedRegEnabled
         */
        CommandMotorSetSpeed(Motor & motor, int value);
        
        /**
         * @see Command
         */
        void execute() override;

    private:
        /// Speed value in tacho pulses per second.
        int _value;
    };
    
    class CommandMotorSetStopMode : public CommandMotor
    {
    public:
        enum StopMode {
            COAST,
            BRAKE,
            HOLD
        };
        
        /**
         * Constructor with ev3dev::motor parameter.
         * @param motor Motor to execute CommandMotor on.
         * @param mode TODO
         */
        CommandMotorSetStopMode(Motor & motor, StopMode mode);
        
        /**
         * @see Command
         */
        void execute() override;

    private:
        StopMode _mode;
    };
}