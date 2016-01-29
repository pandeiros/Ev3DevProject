#include "Communication.h"

#include <iostream>

using namespace ev3;

Communication::Communication() { }

std::thread Communication::createThread(Queue<Message> * sendQueue, Queue<Message> * receiveQueue, bool isMaster)
{
    return std::thread([ = ]{run(sendQueue, receiveQueue, isMaster);});
}

void Communication::run(Queue<Message> * sendQueue, Queue<Message> * receiveQueue, bool isMaster)
{
    _sendQueue = sendQueue;
    _receiveQueue = receiveQueue;
    _isMaster = isMaster;

    _socket = _commUtils.preparePassiveSocket(_port);

    bool stop = false;

    while (!stop)
    {
        receive();
        send();
    }
}

void Communication::receive()
{
    Message msg;
    CommUtils::NetworkNode sender;

    unsigned int count = 0;
    while (_commUtils.receiveMessageDelay(_socket, msg, sender) && count++ < MAX_COMM_ITERATIONS)
    {
        if (!msg.empty() && (_isMaster && msg.getReceiverId() == MASTER_ID || !_isMaster))
        {
            _sendQueue->push(msg);
        }
        else
            break;
        
        msg = Message();
    }
}

void Communication::send()
{
    unsigned int count = 0;
    while (!_receiveQueue->empty() && count++ < MAX_COMM_ITERATIONS)
    {
        Message msg = _receiveQueue->pop();

        if (msg.empty())
            continue;
        
        std::string messageStr = Message::encodeMessage(msg);
        for (unsigned int i = 0; i < SEND_RETRIES; ++i)
        {
            if (_commUtils.sendMessage(_socket, _port, msg, messageStr, _isMaster))
                break;
        }
    }
}



