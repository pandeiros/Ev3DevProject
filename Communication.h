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

        std::thread createThread(MessageQueue * messageQueue);
        void run(MessageQueue * messageQueue);
    private:
        MessageQueue * _messageQueue;
        CommUtils _commUtils;
        
        unsigned int _socket;
        unsigned int _port = DEFAULT_PORT;
       
    };
}


