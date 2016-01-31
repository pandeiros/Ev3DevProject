#include "Behaviour.h"
#include "Logger.h"

#include <iostream>

using namespace ev3;

Behaviour::~Behaviour()
{
    for (auto & state : _states)
        delete(state.getAction());
}

Behaviour::Behaviour(BehaviourType type, BehaviourStates states)
: _type(type), _states(states)
{
    if (_states.size() > 0)
        _currentState = states[0];
};

Behaviour::Behaviour(BehaviourType type)
: _type(type) { };

void Behaviour::process()
{
    Logger::getInstance()->log("Behaviour process", Logger::VERBOSE);
    unsigned int result = _currentState.process();

    try
    {
        if (result >= 0 && result < _states.size())
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

StringVector Behaviour::getPrototype() { }

StringVector Behaviour::getParameters(StringVector proto) { }

std::string Behaviour::getString()
{
    return "";
}

BehaviourDriveOnSquare::BehaviourDriveOnSquare(unsigned int side, bool turningRight)
: Behaviour(DRIVE_ON_SQUARE), _squareSide(side), _isTurningRight(turningRight) { }

BehaviourDriveOnSquare::BehaviourDriveOnSquare(BehaviourStates states, unsigned int side, bool turningRight)
: Behaviour(DRIVE_ON_SQUARE, states), _squareSide(side), _isTurningRight(turningRight) { }

StringVector BehaviourDriveOnSquare::getPrototype()
{
    return
    {
        std::to_string(_type), std::to_string(_squareSide), std::to_string(_isTurningRight)
    };
}

std::string BehaviourDriveOnSquare::getString()
{
    return "Drive on square: side length (" + std::to_string(_squareSide) +
            "), turning right(" + std::to_string(_isTurningRight) + ")";
}

BehaviourState::BehaviourState(Action * action, unsigned int nextState)
: _action(action), _nextStateId(nextState) { }

unsigned int BehaviourState::process()
{
    Logger::getInstance()->log("State", Logger::VERBOSE);

    if (!_action)
    {
        Logger::getInstance()->log("Null Action pointer!", Logger::ERROR);
    }
    else if (_action->getType() == Action::REPEAT || !_isExecuted)
    {
        Logger::getInstance()->log("Execute", Logger::VERBOSE);
        _action->execute();
        _isExecuted = true;
    }
    else if (_action->isFinished())
    {
        Logger::getInstance()->log("Finished", Logger::VERBOSE);
        return _nextStateId;
    }

    return -1;
}

Action* BehaviourState::getAction()
{
    return _action;
}






