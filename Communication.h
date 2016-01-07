#pragma once

#include "Queue.h"
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

        std::thread createThread(Queue<Message> * sendQueue, Queue<Message> * receiveQueue, bool isMaster = false);
        void run(Queue<Message> * sendQueue, Queue<Message> * receiveQueue, bool isMaster = false);
    private:
        void receive();
        void send();
        
        bool _isMaster = false;
        Queue<Message> * _sendQueue;
        Queue<Message> * _receiveQueue;
        
        CommUtils _commUtils;
        
        unsigned int _socket;
        unsigned int _port = DEFAULT_PORT;
        
        unsigned int _lastIdReceived = 0;
    };
}


