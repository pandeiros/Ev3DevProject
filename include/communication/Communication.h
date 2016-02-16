#pragma once

#include "Queue.h"
#include "CommUtils.h"
#include <thread>

/**
 * @file Communication.h
 * Contains Communication class.
 */

namespace ev3
{
    /// Default maximum number of one time communication thread iterations.
    static const unsigned int MAX_COMM_ITERATIONS = 10;
    
    /// Default number of subsequent attempts to send a message.
    static const unsigned int SEND_RETRIES = 3;
    
    /**
     * @class Communication
     * Encapsulates low-level communication and adds logic concerning
     * sending and receiving Message queueing.
     */
    class Communication
    {
    public:
        /**
         * Default constructor.
         */
        Communication();

        /**
         * Thread creation method (insted of running Communication 
         * in the main thread).
         * @param sendQueue Out Message queue.
         * @param receiveQueue In Message queue.
         * @param isMaster True if queue is synchronized with master, false otherwise.
         * @return New std::thread object with Communication class active.
         */
        std::thread createThread(Queue<Message> * sendQueue, Queue<Message> * receiveQueue, bool isMaster = false);
        
        /**
         * Starts Communication procedures.
         * @param sendQueue Out Message queue.
         * @param receiveQueue In Message queue.
         * @param isMaster True if queue is synchronized with master, false otherwise.
         */
        void run(Queue<Message> * sendQueue, Queue<Message> * receiveQueue, bool isMaster = false);
        
    private:
        /**
         * Looped Message receiving.
         */
        void receive();
        
        /**
         * Looped Message sending.
         */
        void send();
        
        /// True if Communication is synchronized with master, false otherwise.
        bool _isMaster = false;
        
        /// Out Message queue.
        Queue<Message> * _sendQueue;
        
        /// In Message queue.
        Queue<Message> * _receiveQueue;
        
        /// Low-level object performing the actual sending/receiving.
        CommUtils _commUtils;
        
        /// Assigned socket id.
        unsigned int _socket;
        
        /// Chosen port number.
        unsigned int _port = DEFAULT_PORT;
    };
}


