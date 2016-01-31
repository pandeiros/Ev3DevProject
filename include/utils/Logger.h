#pragma once

#include <string>

namespace ev3
{

    class Logger
    {
    public:
        /*
         *
         */
        enum LogLevel {
            DEBUG = 1,
            VERBOSE = 1 << 1,
            INFO = 1 << 2,
            WARNING = 1 << 3,
            ERROR = 1 << 4
        };

        enum LogOutput {
            STD_OUT = 1,
            STD_ERR = 1 << 1,
            FILE = 1 << 2
        };

        static Logger * getInstance();
        static void destroy();

        void log(std::string message, LogLevel level, LogOutput output = STD_OUT);
        void setLogLevel(LogLevel level);
        void setLogLevel(std::string level);
        void setLogOutput(LogOutput output);

    private:
        Logger(); // Prevent construction
        Logger(const Logger&); // Prevent construction by copying
        Logger& operator=(const Logger&); // Prevent assignment
        ~Logger(); // Prevent unwanted destruction
        static Logger * _instance;

        LogLevel _level = ERROR;
        LogOutput _output;

        std::string getLabel(LogLevel level, LogOutput output);
        std::string getColor(LogLevel level, LogOutput output);
        
        bool _loggerForced = false;
    };
}
