#include "Master.h"
#include "Logger.h"

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

    _currentBehaviour = std::make_shared<BehaviourExploreRandom>();
    _measurements = Measurements({Sensor::ULTRASONIC, Sensor::TOUCH});

    bool stop = false;

    Message retMessage;
    retMessage.reset();

    Message msg = receiveQueue->pop();
    while (true)
    {
        if (msg.getType() != Message::EMPTY)
            Logger::getInstance()->log(MASTER_RECEIVE + msg.getString(), Logger::VERBOSE);

        if (msg.getType() == Message::ABORT)
            break;

        if (msg.getType() == Message::AGENT)
        {
            Agent agent;
            unsigned int id = ++_agentId;
            agent.setId(id);
            agent.setCommId(msg.getMessageId());
            agent.setBehaviour(_currentBehaviour);
            agent.setMeasurement(_measurements);

            _agents.insert({id, agent});

            send(Message(MASTER_ID, id, agent.getCommId(), Message::MASTER, { }));
        }
        else if (msg.getType() == Message::PING)
        {
            unsigned int id = msg.getSenderId();
            if (_agents.find(id) != _agents.end())
            {
                if (_agents[id].getCommId() < msg.getMessageId())
                {

                    send(Message(MASTER_ID, id, msg.getMessageId(), Message::PONG, { }));
                    _agents[id].setCommId(msg.getMessageId());
                }
            }

        }
//        else if (_agents.find(msg.getSenderId()) != _agents.end())
//            _agents[msg.getSenderId()].processMessage(&msg, &retMessage);
        
        for (auto & agent : _agents)
            agent.second.processMessage(&msg, &retMessage);

        if (!retMessage.empty())
        {
            send(retMessage);
            retMessage.reset();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        if (!receiveQueue->empty() || msg.getType() != Message::EMPTY)
            msg = receiveQueue->pop();
    }

    Logger::getInstance()->log("Master finished.", Logger::INFO);

    return;
}

void Master::send(Message message, bool recordMessage)
{
    if (recordMessage)
        _agents[message.getReceiverId()].updateLastMessage(&message);

    Logger::getInstance()->log(MASTER_SEND + message.getString(), Logger::VERBOSE);

    _sendQueue->push(message);
}

void Master::stop()
{

    for (auto & agent : _agents)
        send(Message(MASTER_ID, agent.second.getId(), 0, Message::MASTER_OVER, { }), false);

    _receiveQueue->push(Message(0, 0, 0, Message::ABORT));
}
