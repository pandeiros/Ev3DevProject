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
        void send(Message message);
        
        virtual std::string getString();

    protected:
        virtual SharedPtrBehaviour generateBehaviour(SharedPtrBehaviour & ptr, Behaviour::BehaviourType type, StringVector parameters);

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
        void processEvents();
        void processMessage();
        void processBehaviour();

        void sendInfo();

        bool _behaviourSet = false;
        Message _currentMessage;
    };
}
