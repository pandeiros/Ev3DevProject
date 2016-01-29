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
            VERBOSE = 1,
            INFO = 1 << 1,
            WARNING = 1 << 2,
            ERROR = 1 << 3
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
        void setLogOutput(LogOutput output);

    private:
        Logger(); // Prevent construction
        Logger(const Logger&); // Prevent construction by copying
        Logger& operator=(const Logger&); // Prevent assignment
        ~Logger(); // Prevent unwanted destruction
        static Logger * _instance;

        LogLevel _level;
        LogOutput _output;

//        void print(std::string & message, LogOutput output = STD_OUT);
        std::string getLabel(LogLevel level);
    };
}
