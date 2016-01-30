#pragma once

#include "Robot.h"
#include "Master.h"
#include "Devices.h"
#include "Logger.h"

#include <iostream>

namespace ev3
{

    class SignalHandler
    {
    public:

        static void
        HandleSignal(int signum)
        {
            Logger::getInstance()->log("Signal caught: " + std::to_string(signum), 
                    ev3::Logger::WARNING);
            if (SignalHandler::robot)
                SignalHandler::robot->stop();
            if (SignalHandler::master)
                SignalHandler::master->stop();
            
            Devices::destroy();

            exit(signum);
        };

        static Robot * robot;
        static Master * master;
    };
}
