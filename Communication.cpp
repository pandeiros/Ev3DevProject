#include "Communication.h"

#include <iostream>

using namespace ev3;

Communication::Communication() { }

std::thread Communication::createThread(MessageQueue * sendQueue, MessageQueue * receiveQueue)
{
    return std::thread([ = ]{run(sendQueue, receiveQueue);});
}

void Communication::run(MessageQueue * sendQueue, MessageQueue * receiveQueue)
{
    _sendQueue = sendQueue;
    _receiveQueue = receiveQueue;

    _socket = _commUtils.preparePassiveSocket(_port);
    
    Message msg;
    CommUtils::Sender sender;

    if (_socket >= 0)
        //int result = _commUtils.receiveMessage(_socket, msg, sender);
        for (unsigned int i = 0; i < 10; ++i)
        {
            std::cout << "Broadcast...\n";
            _commUtils.sendBroadcastMessage(_socket, _port, Message(i, Message::PING,{"Test", "Testing...."}));
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

    //    for (unsigned int i = 0; i < 2; ++i)
    //    {
    //        messageQueue->push(Message(i, Message::PING,{"Test", "Testing...."}));
    //        std::cout << "Push\n";
    //        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    //    }
    //
    _sendQueue->push(Message(0, Message::ABORT,{"Abort"}));
}

