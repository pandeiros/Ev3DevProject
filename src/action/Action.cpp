#include "Action.h"

#include <sstream>

using namespace ev3;

const std::string Action::EMPTY_PROTO("::");

Action::Action(CommandsVector commands, ActionType type)
: _commands(commands), _type(type) { };

Action::Action(CommandsVector commands)
: _commands(commands), _type(ActionType::NOP) { };

Action::Action(ActionType type)
: _type(type) { };

Action::~Action() { }

void Action::execute()
{
    for (auto * c : _commands)
    {
        c->execute();
        c->printDebug();
    }
}

bool Action::isFinished()
{
    return _endCondition();
}

std::string Action::getActionPrototype()
{
    return EMPTY_PROTO;
}

void Action::setCommands(CommandsVector commands)
{
    this->_commands = commands;
}

void Action::setEndCondition(EndCondition condition)
{
    this->_endCondition = condition;
}

//void Action::setEndCondition(std::function<int(void) > func, ConditionType type) {
//    this->_endCondition = []() {
//        if (type == Action::GREATER)
//            return func > 
//    }
//}

Action::ActionType Action::getType()
{
    return _type;
}

ActionRepeat::ActionRepeat(std::vector<Action*> actions, unsigned int n)
: Action(ActionType::REPEAT_FOREVER), _actions(actions), _n(n) { }

void ActionRepeat::execute()
{
    if (_n == 0)
    {
        while (!this->_repeatCondition())
        {
            for (auto * action : _actions)
            {
                std::cout << action->getActionPrototype() << "\n";
                action->execute();
                while (!action->isFinished())
                {
                };
            }
        }
    }
    else
    {
        for (unsigned int i = 0; i < _n; ++i)
        {
            for (auto * action : _actions)
            {
                std::cout << action->getActionPrototype() << "\n";
                action->execute();
                while (!action->isFinished())
                {
                };
            }
        }
    }
}

void ActionRepeat::setRepeatCondition(EndCondition condition)
{
    this->_repeatCondition = condition;
}

ActionDriveDistance::ActionDriveDistance(int distance)
: Action(ActionType::DRIVE_DISTANCE), _distance(distance) { }

int ActionDriveDistance::getDistance()
{
    return _distance;
}

//bool ActionDriveDistance::isFinished() { }

std::string ActionDriveDistance::getActionPrototype()
{
    std::stringstream ss;

    ss << _type << "::" << _distance;
    return ss.str();
}

ActionRotate::ActionRotate(int rotation)
: Action(ActionType::ROTATE), _rotation(rotation) { }

int ActionRotate::getRotation()
{
    return _rotation;
}

//bool ActionDriveDistance::isFinished() { }

std::string ActionRotate::getActionPrototype()
{
    std::stringstream ss;

    ss << _type << "::" << _rotation;
    return ss.str();
}