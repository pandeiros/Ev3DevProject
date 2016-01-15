#pragma once

#include <queue>
#include <mutex>

namespace ev3
{
    template<class T>
    class SingletonQueue
    {
    public:
        static SingletonQueue * getInstance();
        static void destroy();
        
        void push(T message);
        T pop();
        bool empty();
        
    private:
        SingletonQueue();
        SingletonQueue(const SingletonQueue &);
        SingletonQueue& operator=(const SingletonQueue&);
        ~SingletonQueue();
        
        static SingletonQueue * _instance;

        std::queue<T> _queue;

        std::mutex _mutex;
    };
    
    template<class T>
    void SingletonQueue<T>::push(T element)
    {
        std::lock_guard<std::mutex> guard(_mutex);
        _queue.push(element);
    }

    template<class T>
    T SingletonQueue<T>::pop()
    {
        std::lock_guard<std::mutex> guard(_mutex);
        if (_queue.empty())
            return T();

        T msg = _queue.front();
        _queue.pop();

        return msg;
    }

    template<class T>
    bool SingletonQueue<T>::empty()
    {
        return _queue.empty();
    }
}


