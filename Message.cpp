#include "Message.h"

#include <string>
#include <sstream>
#include <iostream>

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

Message::StringVector Message::getParameters()
{
    return _parameters;
}

Message::MessageType Message::getType()
{
    return _type;
}

bool Message::empty()
{
    return _type == EMPTY;
}

Message Message::decodeMessage(const std::string msg)
{
    std::cout << "DECODED: " << msg << "\n";
    
    std::vector<std::string> parts;
    std::istringstream f(msg);
    std::string s;
    while (std::getline(f, s, MESSAGE_DELIM))
    {
//        std::cout << s << " ";
        parts.push_back(s);
    }

//    std::cout << "\n";

    std::vector<std::string> params;
    if (parts.size() >= 5)
        params = std::vector<std::string>(parts.begin() + 3, parts.end());

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
    
    std::cout << "ENCODED: " << msg << "\n";

    return msg;
}


