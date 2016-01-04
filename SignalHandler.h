#pragma once

#include "Robot.h"

namespace ev3
{

    class SignalHandler
    {
    public:

        static void
        HandleSignal(int signum)
        {
            std::cout << "SIGNAL CAUGHT " << signum << "\n";
            SignalHandler::robot->stop();

            exit(signum);
        };

        static Robot * robot;
    };
}