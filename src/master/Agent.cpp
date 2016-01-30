#include "Agent.h"

using namespace ev3;

unsigned int Agent::getId()
{
    return _id;
}

void Agent::setId(const unsigned int id)
{
    _id = id;
}

unsigned int Agent::getCommId()
{
    return _commId;
}

void Agent::setCommId(const unsigned int commId)
{
    _commId = commId;
}

void Agent::updateLastMessage(Message* message)
{
    _lastMessageType = message->getType();
}

void Agent::processMessage(Message * message, Message * retMessage)
{
    retMessage->reset();
    Message::MessageType type = message->getType();

    switch (_state)
    {
        case RobotState::IDLE:
            if (_lastMessageType == Message::MASTER && type == Message::ACK)
            {
                _state = RobotState::ACTIVE;
                retMessage->setType(Message::BEHAVIOUR);
                retMessage->setParameters(_currentBehaviour->getPrototype());
            }
            break;
        case RobotState::ACTIVE:
            if (_lastMessageType == Message::BEHAVIOUR)
            {
                if (type == Message::ACK)
                {
                    _state = RobotState::WORKING;
                    retMessage->setType(Message::START);
                }
            }
            break;
        case RobotState::WORKING:
            break;
        case RobotState::PAUSED:
            break;
        case RobotState::PANIC:
            break;
        default:
            break;
    }

    _commId = message->getMessageId();

    retMessage->setSenderId(MASTER_ID);
    retMessage->setReceiverId(_id);
    retMessage->setMessageId(_commId);
}

void Agent::setBehaviour(SharedPtrBehaviour behaviour)
{
    _currentBehaviour = behaviour;
}






