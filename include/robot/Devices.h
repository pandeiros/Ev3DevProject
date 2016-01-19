#pragma once

#include "ev3dev.h"
#include "Motor.h"
#include "Sensor.h"

namespace ev3
{
    const std::vector<ev3dev::port_type> INPUTS = {ev3dev::INPUT_1, ev3dev::INPUT_2, ev3dev::INPUT_3, ev3dev::INPUT_4};
    const std::vector<ev3dev::port_type> OUTPUTS = {ev3dev::OUTPUT_A, ev3dev::OUTPUT_B, ev3dev::OUTPUT_C, ev3dev::OUTPUT_D};

    class Devices
    {
    public:
        typedef std::map<ev3dev::port_type, Motor> MotorsVector;
        typedef std::map<ev3dev::port_type, Sensor> SensorsVector;
        typedef std::vector<std::pair<ev3dev::port_type, ev3dev::device_type> > RequiredDevices;
        typedef std::map<ev3dev::port_type, std::vector<std::pair<int, int> > > SensorStatus;
        
        static const ev3dev::port_type PORT_ANY;
                
        static Devices * getInstance();
        static void destroy();
        
        bool checkDevices(RequiredDevices & devices);
        void update();
        void addListener();
        
        Motor getMotor(ev3dev::port_type port);
        Sensor getSensor(ev3dev::port_type port);
        
        void stopAllDevices();
        
    protected:
        Devices(); // Prevent construction
        Devices(const Devices&); // Prevent construction by copying
        Devices& operator=(const Devices&); // Prevent assignment
        ~Devices(); // Prevent unwanted destruction
        static Devices * _instance;
        
        MotorsVector _motors;
        SensorsVector _sensors;
        SensorStatus _status;
    };
}