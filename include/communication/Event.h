#pragma once

namespace ev3
{

    class Event
    {
    public:
        enum EventType {
            EMPTY,
            BEHAVIOUR_START
        };
        
        Event();
        Event(EventType type);
        
        EventType getType();

    private:
        EventType _type;
    };
}

