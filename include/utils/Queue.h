#pragma once
#include "Message.h"

#include <queue>
#include <mutex>

namespace ev3
{
    /**
     * @class Queue
     * Template class implementing synchronized queue.
     * All method are guarded by mutex.
     */
    template<class T>
    class Queue
    {
    public:
        /**
         * Insert new object to the queue.
         * @param element Inserted object.
         */
        void push(T element);
        
        /**
         * Removes first object from the queue.
         * @return Copy of removed object.
         */
        T pop();
        
        /**
         * Check whether queue is empty.
         * @return True if queue is empty, false otherwise.
         */
        bool empty();

    private:
        /// The actual queue implemented as std::queue.
        std::queue<T> _elements;

        /// Synchronization mutex.
        std::mutex _mutex;
    };

    template<class T>
    void Queue<T>::push(T element)
    {
        std::lock_guard<std::mutex> guard(_mutex);
        _elements.push(element);
    }

    template<class T>
    T Queue<T>::pop()
    {
        std::lock_guard<std::mutex> guard(_mutex);
        if (_elements.empty())
            return T();

        T element = _elements.front();
        _elements.pop();

        return element;
    }

    template<class T>
    bool Queue<T>::empty()
    {
        std::lock_guard<std::mutex> guard(_mutex);
        return _elements.empty();
    }
}

