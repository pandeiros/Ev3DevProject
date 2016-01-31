#pragma once

#include "Event.h"

#include <queue>
#include <mutex>

namespace ev3
{    
    typedef std::shared_ptr<Event> SharedPtrEvent;
    
    class EventQueue
    {
    public:
        static EventQueue * getInstance();
        static void destroy();
        
        void push(SharedPtrEvent message);
        SharedPtrEvent pop();
        bool empty();
        unsigned int size();
        
    protected:
        EventQueue();
        EventQueue(const EventQueue &);
        EventQueue& operator=(const EventQueue&);
        ~EventQueue();
        
        static EventQueue * _instance;

        std::queue<SharedPtrEvent> _queue;

        std::mutex _mutex;
    };
}


