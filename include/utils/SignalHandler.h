#pragma once

#include "Robot.h"
#include "Master.h"
#include "Devices.h"
#include "Logger.h"

#include <iostream>

namespace ev3
{

    /**
     * @class SignalHandler
     * Simple class catching system signals.
     * Stops Robot and Master if break signal is received.
     */
    class SignalHandler
    {
    public:
        /**
         * Main signal catching method.
         * @param signum Signal code to catch.
         */
        static void HandleSignal(int signum);

        /// Pointer to Robot instance.
        static Robot * robot;
        
        /// Pointer to Master instance.
        static Master * master;
    };
}
