#include "RobotState.h"
#include "Utils.h"

#include <iostream>

#define CHANGE_STATE if (_changes.find(msg.getType()) == _changes.end()) \
return this; \
delete this; \
return this->switchState(msg.getType())

#define FORCE_STATE(state) delete this;\
return this->changeState(state)

using namespace ev3;

const float RobotState::MASTER_TIMEOUT = 10.f * 1000; // In milliseconds.

RobotState::RobotState(ChangeMap changes, LedControl * led)
: _changes(changes), _led(led), _masterTimeout(HighResClock::now()) { }

RobotState* RobotState::process(Message msg) { }

Message::MessageType RobotState::getPendingMessage()
{
    Message::MessageType type = _pendingMessage;
    _pendingMessage = Message::EMPTY;
    return type;
}

void RobotState::updateTimer()
{
    _masterTimeout = HighResClock::now();
}

RobotState* RobotState::switchState(Message::MessageType type)
{
    States state = _changes[type];
    return changeState(state);
}

RobotState* RobotState::changeState(States state)
{
    switch (state)
    {
        case IDLE:
            return new RobotStateIdle(_led);
        case ACTIVE:
            return new RobotStateActive(_led);
        case PANIC:
            return new RobotStatePanic(_led);
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

RobotStatePanic::RobotStatePanic(LedControl* led)
: RobotState({
    {Message::MASTER_OVER, IDLE}
}, led)
{
    led->flashColor(LedControl::RED, 200, 0);
}

RobotState* RobotStateIdle::process(Message msg)
{
    std::cout << DurationMilli(HighResClock::now() - _masterTimeout).count() << "\n";
    if (DurationMilli(HighResClock::now() - _masterTimeout).count() >= MASTER_TIMEOUT)
    {
        // Cannot connect to the master, enter Panic state.
        FORCE_STATE(PANIC);
    }
    else if (msg.getType() != Message::MASTER)
    {
        _pendingMessage = Message::AGENT;
    }

    CHANGE_STATE;
}

RobotState* RobotStateActive::process(Message msg)
{
    if (DurationMilli(HighResClock::now() - _masterTimeout).count() >= MASTER_TIMEOUT)
    {
        //_pendingMessage = Message::AGENT_OVER;
    }
    else if (msg.getType() != Message::MASTER)
    {
        //_pendingMessage = Message::AGENT;
    }

    CHANGE_STATE;
}

RobotState* RobotStatePanic::process(Message msg)
{
    if (DurationMilli(HighResClock::now() - _masterTimeout).count() >= MASTER_TIMEOUT)
    {
        // TODO Generate event instead.
        _pendingMessage = Message::AGENT_OVER;
    }
    else if (msg.getType() != Message::MASTER)
    {
        //_pendingMessage = Message::AGENT;
    }

    CHANGE_STATE;
}




