#pragma once

#include "MessageQueue.h"
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
    };
}


