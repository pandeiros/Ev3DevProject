#pragma once
#include <functional>
#include <iostream>

#include "ev3dev.h"

namespace ev3
{

    /**
     * @class Command
     * Base class for all command controlling classes.
     * Each Command class encapsulates basic motor or sensor operation.
     */
    class Command
    {
    public:
        /**
         * Default constructor.
         */
        Command();

        /**
         * Execute stored function as a device command.
         */
        virtual void execute();

        virtual std::string getPrototype();
    protected:
        /// String containing Command's debug name.
        std::string _debugInfo = "";
    };
}
