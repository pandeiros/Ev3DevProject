#include "Communication.h"
#include <iostream>

using namespace ev3;

Communication::Communication() { }

std::thread Communication::createThread(MessageQueue* messageQueue)
{
    return std::thread([ = ]{run(messageQueue);});
}

void Communication::run(MessageQueue * messageQueue)
{
    this->_messageQueue = messageQueue;

    for (unsigned int i = 0; i < 2; ++i)
    {
        messageQueue->push(Message(i, Message::PING,{"Test", "Testing...."}));
        std::cout << "Push\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
    
    messageQueue->push(Message(0, Message::ABORT,{"Abort"}));
}

