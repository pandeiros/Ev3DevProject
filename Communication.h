#pragma once

#include "MessageQueue.h"
#include "CommUtils.h"
#include <thread>

namespace ev3
{

    class Communication
    {
    public:
        Communication();

        std::thread createThread(MessageQueue * sendQueue, MessageQueue * receiveQueue);
        void run(MessageQueue * sendQueue, MessageQueue * receiveQueue);
    private:
        MessageQueue * _sendQueue;
        MessageQueue * _receiveQueue;
        
        CommUtils _commUtils;
        
        unsigned int _socket;
        unsigned int _port = DEFAULT_PORT;
       
    };
}


