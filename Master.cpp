#include "Master.h"

//#include <future>
//#include <functional>
//#include <unistd.h>
#include <iostream>

using namespace ev3;

std::thread Master::createThread(Queue<Message> * sendQueue, Queue<Message> * receiveQueue)
{
    return std::thread([ = ]{run(sendQueue, receiveQueue);});
}

void Master::run(Queue<Message> * sendQueue, Queue<Message> * receiveQueue)
{
    _sendQueue = sendQueue;
    _receiveQueue = receiveQueue;

    bool stop = false;

    Message msg = receiveQueue->pop();
    while (!stop)
    {
        if (msg.getType() == Message::ABORT)
            break;
        
        if (msg.empty())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            if (!receiveQueue->empty())
                msg = receiveQueue->pop();
            continue;
        }
        
        if (msg.getType() == Message::AGENT)
        {            
            Agent agent;
            unsigned int id = ++_agentId;
            agent.setId(id);
            agent.setCommId(msg.getMessageId());
            
            _agents.insert({id, agent});
            
            _sendQueue->push(Message(MASTER_ID, id, agent.getCommId(), Message::MASTER, {}));
        }
        
        if (msg.getType() == Message::PING)
        {
            unsigned int id = msg.getSenderId();
            if (_agents.find(id) != _agents.end())
            {
                if (_agents[id].getCommId() < msg.getMessageId())
                {
                    _sendQueue->push(Message(MASTER_ID, id, msg.getMessageId(), Message::PONG, {}));
                    _agents[id].setCommId(msg.getMessageId());
                }
            }
            
        }
        
        if (_agentId == MASTER_ID + 3)
            break;

        //parseMessage(msg);

//        std::cout << msg.getMessageId() << " : ";
//        for (auto & s : msg.getParameters())
//            std::cout << s << " ";
//        std::cout << "\n";

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        msg = receiveQueue->pop();
    }

//    std::cout << msg.getMessageId() << " : ";
//    for (auto & s : msg.getParameters())
//        std::cout << s << " ";
//    std::cout << "\n";

    return;
}

void Master::stop()
{

    for (auto & agent : _agents)
        _sendQueue->push(Message(MASTER_ID, agent.second.getId(), 0, Message::MASTER_OVER, { }));
        
    _receiveQueue->push(Message(0,0,0,Message::ABORT));
}
