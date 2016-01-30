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
        virtual SharedPtrBehaviour generateBehaviour(SharedPtrBehaviour & ptr, Behaviour::BehaviourType type, StringVector parameters) override;
        Action * generateAction(Action * action, Action::ActionType type);
        //        void generateEndConditions(SharedPtrAction action, Action::ActionType type);
        //        SharedPtrAction generateAction(SharedPtrAction action, Action::ActionType type, StringVector parameters);

        float _wheelRadius = 5.75 / 2.f;
    };
}

