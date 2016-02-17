#pragma once

#include <string>

namespace ev3
{

    /**
     * @class Logger
     * Singleton class responsible for displaying information about 
     * events, messages, exceptions and executed methods.
     */
    class Logger
    {
    public:
        /**
         * Default logging complexity.
         * For a particular level, everything above will be printed as well.
         */
        enum LogLevel {
            DEBUG = 1,          /**< Print objects and methods information. */
            VERBOSE = 1 << 1,   /**< Print communication and states specifics. */
            INFO = 1 << 2,      /**< Print information for the user. */
            WARNING = 1 << 3,   /**< Print all warnings. */
            ERROR = 1 << 4      /**< Print all errors. */
        };

        /**
         * Desired logging output.
         */
        enum LogOutput {
            STD_OUT = 1,        /**< Standard output. */
            STD_ERR = 1 << 1,   /**< Standard error output. */
            FILE = 1 << 2       /**< File output. */
        };
        
        /**
         * Instance getter.
         * @return Create previously or new instance of class Logger.
         */
        static Logger * getInstance();
        
        /**
         * Deallocate instance.
         */
        static void destroy();

        /**
         * Print message to a specified output.
         * @param message String containing message.
         * @param level Logging level (used to choose color for the level label).
         * @param output Type of output to be used,
         */
        void log(std::string message, LogLevel level, LogOutput output = STD_OUT);
        
        /**
         * Logger level setter.
         * @param level LogLevel enum value.
         */
        void setLogLevel(LogLevel level);
        
        /**
         * Logger level setter by name.
         * @param level String with name of the level.
         */
        void setLogLevel(std::string level);
        
        /**
         * Logger output setter.
         * @param output Type of output to be used as default.
         */
        void setLogOutput(LogOutput output);

    private:
        /**
         * Default protected constructor (preventing object construction).
         */
        Logger();
        
        /**
         * Default protected copy constructor (preventing object construction by copying).
         * @param other Other Logger object.
         */
        Logger(const Logger& other);
        
        /**
         * Protected assignment operator (preventing object assignment).
         * @param other Other Logger object.
         * @return Copy of passed object.
         */
        Logger& operator=(const Logger& other);
        
        /**
         * Default protected destructor (preventing object unwanted destruction).
         */
        ~Logger();
        
        /**
         * Get level label.
         * @param level Logging level to get label for.
         * @param output Desired message output.
         * @return String with formatted label.
         */
        std::string getLabel(LogLevel level, LogOutput output);
        
        /**
         * Get color for logging level.
         * @param level Logging level to get color for.
         * @param output Logging output to match color on.
         * @return String with color code.
         */
        std::string getColor(LogLevel level, LogOutput output);
        
        /// Instance of Logger singleton class.
        static Logger * _instance;

        /// Current Logger level.
        LogLevel _level = ERROR;
        
        /// Current Logger output.
        LogOutput _output;

        /// Control flag. Checked when device should not 
        /// produce any Logger output.
        bool _loggerForced = false;
    };
}
