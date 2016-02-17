#include "Logger.h"
#include "ColorUtils.h"

#include <iostream>
#include <exception>
#include <ctime>
#include <sstream>

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

void Logger::setLogLevel(LogLevel level)
{
    _level = level;
}

void Logger::setLogLevel(std::string level)
{
    if (level == "debug")
        setLogLevel(DEBUG);
    else if (level == "verbose")
        setLogLevel(VERBOSE);
    else if (level == "info")
        setLogLevel(INFO);
    else if (level == "warning")
        setLogLevel(WARNING);
    else if (level == "error")
        setLogLevel(ERROR);
    else
        throw std::exception();
}

void Logger::setLogOutput(LogOutput output)
{
    _output = output;
    if (output == STD_ERR || output == STD_OUT)
        _loggerForced = true;
}

void Logger::log(std::string message, LogLevel level, LogOutput output)
{
    // TODO Add timestamp.
    //    time_t currentTime;
    //    struct tm *localTime;
    //
    //    time(&currentTime); // Get the current time
    //    localTime = localtime(&currentTime); // Convert the current time to the local time
    //
    //    int Hour = localTime->tm_hour;
    //    int Min = localTime->tm_min;
    //    int Sec = localTime->tm_sec;
    //
    //    std::stringstream ss;
    //    ss << "[" << Hour << ":" << Min << ":" << Sec << "]";

    if (level >= _level)
    {
        switch (output)
        {
            case STD_OUT:
#ifdef __AGENT
                if (_loggerForced)
#endif
                    std::cout << getColor(level, output) <<
                    getLabel(level, output) <<
                    " " << message << "\n";
                break;

            case STD_ERR:
#ifdef __AGENT
                if (_loggerForced)
#endif
                    std::cerr << getColor(level, output) <<
                    getLabel(level, output) <<
                    " " << message << "\n";
                break;
            default:
                break;
        }
    }
}

std::string Logger::getLabel(LogLevel level, LogOutput output)
{
    std::string label = "[";
    switch (level)
    {
        case DEBUG:
            label += " DEBUG ";
            break;
        case VERBOSE:
            label += "VERBOSE";
            break;
        case INFO:
            label += " INFO  ";
            break;
        case WARNING:
            label += "WARNING";
            break;
        case ERROR:
            label += " ERROR ";
            break;
        default:
            label += "       ";
    }

    label += "]";
    if (output != FILE)
        label += ColorUtils::RESET;

    return label;
}

std::string Logger::getColor(LogLevel level, LogOutput output)
{
    if (output == FILE)
        return "";

    std::string label = "";
    switch (level)
    {
        case DEBUG:
            label = ColorUtils::BLUE;
            break;
        case VERBOSE:
            label = ColorUtils::WHITE_FAINT;
            break;
        case INFO:
            label = ColorUtils::GREEN;
            break;
        case WARNING:
            label = ColorUtils::YELLOW_BOLD;
            break;
        case ERROR:
            label = ColorUtils::RED_BOLD;
            break;
        default:
            label = "       ";
    }

    return label;
}

Logger::Logger() { }

Logger::~Logger() { }


