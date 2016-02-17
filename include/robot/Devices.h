#pragma once

#include "ev3dev.h"
#include "Motor.h"
#include "Sensor.h"
#include "Utils.h"

/**
 * @file Devices.h
 * Contains Devices classes.
 */

namespace ev3
{
    /// Type for storing all available Sensor inputs.
    const std::vector<ev3dev::port_type> INPUTS = {ev3dev::INPUT_1, ev3dev::INPUT_2, ev3dev::INPUT_3, ev3dev::INPUT_4};
    
    /// Type for storing all available Motor outpus.
    const std::vector<ev3dev::port_type> OUTPUTS = {ev3dev::OUTPUT_A, ev3dev::OUTPUT_B, ev3dev::OUTPUT_C, ev3dev::OUTPUT_D};

    /**
     * @class Devices
     * Singleton class responsible for managing devices connected to the robot.
     */
    class Devices
    {
    public:
        /// Type for mapping Motor objects to their assigned ports.
        typedef std::map<ev3dev::port_type, Motor> MotorsVector;
        
        /// Type for mapping Sensor objects to their assigned ports.
        typedef std::map<ev3dev::port_type, Sensor> SensorsVector;
        
        /// Vector of pairs mapping port to required device.
        typedef std::vector<std::pair<ev3dev::port_type, ev3dev::device_type> > RequiredDevices;
        
        /// Map containing pairs port-values for all sensors.
        typedef std::map<ev3dev::port_type, SensorValue > SensorStatus;
        
        /// Can be used to define that device port is irrelevant.
        static const ev3dev::port_type PORT_ANY;
                
        /**
         * Instance getter.
         * @return Create previously or new instance of class Devices.
         */
        static Devices * getInstance();
        
        /**
         * Deallocate instance.
         */
        static void destroy();
        
        /**
         * Check connected devices and requirements.
         * @param devices Vector of required devices.
         * @return True if everything is connected properly, false otherwise.
         */
        bool checkDevices(RequiredDevices & devices);
        
        /**
         * Performs update on measuring values.
         */
        void update();
        
        /**
         * Add listener for given Sensor type.
         * @param type Type of Sensor for which value to watch.
         */
        void addListener(Sensor::SensorType type);
        
        /**
         * Remove listener for given Sensor type.
         * @param type Type of Sensor for which value not to watch anymore.
         */
        void removeListener(Sensor::SensorType type);
        
        /**
         * Motor getter.
         * @param port Port id on which the Motor is.
         * @return Motor object assigned to specified port.
         */
        Motor getMotor(ev3dev::port_type port);
        
        /**
         * Sensor getter.
         * @param port Port id on which the Sensor is.
         * @return Sensor object assigned to specified port.
         */
        Sensor getSensor(ev3dev::port_type port);
        
        /**
         * Specify port on which touch sensor that detects collisions is.
         * @param port Port for safety touch sensor.
         */
        void setSafetyTouchSensor(ev3dev::port_type port);
        
        /**
         * Specify port on which proximity sensor that detects obstacles is.
         * @param port Port for proximity sensor.
         */
        void setProximitySensor(ev3dev::port_type port);
        
        /**
         * Stops all Motors.
         */
        void stopAllDevices();
        
    protected:
        /**
         * Default protected constructor (preventing object construction).
         */
        Devices();
        
        /**
         * Default protected copy constructor (preventing object construction by copying).
         * @param other Other Devices object.
         */
        Devices(const Devices& other);
        
        /**
         * Protected assignment operator (preventing object assignment).
         * @param other Other Devices object.
         * @return Copy of passed object.
         */
        Devices& operator=(const Devices& other);
        
        /**
         * Default protected destructor (preventing object unwanted destruction).
         */
        ~Devices(); // Prevent unwanted destruction
        
        /// Instance of Devices singleton class.
        static Devices * _instance;
        
        /// Sensor listeners.
        std::map<Sensor::SensorType, bool> _listeners;
        
        /// Touch sensor for detecting collisions.
        std::map<ev3dev::port_type, int> _safetyTouchSensors;
        
        /// Proximity sensors for detecting obstacles.
        std::map<ev3dev::port_type, int> _proximitySensors;
        
        /// Stored Motor objects.
        MotorsVector _motors;
        
        /// Stored Sensor objects.
        SensorsVector _sensors;
        
        /// Sensors' status with all values.
        SensorStatus _status;
    };
}