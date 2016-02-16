#include "Behaviour.h"
#include "Logger.h"
#include "EventQueue.h"
#include "Devices.h"

#include <iostream>

using namespace ev3;

/* BEHAVIOUR */
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
    if (!_active)
        return;

    Logger::getInstance()->log("Behaviour process", Logger::DEBUG);
    unsigned int result = _currentState.process();

    try
    {
        if (result >= 0 && result < _states.size())
        {
            if (_currentState.isStopState())
            {
                _currentState = _states[result];
                for (auto & m : _measurements)
                    Devices::getInstance()->addListener(m);
            }
            else
            {
                if (_stopState.getAction() != nullptr)
                {
                    _stopState.setNextState(result);
                    _currentState = _stopState;
                }
                else
                    _currentState = _states[result];
            }
        }
        else if (result == -1)
        {
            //EventQueue::getInstance()->push(std::make_shared<Event>(Event::BEHAVIOUR_STOP));
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

void Behaviour::setReactionStates(BehaviourStates reactionStates)
{
    _reactionStates = reactionStates;
}

void Behaviour::setMeasurements(Measurements measurements)
{
    _measurements = measurements;
}

void Behaviour::setStopState(BehaviourState state)
{
    _stopState = state;
}

StringVector Behaviour::getPrototype() { }

std::string Behaviour::getString()
{
    return "";
}

void Behaviour::stop()
{
    _stopState.process();
    _currentState.setNextState(-1);
    _active = true;
}

void Behaviour::pause()
{
    _stopState.process();
    _active = false;
}

void Behaviour::resume()
{
    _active = true;
}

void Behaviour::start()
{
    _active = true;
    if (_stopState.getAction())
    {
        _stopState.setNextState(0);
        _currentState = _stopState;
    }
    else if (_states.size() > 0)
        _currentState = _states[0];

    Logger::getInstance()->log("Behaviour start.", Logger::VERBOSE);
}

void Behaviour::react(Event::EventType type)
{
    int reaction = _currentState.getReaction(type);

    if (reaction >= 0 && reaction < _reactionStates.size())
    {
        EventQueue::getInstance()->push(
                std::make_shared<EventAction>(Event::ACTION_FINISHED, _currentState.getAction()->getType()));
        _currentState = _reactionStates[reaction];

    }
    else
        Logger::getInstance()->log("Reaction not found. ", Logger::WARNING);
}

/* BEHAVIOUR DRIVE ON SQUARE */
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

/* BEHAVIOUR EXPLORE RANDOM */
BehaviourExploreRandom::BehaviourExploreRandom()
: Behaviour(EXPLORE_RANDOM) { }

BehaviourExploreRandom::BehaviourExploreRandom(BehaviourStates states)
: Behaviour(EXPLORE_RANDOM, states) { }

StringVector BehaviourExploreRandom::getPrototype()
{
    return
    {
        std::to_string(_type)
    };
}

std::string BehaviourExploreRandom::getString()
{
    return "Explore random.";
}
