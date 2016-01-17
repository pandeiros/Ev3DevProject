#pragma once
#include "Message.h"

#include <queue>
#include <mutex>

namespace ev3
{
    template<class T>
    class Queue
    {
    public:
        void push(T message);
        T pop();
        bool empty();

    private:
        std::queue<T> _messages;

        std::mutex _mutex;
    };

    template<class T>
    void Queue<T>::push(T message)
    {
        std::lock_guard<std::mutex> guard(_mutex);
        _messages.push(message);

        message.print();
        //    pthread_mutex_unlock(_mutex);
    }

    template<class T>
    T Queue<T>::pop()
    {
        std::lock_guard<std::mutex> guard(_mutex);
        if (_messages.empty())
            return T();

        T msg = _messages.front();
        _messages.pop();
        //    pthread_mutex_unlock(_mutex);

        return msg;
    }

    template<class T>
    bool Queue<T>::empty()
    {
        return _messages.empty();
    }
}

