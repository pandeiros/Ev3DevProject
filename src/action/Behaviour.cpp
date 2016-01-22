#include "Behaviour.h"

using namespace ev3;

Behaviour::Behaviour(BehaviourType type, StoredActions actions)
: _type(type), _actions(actions) { };

Behaviour::Behaviour(BehaviourType type)
: _type(type) { };

void Behaviour::execute()
{
    for (auto action : _actions)
    {
        std::cout << action->getActionPrototype() << "\n";
        action->execute();
        while (!action->isFinished())
        {
        };
    }
}

void Behaviour::setActions(StoredActions actions)
{
    _actions = actions;
}

StringVector Behaviour::getParameters(StringVector proto) { }

BehaviourDriveOnSquare::BehaviourDriveOnSquare(StoredActions actions, unsigned int side, bool turningRight)
: Behaviour(DRIVE_ON_SQUARE, actions), _squareSide(side), _isTurningRight(turningRight) { }




