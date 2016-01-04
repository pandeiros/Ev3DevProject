#pragma once

#include "Message.h"

#include <queue>
//#include <thread>
#include <mutex>

namespace ev3
{

    class MessageQueue
    {
    public:
        MessageQueue();
        virtual ~MessageQueue();

        void push(Message message);
        Message pop();

    private:
        std::queue<Message> _messages;

        std::mutex _mutex;
    };
}


