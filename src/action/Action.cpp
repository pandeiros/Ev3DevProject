#include "Action.h"
#include "Logger.h"

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
    Logger::getInstance()->log(getString(), Logger::DEBUG);

    for (auto c : _commands)
    {
        c->execute();
        //        Logger::getInstance()->log("Command " + c->getString(), Logger::DEBUG);
    }

    _isExecuted = true;
}

bool Action::isFinished()
{
    return _endCondition();
}

bool Action::isExecuted()
{
    return _isExecuted;
}

std::string Action::getActionPrototype()
{
    return EMPTY_PROTO;
}

std::string Action::getString()
{
    return "Base Action";
}

void Action::setCommands(CommandsVector commands)
{
    this->_commands = commands;
}

void Action::setEndCondition(EndCondition condition)
{
    this->_endCondition = condition;
}

Action::ActionType Action::getType()
{
    return _type;
}

ActionRepeat::ActionRepeat(StoredActions actions, unsigned int n)
: Action(ActionType::REPEAT), _actions(actions), _n(n) { }

void ActionRepeat::execute()
{
    Logger::getInstance()->log(getString(), Logger::DEBUG);

    if (_n == 0)
    {
        if (_actions[_currentAction]->isFinished())
        {
            _currentAction = (_currentAction + 1) % _actions.size();

            _actions[_currentAction]->execute();
        }
    }
    else
    {
        if (_currentIteration < _n)
        {
            if (_isExecuted && _currentAction == _actions.size() - 1 &&
                _actions[_currentAction]->isFinished())
            {
                ++_currentIteration;
            }

            if (_actions[_currentAction]->isFinished())
            {
                _currentAction = (_currentAction + 1) % _actions.size();

                _actions[_currentAction]->execute();
            }
        }
    }

    if (!_isExecuted)
    {
        _actions[_currentAction]->execute();
        _isExecuted = true;
    }
}

std::string ActionRepeat::getString()
{
    return "Action repeat";
}

ActionDriveDistance::ActionDriveDistance(int distance)
: Action(ActionType::DRIVE_DISTANCE), _distance(distance) { }

ActionDriveDistance::ActionDriveDistance(CommandsVector commands, int distance)
: Action(commands, ActionType::DRIVE_DISTANCE), _distance(distance) { }

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

std::string ActionDriveDistance::getString()
{
    return "Action drive distance";
}

ActionRotate::ActionRotate(int rotation)
: Action(ActionType::ROTATE), _rotation(rotation) { }

ActionRotate::ActionRotate(CommandsVector commands, int rotation)
: Action(commands, ActionType::ROTATE), _rotation(rotation) { }

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

std::string ActionRotate::getString()
{
    return "Action rotate";
}

ActionStop::ActionStop()
: Action(ActionType::STOP) { }

ActionStop::ActionStop(CommandsVector commands)
: Action(commands, ActionType::STOP) { }

std::string ActionStop::getActionPrototype()
{
    return std::to_string(_type);
}

std::string ActionStop::getString()
{
    return "Action stop";
}

ActionDriveForever::ActionDriveForever(bool forward)
: Action(ActionType::DRIVE_FOREVER), _isForward(forward) { }

ActionDriveForever::ActionDriveForever(CommandsVector commands, bool forward)
: Action(commands, ActionType::STOP), _isForward(forward) { }

std::string ActionDriveForever::getActionPrototype()
{
    std::stringstream ss;

    ss << _type << "::" << _isForward;
    return ss.str();
}

std::string ActionDriveForever::getString()
{
    return "Action drive forever";
}




