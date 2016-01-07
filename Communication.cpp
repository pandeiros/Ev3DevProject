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

    //    Message msg;
    //    CommUtils::NetworkNode sender;
    //
    //    if (_socket >= 0)
    //        //int result = _commUtils.receiveMessage(_socket, msg, sender);
    //        for (unsigned int i = 0; i < 10; ++i)
    //        {
    //            std::cout << "Broadcast...\n";
    //            _commUtils.sendBroadcastMessage(_socket, _port, Message(1, i, Message::PING,{"Test", "Testing...."}));
    //            std::this_thread::sleep_for(std::chrono::seconds(1));
    //        }

    //    for (unsigned int i = 0; i < 2; ++i)
    //    {
    //        messageQueue->push(Message(i, Message::PING,{"Test", "Testing...."}));
    //        std::cout << "Push\n";
    //        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    //    }
    //
    //_sendQueue->push(Message(1, 0, Message::ABORT,{"Abort"}));
}

void Communication::receive()
{
    Message msg;
    CommUtils::NetworkNode sender;
    std::string proto = "";
    std::string currentProto = "";

    unsigned int count = 0;
    while (_commUtils.receiveMessageDelay(_socket, msg, sender) && count++ < MAX_COMM_ITERATIONS)
    {
        //currentProto = Message::encodeMessage(msg);
        if (!msg.empty() && (_isMaster && msg.getReceiverId() == MASTER_ID || !_isMaster))
        {
            _sendQueue->push(msg);
        }
        else
            break;
        
        msg = Message();
        
//        currentProto = Message::encodeMessage(msg);
//        if (!msg.empty() && (_isMaster && msg.getReceiverId() == MASTER_ID || !_isMaster) &&
//            proto != currentProto)
//        {
//            _sendQueue->push(msg);
//            proto = currentProto
//        }
//        else
//            break;
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
        
        for (unsigned int i = 0; i < SEND_RETRIES; ++i)
        {
            if (_commUtils.sendMessage(_socket, _port, msg, _isMaster))
                break;
        }
    }
    //    Message msg;
    //    CommUtils::NetworkNode sender;
    //
    //    unsigned int count = 0;
    //    while (_commUtils.receiveMessageDelay(_socket, msg, sender) && count++ < MAX_RECEIVE_ITERATIONS)
    //    {
    //        if (msg.getType() != Message::EMPTY)
    //            _sendQueue.push(msg);
    //        else
    //            break;
    //    }F
}



