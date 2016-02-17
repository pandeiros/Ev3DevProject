#pragma once

#include "Robot.h"

namespace ev3
{
    /**
     * @class RobotModelA 
     * Describes particular Robot construction and its way
     * of implementing actions and running behaviours.
     */
    class RobotModelA : public Robot
    {
    public:
        /**
         * Default constructor.
         */
        RobotModelA();
        
        /**
         * Human-readable name getter.
         * @return String with Robot model name.
         */
        virtual std::string getString() override;

    private:
        /**
         * Overrides Robot method of Behaviour creation.
         */
        virtual SharedPtrBehaviour generateBehaviour(Behaviour::BehaviourType type, StringVector parameters) override;
        
        /**
         * Generate Action based on its type.
         * @param action Shared pointer object with Action to be constructed.
         * @param type Action type.
         * @return Copy of the Action object with new data.
         */
        SharedPtrAction generateAction(SharedPtrAction action, Action::ActionType type);
       
        /// This model's wheel radius.
        float _wheelRadius = 5.75 / 2.f;
    };
}

