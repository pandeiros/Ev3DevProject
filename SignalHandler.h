#pragma once

#include "Robot.h"
#include "Master.h"

namespace ev3
{

    class SignalHandler
    {
    public:

        static void
        HandleSignal(int signum)
        {
            std::cout << "SIGNAL CAUGHT " << signum << "\n";
            if (SignalHandler::robot)
                SignalHandler::robot->stop();
            if (SignalHandler::master)
                SignalHandler::master->stop();

            exit(signum);
        };

        static Robot * robot;
        static Master * master;
    };
}