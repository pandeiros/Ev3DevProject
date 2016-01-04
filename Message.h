#pragma once

#include <vector>
#include <string>

namespace ev3
{

    class Message
    {
    public:

        typedef std::vector<std::string> StringVector;

        enum MessageType
        {
            EMPTY,
            ABORT,
            PING
        };

        Message();
        Message(unsigned int id, MessageType type, StringVector parameters);

        unsigned int getId();
        MessageType getType();
        StringVector getParameters();

    private:
        unsigned int _id;
        MessageType _type = EMPTY;
        StringVector _parameters;

    };
}

inline unsigned int ev3::Message::getId()
{
    return _id;
}

inline ev3::Message::StringVector ev3::Message::getParameters()
{
    return _parameters;
}

inline ev3::Message::MessageType ev3::Message::getType()
{
    return _type;
}

