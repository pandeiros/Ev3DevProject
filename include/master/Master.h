#pragma once

#include "Queue.h"
#include "Agent.h"
#include <thread>
#include <map>

namespace ev3
{

    class Master
    {
    public:
        typedef std::map<unsigned int, Agent> AgentMap;

        std::thread createThread(Queue<Message> * sendQueue, Queue<Message> * receiveQueue);
        void run(Queue<Message> * sendQueue, Queue<Message> * receiveQueue);

        void stop();
    private:
        AgentMap _agents;
        
        Queue<Message> * _sendQueue;
        Queue<Message> * _receiveQueue;
        
        unsigned int _agentId = MASTER_ID;
    };
}

