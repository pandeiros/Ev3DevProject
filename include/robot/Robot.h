#pragma once
#include "ev3dev.h"
#include "Behaviour.h"
#include "Action.h"
#include "Utils.h"
#include "Queue.h"
#include "LedControl.h"
#include "Devices.h"
#include <vector>
#include <thread>

namespace ev3
{
    class Robot
    {
    public:
        typedef std::vector<Action::ActionType> AvailableActions;

        Robot();
        Robot(Devices::RequiredDevices devices, AvailableActions actions);
        virtual ~Robot();

        std::thread createThread(Queue<Message> * sendQueue, Queue<Message> * receiveQueue);
        virtual void run(Queue<Message> * sendQueue, Queue<Message> * receiveQueue);

        void stop();

    protected:
        unsigned int _id = 0;
        unsigned int _commId = 0;
        
        float _pulsePerUnitRatio = 1.f;
        bool checkDevices();

        Devices::RequiredDevices _requiredDevices;
        AvailableActions _availableActions;

        Behaviour _currentBehaviour;
        Queue<Message> * _sendQueue;
        Queue<Message> * _receiveQueue;
        
        LedControl _ledControl;

    private:
        //void updateStatus();
    };
}

