#pragma once

#include "Message.h"
#include "LedControl.h"
#include "Utils.h"

#include <map>
#include <chrono>

namespace ev3
{

    class RobotState
    {
    public:

        enum States
        {
            IDLE,
            ACTIVE,
            WORKING,
            PAUSED,
            PANIC
        };

        const static float MASTER_TIMEOUT;

        typedef std::map<Message::MessageType, States> ChangeMap;

        RobotState(ChangeMap changes, LedControl * led);
        virtual RobotState * process(Message msg);

        Message::MessageType getPendingMessage();
        void updateTimer();
        
        bool isPendingEnabled();

    protected:
        RobotState* switchState(Message::MessageType type);
        RobotState* changeState(States state);

        States _state;
        ChangeMap _changes;
        LedControl * _led;
        Message::MessageType _pendingMessage = Message::EMPTY;
        float _pendingTimeout = 0.f;

        HighResClock::time_point _masterTimeout = HighResClock::now();
        HighResClock::time_point _messageDelay = HighResClock::now();
    };

    class RobotStateIdle : public RobotState
    {
    public:
        RobotStateIdle(LedControl * led);
        RobotState * process(Message msg);
    };

    class RobotStateActive : public RobotState
    {
    public:
        RobotStateActive(LedControl * led);
        RobotState * process(Message msg);
    };
    
    class RobotStateWorking : public RobotState
    {
    public:
        RobotStateWorking(LedControl * led);
        RobotState * process(Message msg);
    };
    
    class RobotStatePaused : public RobotState
    {
    public:
        RobotStatePaused(LedControl * led);
        RobotState * process(Message msg);
    };

    class RobotStatePanic : public RobotState
    {
    public:
        RobotStatePanic(LedControl * led);
        RobotState * process(Message msg);
    };
}

