#pragma once

#include "Message.h"
#include "LedControl.h"

#include <map>

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
        
        typedef std::map<Message::MessageType, RobotState::States> ChangeMap;

        RobotState(ChangeMap changes, LedControl * led);
        virtual RobotState * process(Message msg);

    protected:
        RobotState* switchState(Message::MessageType type);
        
        States _state;
        ChangeMap _changes;
        LedControl * _led;
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
}

