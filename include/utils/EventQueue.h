#pragma once

#include "Event.h"

#include <queue>
#include <mutex>

namespace ev3
{    
    class EventQueue
    {
    public:
        static EventQueue * getInstance();
        static void destroy();
        
        void push(Event message);
        Event pop();
        bool empty();
        unsigned int size();
        
    protected:
        EventQueue();
        EventQueue(const EventQueue &);
        EventQueue& operator=(const EventQueue&);
        ~EventQueue();
        
        static EventQueue * _instance;

        std::queue<Event> _queue;

        std::mutex _mutex;
    };
}


