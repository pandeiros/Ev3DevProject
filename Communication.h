#pragma once

#include "MessageQueue.h"
#include "CommUtils.h"
#include <thread>

namespace ev3
{
    static const unsigned int MAX_COMM_ITERATIONS = 10;
    static const unsigned int SEND_RETRIES = 3;

    class Communication
    {
    public:
        Communication();

        std::thread createThread(MessageQueue * sendQueue, MessageQueue * receiveQueue, bool isMaster = false);
        void run(MessageQueue * sendQueue, MessageQueue * receiveQueue, bool isMaster = false);
    private:
        void receive();
        void send();
        
        bool _isMaster = false;
        MessageQueue * _sendQueue;
        MessageQueue * _receiveQueue;
        
        CommUtils _commUtils;
        
        unsigned int _socket;
        unsigned int _port = DEFAULT_PORT;
        
        unsigned int _lastIdReceived = 0;
    };
}


