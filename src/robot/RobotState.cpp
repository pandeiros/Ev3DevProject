#include "RobotState.h"
#include "Utils.h"
#include "Logger.h"
#include "EventQueue.h"

#include <iostream>

#define CHANGE_STATE if (_changes.find(msg.getType()) == _changes.end()) \
return this; \
SharedPtrBehaviour behaviour = _currentBehaviour; \
delete this; \
RobotState * newState = this->switchState(msg.getType()); \
newState->setBehaviour(behaviour); \
return newState;    

#define FORCE_STATE(state) delete this;\
return this->changeState(state)

using namespace ev3;

const float RobotState::MASTER_TIMEOUT = 10.f * 1000; // In milliseconds.
const float RobotState::MASTER_PING_TIME = 3.f * 1000; // In milliseconds.

/* ROBOT STATE */
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

void RobotState::setBehaviour(SharedPtrBehaviour behaviour)
{
    _currentBehaviour = behaviour;
}

SharedPtrBehaviour RobotState::getBehaviour()
{
    return _currentBehaviour;
}

RobotState* RobotState::switchState(Message::MessageType type)
{
    States state = _changes[type];
    return changeState(state);
}

RobotState* RobotState::changeState(States state)
{
    RobotState * newState;
    
    switch (state)
    {
        case IDLE:
            Logger::getInstance()->log("Changing state to IDLE", Logger::INFO);
            newState = new RobotStateIdle(_led);
            break;
        case ACTIVE:
            Logger::getInstance()->log("Changing state to ACTIVE", Logger::INFO);
            newState = new RobotStateActive(_led);
            break;
        case WORKING:
            Logger::getInstance()->log("Changing state to WORKING", Logger::INFO);
            newState = new RobotStateWorking(_led);
            break;
        case PAUSED:
            Logger::getInstance()->log("Changing state to PAUSED", Logger::INFO);
            newState = new RobotStatePaused(_led);
            break;
        case PANIC:
            Logger::getInstance()->log("Changing state to PANIC", Logger::INFO);
            newState = new RobotStatePanic(_led);
            break;
        default:
            newState = this;
    }

    return newState;
}

/* ROBOT STATES CONSTRUCTORS  */
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
    _pendingMessage = Message::ACK;
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

/* ROBOT STATES PROCESSING METHODS */
RobotState* RobotStateIdle::process(Message msg)
{
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

    CHANGE_STATE;
}

RobotState* RobotStateActive::process(Message msg)
{
    if (DurationMilli(HighResClock::now() - _masterTimeout).count() >= MASTER_TIMEOUT)
    {
        FORCE_STATE(PANIC);
    }
    else if (msg.getType() == Message::START)
    {
        EventQueue::getInstance()->push(std::make_shared<Event>(Event::BEHAVIOUR_START));
    }

    CHANGE_STATE;
}

RobotState* RobotStateWorking::process(Message msg)
{
    if (DurationMilli(HighResClock::now() - _masterTimeout).count() >= MASTER_TIMEOUT)
    {
        // Cannot connect to the master, enter PAUSED state.

        _currentBehaviour->stop();
        FORCE_STATE(PAUSED);
    }

    // Process behaviour.
    if (_currentBehaviour.get() != nullptr && _currentBehaviour != nullptr) // && _behaviourSet)
        _currentBehaviour->process();
    else
        Logger::getInstance()->log("Behaviour is NULL!", Logger::ERROR);

    CHANGE_STATE;
}

RobotState* RobotStatePaused::process(Message msg)
{
    if (DurationMilli(HighResClock::now() - _masterTimeout).count() >= MASTER_TIMEOUT)
    {
        // Cannot connect to the master, enter PANIC state.
        FORCE_STATE(PANIC);
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

    CHANGE_STATE;
}




