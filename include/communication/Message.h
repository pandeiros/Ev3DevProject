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
            AGENT,
            MASTER,
            MASTER_OVER,
            PING,
            PONG,
            AGENT_OVER,
            ABORT,
            BEHAVIOUR
        };

        Message();
        Message(unsigned int senderId, unsigned int receiverId, unsigned int messageId, MessageType type, StringVector parameters = {});

        unsigned int getSenderId();
        unsigned int getReceiverId();
        unsigned int getMessageId();
        MessageType getType();
        StringVector getParameters();
        
        bool empty();
        void print();
        
        static std::string encodeMessage(Message & message);
        static Message decodeMessage(const std::string msg);

    private:
        unsigned int _id;
        unsigned int _sender;
        unsigned int _receiver;
        MessageType _type = EMPTY;
        StringVector _parameters;

    };
}