#pragma once

#include "Action.h"

#include <unistd.h>

namespace ev3
{

    class Behaviour
    {
    public:
        typedef std::vector<Action*> ActionsVector;

        Behaviour();
        Behaviour(ActionsVector actions);
        virtual ~Behaviour();

        virtual void execute()
        {
            for (auto * action : _actions)
            {
                std::cout << action->getActionPrototype() << "\n";
                action->execute();
                while (!action->isFinished())
                {
                };
            }
        }

    protected:
        ActionsVector _actions;
    };


}
