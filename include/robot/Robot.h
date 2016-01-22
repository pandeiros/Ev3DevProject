#pragma once
#include "ev3dev.h"
#include "Behaviour.h"
#include "Action.h"
#include "Utils.h"
#include "Queue.h"
#include "LedControl.h"
#include "Devices.h"
#include "RobotState.h"

#include <vector>
#include <thread>

namespace ev3
{
    /**
     * @class Robot
     */
    class Robot
    {
    public:
        /// Type for specifying all available actions for given Robot model.
        typedef std::vector<Action::ActionType> AvailableActions;

        Robot();
        Robot(Devices::RequiredDevices devices, AvailableActions actions);
        virtual ~Robot();

        std::thread createThread(Queue<Message> * sendQueue, Queue<Message> * receiveQueue);
        virtual void run(Queue<Message> * sendQueue, Queue<Message> * receiveQueue);

        void stop();

    protected:
        virtual SharedPtrBehaviour generateBehaviour(Behaviour::BehaviourType type, StringVector parameters) = 0;
        
        unsigned int _id = 0;
        unsigned int _commId = 0;

        float _pulsePerUnitRatio = 1.f;

        Devices::RequiredDevices _requiredDevices;
        AvailableActions _availableActions;

        SharedPtrBehaviour _currentBehaviour;
        Queue<Message> * _sendQueue;
        Queue<Message> * _receiveQueue;

        LedControl _ledControl;

        RobotState * _state = new RobotStateIdle(&_ledControl);

        
    private:
        void processState();
        void processMessage();
        void processBehaviour();
        
        void sendInfo();
        
        Message _currentMessage;
    };
}

