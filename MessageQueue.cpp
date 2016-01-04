#include "MessageQueue.h"

using namespace ev3;

MessageQueue::MessageQueue()
{
//    pthread_mutex_init(_mutex, NULL);
}

MessageQueue::~MessageQueue()
{
//    pthread_mutex_destroy(_mutex);
}

void MessageQueue::push(Message message)
{
    std::lock_guard<std::mutex> guard(_mutex);
    _messages.push(message);
//    pthread_mutex_unlock(_mutex);
}

Message MessageQueue::pop()
{
    std::lock_guard<std::mutex> guard(_mutex);
    if (!_messages.size())
        return Message();
    
    Message msg = _messages.front();
    _messages.pop();
//    pthread_mutex_unlock(_mutex);

    return msg;
}


