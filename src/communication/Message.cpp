#include "Message.h"

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace ev3;

Message::Message()
: _sender(0), _receiver(0), _id(0), _type(EMPTY) { }

Message::Message(unsigned int senderId, unsigned int receiverId, unsigned int messageId, MessageType type, StringVector parameters)
: _sender(senderId), _receiver(receiverId), _id(messageId), _type(type), _parameters(parameters) { }

unsigned int Message::getSenderId()
{
    return _sender;
}

unsigned int Message::getMessageId()
{
    return _id;
}

unsigned int Message::getReceiverId()
{
    return _receiver;
}

StringVector Message::getParameters()
{
    return _parameters;
}

Message::MessageType Message::getType()
{
    return _type;
}

void Message::setMessageId(unsigned int id)
{
    _id = id;
}

void Message::setParameters(StringVector parameters)
{
    _parameters = parameters;
}

void Message::setReceiverId(unsigned int id)
{
    _receiver = id;
}

void Message::setSenderId(unsigned int id)
{
    _sender = id;
}

void Message::setType(MessageType type)
{
    _type = type;
}

bool Message::empty()
{
    return _type == EMPTY;
}

std::string Message::getString()
{
    std::stringstream ss;
    ss << "Sender: " << std::setw(7) << _sender << " | ";
    ss << "Receiver: " << std::setw(5) << _receiver << " | ";
    ss << "Msg. Id: " << std::setw(5) << _id << " | ";
    ss << "Type: " << std::setw(10) << getStringType() << " | ";
    ss << "Parameters: ";
    for (auto & s : _parameters)
        ss << s << " | ";

    return ss.str();
}

void Message::reset()
{
    _id = 0;
    _receiver = 0;
    _sender = 0;
    _type = EMPTY;
    _parameters.clear();
}

Message Message::decodeMessage(const std::string message)
{
    std::vector<std::string> parts;
    std::istringstream f(message);
    std::string s;
    while (std::getline(f, s, MESSAGE_DELIM))
    {
        parts.push_back(s);
    }

    std::vector<std::string> params;
    if (parts.size() >= 5)
        params = std::vector<std::string>(parts.begin() + 4, parts.end());

    if (parts.size() >= 4)
        return Message(std::stoi(parts[0]), std::stoi(parts[1]), std::stoi(parts[2]),
            static_cast<MessageType> (std::stoi(parts[3])), params);
    else
        return Message();
}

std::string Message::encodeMessage(Message& message)
{
    std::string msg = "";
    msg += std::to_string(message.getSenderId());
    msg += MESSAGE_DELIM;
    msg += std::to_string(message.getReceiverId());
    msg += MESSAGE_DELIM;
    msg += std::to_string(message.getMessageId());
    msg += MESSAGE_DELIM;
    msg += std::to_string(message.getType());
    msg += MESSAGE_DELIM;
    for (auto & s : message.getParameters())
        msg += s + MESSAGE_DELIM;

    return msg;
}

std::string Message::getStringType()
{
    switch (_type)
    {
        case ABORT:
            return "ABORT";
        case ACK:
            return "ACK";
        case ACTION_OK:
            return "ACTION_OK";
        case ACTION_INTERR:
            return "ACTION_INTERR";
        case AGENT:
            return "AGENT";
        case AGENT_OVER:
            return "AGENT_OVER";
        case BEHAVIOUR:
            return "BEHAVIOUR";
        case EMPTY:
            return "EMPTY";
        case MASTER:
            return "MASTER";
        case MASTER_OVER:
            return "MASTER_OVER";
        case MEASURE:
            return "MEASURE";
        case NOT:
            return "NOT";
        case PAUSE:
            return "PAUSE";
        case PING:
            return "PING";
        case PONG:
            return "PONG";
        case RESUME:
            return "RESUME";
        case SENSOR_VALUE:
            return "SENSOR_VALUE";
        case START:
            return "START";
        default:
            return "???";
    }
}



