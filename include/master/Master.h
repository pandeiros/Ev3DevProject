#pragma once

#include "Queue.h"
#include "Agent.h"
#include "Behaviour.h"

#include <thread>
#include <map>

namespace ev3
{

    /**
     * @class Master
     * Controls the whole system and knows about every Agent.
     * Initiates Behaviour and receives values from sensor.
     */
    class Master
    {
    public:
        /// Type for mapping Agents to their ids.
        typedef std::map<unsigned int, Agent> AgentMap;

        /**
         * Creates thread instead of running Master in the main thread.
         * @param sendQueue Out Message queue.
         * @param receiveQueue In Message queue.
         * @return New std::thread object with active Master class.
         */
        std::thread createThread(Queue<Message> * sendQueue, Queue<Message> * receiveQueue);

        /**
         * Starts Master procedures
         * @param sendQueue
         * @param receiveQueue
         */
        void run(Queue<Message> * sendQueue, Queue<Message> * receiveQueue);

        /**
         * Sending method assigning id to the message.
         * @param message Message to be passed to Communication thread via sendQueue.
         * @param recordMessage True if information about 
         * message should be saved for further purposes, false otherwise.
         */
        void send(Message message, bool recordMessage = true);

        /**
         * Stop Master main loop and exit.
         */
        void stop();

    private:
        /// Map of all active Agents.
        AgentMap _agents;

        /// Out Message Queue.
        Queue<Message> * _sendQueue;
        
        /// In Message Queue.
        Queue<Message> * _receiveQueue;

        /// Currently active Behaviour for all Agents.
        SharedPtrBehaviour _currentBehaviour;

        /// Incremented variable used to assign ids to new Agents.
        unsigned int _agentId = MASTER_ID;

        /// Types of Sensors which values are interesting and must be gathered.
        Measurements _measurements;
    };
}

