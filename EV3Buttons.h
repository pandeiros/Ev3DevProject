#pragma once

#include "ev3dev.h"
#include <iostream>

class EV3Buttons
{
public:

    enum BUTTON_CODE
    {
        BACK = 1,
        LEFT = 1 << 1,
        RIGHT = 1 << 2,
        UP = 1 << 3,
        DOWN = 1 << 4,
        ENTER = 1 << 5
    };

    static unsigned int getButtonCode();
};