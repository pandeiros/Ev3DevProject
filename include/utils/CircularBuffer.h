#pragma once

#include <vector>
#include <algorithm>

namespace ev3
{

    template<class T>
    class CircularBuffer
    {
    public:
        CircularBuffer() = delete;
        CircularBuffer(unsigned int limit);

        void push(T object);
        bool contain(T object);

    private:
        std::vector<T> _buffer;
        unsigned int _index = 0;
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



