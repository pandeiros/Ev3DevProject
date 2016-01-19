#include "RobotState.h"

#include <iostream>

#define CHANGE_STATE if (_changes.find(msg.getType()) == _changes.end()) \
return this; \
delete this; \
return this->switchState(msg.getType())

using namespace ev3;

RobotState::RobotState(ChangeMap changes, LedControl * led)
: _changes(changes), _led(led) { }

RobotState* RobotState::process(Message msg) { }

RobotState* RobotState::switchState(Message::MessageType type)
{
    States state = _changes[type];
    switch (state)
    {
        case IDLE:
            return new RobotStateIdle(_led);
        case ACTIVE:
            return new RobotStateActive(_led);
        default:
            return this;
    }
}

RobotStateIdle::RobotStateIdle(LedControl * led)
: RobotState({
    {Message::MASTER, ACTIVE}
}, led)
{
    led->flashColor(LedControl::GREEN, 200, 0);
}

RobotStateActive::RobotStateActive(LedControl * led)
: RobotState({
    {Message::MASTER_OVER, IDLE}
}, led)
{
    led->flashColor(LedControl::YELLOW, 200, 0);
}

RobotState* RobotStateIdle::process(Message msg)
{
    std::cout << "Idle\n";
    CHANGE_STATE;
}

RobotState* RobotStateActive::process(Message msg)
{
    std::cout << "Active\n";
    CHANGE_STATE;
}



