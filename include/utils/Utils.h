#pragma once

#include <chrono>
#include <vector>
#include <string>
#include <memory>
#include <sstream>
#include <iostream>

namespace ev3
{
    typedef std::chrono::high_resolution_clock HighResClock;
    typedef std::chrono::duration<double, std::milli> DurationMilli;
    typedef std::vector<std::string> StringVector;
    typedef std::vector<std::pair<int, int> > SensorValue;
    
    static const std::string MODE_MASTER = "master";
    static const std::string MODE_AGENT = "agent";

    static const std::string ERR_WRONG_NO_OF_ARGS = "Invalid number of parameters.\n";
    static const std::string ERR_WRONG_MODE = "Invalid mode given.\n";
    static const std::string ERR_WRONG_LOG_LEVEL = "Invalid log level given.\n";
    static const std::string ERR_WRONG_ARGUMENTS = "Wrong arguments!\n";
    
    static const std::string AGENT_SEND         = " [A] >>> ... ";
    static const std::string AGENT_RECEIVE      = " ... <<< [M] ";
    static const std::string MASTER_SEND        = " [M] >>> ... ";
    static const std::string MASTER_RECEIVE     = " ... <<< [A] ";

    static const float UNITS_PER_CENTIMETER = 10.f;

    static unsigned int COUNT_PER_ROT = 360;

    static float PULSES_PER_DEGREE = 1.0;

    static void updateCountPerRot(unsigned int cpr)
    {
        COUNT_PER_ROT = cpr;
        PULSES_PER_DEGREE = 360.f / cpr;
    }

    template<typename T>
    static T transcode(std::string parameter)
    {
        T value;
        std::stringstream ss;
        ss.str(parameter);

        ss >> value;

        return value;
    }
}
