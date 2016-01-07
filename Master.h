#pragma once

#include "MessageQueue.h"
#include "Agent.h"
#include <thread>
#include <map>

namespace ev3
{

    class Master
    {
    public:
        typedef std::map<unsigned int, Agent> AgentMap;

        std::thread createThread(MessageQueue * sendQueue, MessageQueue * receiveQueue);
        void run(MessageQueue * sendQueue, MessageQueue * receiveQueue);

        void stop();
    private:
        AgentMap _agents;
        
        MessageQueue * _sendQueue;
        MessageQueue * _receiveQueue;
        
        unsigned int _agentId = MASTER_ID;
    };
}

