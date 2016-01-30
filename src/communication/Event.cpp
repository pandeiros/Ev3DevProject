#include "Event.h"

using namespace ev3;

Event::Event()
: _type(EMPTY) { }

Event::Event(EventType type)
: _type(type) { }

Event::EventType Event::getType()
{
    return _type;
}

