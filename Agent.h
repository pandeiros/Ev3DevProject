#pragma once

#include "CommUtils.h"

namespace ev3
{

    class Agent
    {
    public:
        unsigned int getId();
        void setId(const unsigned int id);

        unsigned int getCommId();
        void setCommId(const unsigned int commId);

    private:
        unsigned int _id;
        unsigned int _commId = 0;
    };
}