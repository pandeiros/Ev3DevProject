#pragma once

#include "Event.h"

#include <queue>
#include <mutex>

/**
 * @file EventQueue.h
 * Contains EventQueue class.
 */

namespace ev3
{    
    /// Type for Event shared_ptr.
    typedef std::shared_ptr<Event> SharedPtrEvent;
    
    /**
     * @class EventQueue
     * Singleton class responsible for managing Event objects.
     * Instance is shared between many classes and threads.
     */
    class EventQueue
    {
    public:
        /**
         * Instance getter.
         * @return Create previously or new instance of class EventQueue.
         */
        static EventQueue * getInstance();
        
        /**
         * Deallocate instance.
         */
        static void destroy();
        
        /**
         * Insert new Event object to the queue.
         * @param event Event object to be inserted. 
         */
        void push(SharedPtrEvent event);
        
        /**
         * Removes first object from the queue.
         * @return Copy of removed object.
         */
        SharedPtrEvent pop();
        
        /**
         * Check whether queue is empty.
         * @return True if queue is empty, false otherwise.
         */
        bool empty();
        
        /**
         * Queue size getter.
         * @return Number of elements stored in queue.
         */
        unsigned int size();
        
    protected:
        /**
         * Default protected constructor (preventing object construction).
         */
        EventQueue();
        
        /**
         * Default protected copy constructor (preventing object construction by copying).
         * @param other Other EventQueue object.
         */
        EventQueue(const EventQueue & other);
        
        /**
         * Protected assignment operator (preventing object assignment).
         * @param other Other EventQueue object.
         * @return Copy of passed object.
         */
        EventQueue& operator=(const EventQueue& other);
        
        /**
         * Default protected destructor (preventing object unwanted destruction).
         */
        ~EventQueue();
        
        /// Instance of EventQueue singleton class.
        static EventQueue * _instance;

        /// The actual queue implemented as std::queue.
        std::queue<SharedPtrEvent> _queue;
        
        /// Synchronization mutex.
        std::mutex _mutex;
    };
}


