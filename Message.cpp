#include "Message.h"

using namespace ev3;

Message::Message()
: _id(-1), _type(EMPTY) { }

Message::Message(unsigned int id, MessageType type, StringVector parameters)
: _id(id), _type(type), _parameters(parameters) { }


