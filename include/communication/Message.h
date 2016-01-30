#pragma once

#include "Utils.h"

#include <vector>
#include <string>

namespace ev3
{
    static const char MESSAGE_DELIM = ':';

    class Message
    {
    public:

        enum MessageType
        {
            EMPTY,
            ACK,
            NOT,
            AGENT,
            MASTER,
            MASTER_OVER,
            PING,
            PONG,
            AGENT_OVER,
            ABORT,
            BEHAVIOUR,
            START,
            RESUME,
            PAUSE,
            SENSOR_VALUE
        };

        Message();
        Message(unsigned int senderId, unsigned int receiverId, unsigned int messageId, MessageType type, StringVector parameters = {});

        unsigned int getSenderId();
        unsigned int getReceiverId();
        unsigned int getMessageId();
        MessageType getType();
        StringVector getParameters();

        void setSenderId(unsigned int id);
        void setReceiverId(unsigned int id);
        void setMessageId(unsigned int id);
        void setType(MessageType type);
        void setParameters(StringVector parameters);

        bool empty();
        std::string getString();

        static std::string encodeMessage(Message & message);
        static Message decodeMessage(const std::string msg);

        void reset();

    private:
        std::string getStringType();
        
        unsigned int _id;
        unsigned int _sender;
        unsigned int _receiver;
        MessageType _type = EMPTY;
        StringVector _parameters;

    };
}
