#pragma once

#include "Robot.h"

//#include <memory>

namespace ev3
{

    class RobotModelA : public Robot
    {
    public:
        RobotModelA();

    private:
        SharedPtrBehaviour generateBehaviour(Behaviour::BehaviourType type, StringVector & parameters);
        SharedPtrAction generateAction(SharedPtrAction action, Action::ActionType type);
        //        void generateEndConditions(SharedPtrAction action, Action::ActionType type);
        //        SharedPtrAction generateAction(SharedPtrAction action, Action::ActionType type, StringVector parameters);

        float _wheelRadius = 5.75 / 2.f;
    };
}

