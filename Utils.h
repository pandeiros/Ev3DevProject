#pragma once

namespace ev3
{
    static const float UNITS_PER_CENTIMETER = 10.f;

    static unsigned int COUNT_PER_ROT = 360;

    static float PULSES_PER_DEGREE = 1.0;

    static void updateCountPerRot(unsigned int cpr)
    {
        COUNT_PER_ROT = cpr;
        PULSES_PER_DEGREE = 360.f / cpr;
    }
}