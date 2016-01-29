#include "Behaviour.h"

using namespace ev3;

Behaviour::Behaviour(BehaviourType type, BehaviourStates states)
: _type(type), _states(states) { };

Behaviour::Behaviour(BehaviourType type)
: _type(type) { };

void Behaviour::process()
{
    unsigned int result = _currentState.process();

    try
    {
        if (result >= 0)
        {
            _currentState = _states[result];
        }
    }
    catch (...)
    {
        // TODO Generate exception event
    }
}

void Behaviour::setStates(BehaviourStates states)
{
    _states = states;
}

StringVector Behaviour::getParameters(StringVector proto) { }

BehaviourDriveOnSquare::BehaviourDriveOnSquare(BehaviourStates states, unsigned int side, bool turningRight)
: Behaviour(DRIVE_ON_SQUARE, states), _squareSide(side), _isTurningRight(turningRight) { }

BehaviourState::BehaviourState(SharedPtrAction action, unsigned int nextState)
: _action(action), _nextStateId(nextState) { }

//
//bool BehaviourState::isExecuted() {
//    return _isExecuted;
// }

unsigned int BehaviourState::process()
{
    if (_action->isFinished())
    {
        return _nextStateId;
    }
    else if (_action->getType() == Action::REPEAT || !_isExecuted)
    {
        _action->execute();
        _isExecuted = true;
    }

    return -1;
}





