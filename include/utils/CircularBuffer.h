#pragma once

#include <vector>
#include <algorithm>

namespace ev3
{
    /**
     * @class CircularBuffer
     * Template class for storing N objects of a particular class.
     * Replaces old objects if limit is exceeded.
     */
    template<class T>
    class CircularBuffer
    {
    public:
        /**
         * No default constructor.
         */
        CircularBuffer() = delete;
        
        /**
         * Constructor with limit parameter.
         * @param limit Positive integer defining upper buffer limit.
         */
        CircularBuffer(unsigned int limit);

        /**
         * Put object into the buffer. Replace old ones if limit is reached.
         * @param object Template object to be put into the buffer.
         */
        void push(T object);
        
        /**
         * Get information about certain object.
         * @param object Object to be found in buffer.
         * @return True if found, false otherwise.
         */
        bool contain(T object);

    private:
        /// The actual buffer implemented as a vector.
        std::vector<T> _buffer;
        
        /// Current insertion position.
        unsigned int _index = 0;
        
        /// Upper limit for the buffer.
        unsigned int _limit;
    };

    template<class T>
    CircularBuffer<T>::CircularBuffer(unsigned int limit)
    : _limit(limit), _buffer(std::vector<T>(limit)) { }

    template<class T>
    void CircularBuffer<T>::push(T object)
    {
        _buffer[_index++ % _limit] = object;
    }

    template<class T>
    bool CircularBuffer<T>::contain(T object)
    {
        return (std::find(_buffer.begin(), _buffer.end(), object) != _buffer.end());
    }
}



