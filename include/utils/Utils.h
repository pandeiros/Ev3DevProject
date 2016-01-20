#pragma once

#include <chrono>

namespace ev3
{
    typedef std::chrono::high_resolution_clock HighResClock;
    typedef std::chrono::duration<double, std::milli> DurationMilli;
//    std::chrono::high_resolution_clock
    
    static const std::string MODE_MASTER = "master";
    static const std::string MODE_AGENT = "robot";
    
    static const std::string ERR_WRONG_NO_OF_ARGS = "Invalid number of parameters.\n";
    static const std::string ERR_WRONG_MODE = "Invalid mode given.\n";
    
    static const float UNITS_PER_CENTIMETER = 10.f;

    static unsigned int COUNT_PER_ROT = 360;

    static float PULSES_PER_DEGREE = 1.0;

    static void updateCountPerRot(unsigned int cpr)
    {
        COUNT_PER_ROT = cpr;
        PULSES_PER_DEGREE = 360.f / cpr;
    }
}