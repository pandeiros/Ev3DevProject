#include "Logger.h"

#include <iostream>

using namespace ev3;

Logger * Logger::_instance = nullptr;

Logger* Logger::getInstance()
{
    if (!_instance)
        _instance = new Logger;
    return _instance;
}

void Logger::destroy()
{
    delete _instance;
    _instance = nullptr;
}

void Logger::log(std::string message, LogLevel level, LogOutput output) {
    if (level >= _level)
    {
        switch (output)
        {
            case STD_OUT:
                std::cout << getLabel(level) << " " << message << "\n";
                break;
            default:
                break;
        }
    }
}

std::string Logger::getLabel(LogLevel level) {
    std::string label = "[";
    switch (level)
    {
        case VERBOSE:
            label += "VERBOSE";
            break;
        default:
            label += "VERBOSE";
    }
    
    label += "]";
    return label;
 }



Logger::Logger() { }

Logger::~Logger() { }


