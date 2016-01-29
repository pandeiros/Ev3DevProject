#pragma once

#include "CommUtils.h"
#include "RobotState.h"
#include "Message.h"

namespace ev3
{

    class Agent
    {
    public:
        unsigned int getId();
        void setId(const unsigned int id);

        unsigned int getCommId();
        void setCommId(const unsigned int commId);
        
        void processMessage(Message * message, Message * retMessage);
        
        void updateLastMessage(Message * message);
        
    private:
        RobotState::States _state = RobotState::IDLE;
        unsigned int _id;
        unsigned int _commId = 0;
        
        Message::MessageType _lastMessageType;
    };
}