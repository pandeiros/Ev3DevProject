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
         * Execute device specific command.
         */
        virtual void execute();
        
        /**
         * Return Command's name.
         * @return 
         */
        virtual std::string getString();
        
    protected:
        /// String containing Command's name.
        std::string _debugInfo = "";
    };
}
