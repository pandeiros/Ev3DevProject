#include "EventQueue.h"

using namespace ev3;

EventQueue * EventQueue::_instance = nullptr;

EventQueue * EventQueue::getInstance()
{
    if (!_instance)
        _instance = new EventQueue;
    return _instance;
}

void EventQueue::destroy()
{
    delete _instance;
    _instance = nullptr;
}

void EventQueue::push(Event element)
{
    std::lock_guard<std::mutex> guard(_mutex);
    _queue.push(element);
}

Event EventQueue::pop()
{
    std::lock_guard<std::mutex> guard(_mutex);
    if (_queue.empty())
        return Event();

    Event event = _queue.front();
    _queue.pop();

    return event;
}

bool EventQueue::empty()
{
    return _queue.empty();
}

unsigned int EventQueue::size()
{
    return _queue.size();
}

EventQueue::EventQueue() { }

EventQueue::~EventQueue() { }

