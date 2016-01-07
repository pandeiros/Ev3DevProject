#pragma once

#include "Robot.h"

namespace ev3
{

    class RobotModelA : public Robot
    {
    public:
        RobotModelA();
        virtual ~RobotModelA();
    private:
        float _wheelRadius = 5.75 / 2.f;

    };
}

