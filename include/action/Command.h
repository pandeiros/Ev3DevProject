#pragma once
#include <functional>
#include <iostream>

#include "ev3dev.h"

namespace ev3
{

    class Command
    {
    public:
        Command();

        virtual void execute();
        virtual void printDebug();
    protected:
        std::string _debugInfo = "";

        //        ev3dev::device _device;
        //        std::function<void(ev3dev::device) > func;
    };

    //    class Command
}