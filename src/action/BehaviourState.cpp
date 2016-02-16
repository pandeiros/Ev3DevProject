#include "BehaviourState.h"
#include "Logger.h"
#include "EventQueue.h"

using namespace ev3;

BehaviourState::BehaviourState(SharedPtrAction action, unsigned int nextState, bool isStopState)
: _action(action), _nextStateId(nextState), _isStopState(isStopState) { }

BehaviourState::BehaviourState(SharedPtrAction action, unsigned int nextState, ReactionsTransitions reactions)
: _action(action), _nextStateId(nextState), _reactions(reactions) { }

void BehaviourState::setReactions(ReactionsTransitions reactions)
{
    _reactions = reactions;
}

int BehaviourState::getReaction(Event::EventType type)
{
    if (_reactions.find(type) != _reactions.end())
        return _reactions[type];
    else
        return -1;
}

unsigned int BehaviourState::process()
{
    if (!_action)
    {
        Logger::getInstance()->log("Null Action pointer!", Logger::ERROR);
    }
    else if (_action->getType() == Action::REPEAT || !_isExecuted)
    {
        _action->execute();
        _isExecuted = true;
    }
    else if (_action->isFinished())
    {
        EventQueue::getInstance()->push(
                std::make_shared<EventAction>(Event::ACTION_FINISHED, _action->getType()));
        return _nextStateId;
    }

    return -1;
}

SharedPtrAction BehaviourState::getAction()
{
    return _action;
}

void BehaviourState::setNextState(const unsigned int next)
{
    _nextStateId = next;
}

bool BehaviourState::isStopState()
{
    return _isStopState;
}
