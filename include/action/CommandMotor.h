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
        
        /**
         * Get motor associated with Command.
         * @return Motor class object.
         */
        Motor getMotor();

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
     * Calls <CODE>reset()</CODE> method of containing Motor.
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
         * Perform <CODE>reset()</CODE> method on Motor.
         */
        void execute() override;
    };

    /**
     * @class CommandMotorRunForever
     * Calls <CODE>run_forever()</CODE> method of containing Motor.
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
         * Perform <CODE>run_forever()</CODE> method on Motor.
         */
        void execute() override;
    };

    /**
     * @class CommandMotorStop
     * Calls <CODE>stop()</CODE> method of containing Motor.
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
         * Perform <CODE>stop()</CODE> method on Motor.
         */        
        void execute() override;
    };

    /**
     * @class CommandMotorSetSpeedRegEnabled
     * Calls <CODE>set_speed_regulation_enabled()</CODE> method of containing Motor.
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
         * Perform <CODE>set_speed_regulation_enabled()</CODE> on Motor.
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
         * Perform <CODE>set_speed_sp()</CODE> method on Motor.
         */
        void execute() override;

    private:
        /// Speed value in tacho pulses per second.
        int _value;
    };
    
    /**
     * @class CommandMotorSetStopMode
     * Calls <CODE>set_stop_command()</CODE> method of containing Motor.
     */
    class CommandMotorSetStopMode : public CommandMotor
    {
    public:
        
        /**
         * Stop modes for motors.
         */
        enum StopMode {
            COAST,      /**< No voltage. Motor slowly stops.*/
            BRAKE,      /**< Passive braking. Motor stops faster.*/
            HOLD        /**< Active braking. Hardly prevent motor from any movement. */
        };
        
        /**
         * Constructor with ev3dev::motor parameter.
         * @param motor Motor to execute CommandMotor on.
         * @param mode Stop mode chosen from StopMode.
         */
        CommandMotorSetStopMode(Motor & motor, StopMode mode);
        
        /**
         * Perform <CODE>set_stop_command()</CODE> method on Motor.
         */
        void execute() override;

    private:
        /// Mode chosen to be selected on Motor when exeuted.
        StopMode _mode;
    };
}