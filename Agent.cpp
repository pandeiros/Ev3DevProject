#include "Agent.h"

using namespace ev3;

unsigned int Agent::getId()
{
    return _id;
}

void Agent::setId(const unsigned int id)
{
    _id = id;
}

unsigned int Agent::getCommId()
{
    return _commId;
}

void Agent::setCommId(const unsigned int commId)
{
    _commId = commId;
}




