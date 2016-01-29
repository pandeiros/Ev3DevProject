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
    return _pendingMessage;
}

void RobotState::updateTimer()
{
    _pendingMessage = Message::EMPTY;
    _masterTimeout = HighResClock::now();
}

bool RobotState::isPendingEnabled()
{
    if (_pendingTimeout != -1 && DurationMilli(HighResClock::now() - _messageDelay).count() >= _pendingTimeout)
    {
        _messageDelay = HighResClock::now();
        _pendingTimeout = -1;
        return true;
    }
    else
        return false;
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
        case WORKING:
            return new RobotStateWorking(_led);
        case PAUSED:
            return new RobotStatePaused(_led);
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
    {Message::MASTER_OVER, IDLE},
    {Message::START, WORKING}
}, led)
{
    led->flashColor(LedControl::YELLOW, 200, 0);
}

RobotStateWorking::RobotStateWorking(LedControl * led)
: RobotState({
    {Message::PAUSE, PAUSED}
}, led)
{
    led->endFlashing();
    led->setColor(LedControl::GREEN);
}

RobotStatePaused::RobotStatePaused(LedControl * led)
: RobotState({
    {Message::RESUME, WORKING}
}, led)
{
    led->setColor(LedControl::AMBER);
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
    //    std::cout << DurationMilli(HighResClock::now() - _masterTimeout).count() << "\n";
    if (DurationMilli(HighResClock::now() - _masterTimeout).count() >= MASTER_TIMEOUT)
    {
        // Cannot connect to the master, enter Panic state.
        FORCE_STATE(PANIC);
    }
    else if (msg.getType() != Message::MASTER)
    {
        if (_pendingTimeout == -1)
        {
            _pendingMessage = Message::AGENT;
            _pendingTimeout = 2.f * 1000;
            _messageDelay = HighResClock::now();
        }
    }
    else if (msg.getType() == Message::MASTER)
    {
        _pendingMessage = Message::ACK;
    }

    CHANGE_STATE;
}

RobotState* RobotStateActive::process(Message msg)
{
    if (DurationMilli(HighResClock::now() - _masterTimeout).count() >= MASTER_TIMEOUT)
    {
        //_pendingMessage = Message::AGENT_OVER;
    }
    else if (msg.getType() == Message::START)
    {
        //_pendingMessage = Message::AGENT;
    }

    CHANGE_STATE;
}

RobotState* RobotStateWorking::process(Message msg)
{
    //std::cout << DurationMilli(HighResClock::now() - _masterTimeout).count() << "\n";
    if (DurationMilli(HighResClock::now() - _masterTimeout).count() >= MASTER_TIMEOUT)
    {
        // Cannot connect to the master, enter PAUSED state.
        FORCE_STATE(PAUSED);
    }
    // TODO Sending data
    //    else if ()
    //    {
    //        _pendingMessage = Message::AGENT;
    //    }

    CHANGE_STATE;
}

RobotState* RobotStatePaused::process(Message msg)
{
    //std::cout << DurationMilli(HighResClock::now() - _masterTimeout).count() << "\n";
    if (DurationMilli(HighResClock::now() - _masterTimeout).count() >= MASTER_TIMEOUT)
    {
        // Cannot connect to the master, enter PANIC state.
        FORCE_STATE(PANIC);
    }
    //    else if (msg.getType() != Message::MASTER)
    //    {
    //        _pendingMessage = Message::AGENT;
    //    }

    CHANGE_STATE;
}

RobotState* RobotStatePanic::process(Message msg)
{
    if (DurationMilli(HighResClock::now() - _masterTimeout).count() >= MASTER_TIMEOUT)
    {
        // TODO Generate event instead.
        _pendingMessage = Message::AGENT_OVER;
    }

    CHANGE_STATE;
}




