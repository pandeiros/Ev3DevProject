#pragma once
#include "ev3dev.h"
#include "Behaviour.h"
#include "Action.h"
#include "Utils.h"
#include "MessageQueue.h"
#include "LedControl.h"
#include <vector>
#include <thread>

namespace ev3
{
    const std::vector<ev3dev::port_type> INPUTS = {ev3dev::INPUT_1, ev3dev::INPUT_2, ev3dev::INPUT_3, ev3dev::INPUT_4};
    const std::vector<ev3dev::port_type> OUTPUTS = {ev3dev::OUTPUT_A, ev3dev::OUTPUT_B, ev3dev::OUTPUT_C, ev3dev::OUTPUT_D};

    //    class RobotStatus
    //    {
    //    public:
    //        RobotStatus();
    //
    ////        float getValueF(ev3dev::port_type port, unsigned int index = 0);
    ////        int getValue(ev3dev::port_type port, unsigned int index = 0);
    //
    //        //std::map<ev3dev::port_type, std::vector<std::pair<int, int> > > values;
    //    };

    class Robot
    {
    public:
        typedef std::vector<std::pair<ev3dev::port_type, ev3dev::device_type>> RequiredDevices;
        typedef std::vector<Action::ActionType> AvailableActions;
        typedef std::map<ev3dev::port_type, ev3dev::motor> MotorsVector;
        typedef std::map<ev3dev::port_type, ev3dev::sensor> SensorsVector;

        static const ev3dev::port_type PORT_ANY;

        Robot();
        Robot(RequiredDevices devices, AvailableActions actions);
        virtual ~Robot();

        std::thread createThread(MessageQueue * sendQueue, MessageQueue * receiveQueue);
        virtual void run(MessageQueue * sendQueue, MessageQueue * receiveQueue);

        void stop();

        //RobotStatus & getRobotStatus();

    protected:
        float _pulsePerUnitRatio = 1.f;
        bool checkDevices();

        MotorsVector _motors;
        SensorsVector _sensors;

        RequiredDevices _requiredDevices;
        AvailableActions _availableActions;

        Behaviour _currentBehaviour;
        MessageQueue * _sendQueue;
        MessageQueue * _receiveQueue;
        
        LedControl _ledControl;

    private:
        //void updateStatus();
    };
}

