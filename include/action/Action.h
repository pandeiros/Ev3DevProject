#pragma once

#include "CommandMotor.h"

#include <memory>

namespace ev3
{
    class Action;

    typedef std::shared_ptr<Action> SharedPtrAction;
    typedef std::vector<SharedPtrAction> StoredActions;

    typedef std::shared_ptr<Command> SharedPtrCommand;

    /// Type for containing associated Command pointers.
    typedef std::vector<SharedPtrCommand> CommandsVector;

    /**
     * @class Action
     * Base class for all Action controlling classes.
     * Each Action contains of a sequence of many \link Command Commands\endlink and
     * all of them are executed immediately, one after another. Action is valid,
     * until specific Event occurs or its \link Action::_endCondition endCondition\endlink function returns true.
     *
     * Action objects are instantiated accordingly to Robot model that
     * uses them. Actions are predefined and cannot be dynamically created.
     */
    class Action
    {
    public:

        /**
         * Type of Action.
         * It directly points to derived class being used.
         * @see Robot::AvailableActions
         */
        enum ActionType
        {
            NOP, /**< No operation. */
            REPEAT, /**< Repeats execution of other \link Action Actions\endlink. */
            DRIVE_DISTANCE, /**< Power Motor to reach certain distance. */
            ROTATE, /**< Rotate Robot for given angle. */
            STOP /**< Stop all active motors. */
        };

        /// String for empty Action prototype.
        static const std::string EMPTY_PROTO;

        /// Type for lambda functions to store end of Action condition.
        typedef std::function<bool(void) > EndCondition;

        /**
         * Constructor with CommandsVector and ActionType parameters.
         * @param commands \link Command Commands\endlink stored within this Action.
         * @param type Type of Action used.
         */
        Action(CommandsVector commands, ActionType type);

        /**
         * Constructor with CommandsVector parameter.
         * Action \link Action::_type type\endlink is set to Action::NOP .
         * @param commands \link Command Commands\endlink stored within this Action.
         */
        Action(CommandsVector commands);

        /**
         * Constructor with ActionType parameter.
         * @param type Type of Action used.
         */
        Action(ActionType type);

        /**
         * Default destructor.
         */
        virtual ~Action();

        /**
         * Executes stored \link Command Commands\endlink in a sequence.
         */
        virtual void execute();

        /**
         * Check if Action condition is fullfilled.
         * @return Value returned from Action::_endCondition.
         */
        virtual bool isFinished();
        
        virtual bool isExecuted();

        /**
         * Generate std::string prototype for Action.
         * @return Encoded Action data into std::string.
         */
        virtual std::string getActionPrototype();

        /**
         * Set \link Command Commands\endlink to be executed.
         * @param commands CommandsVector with pointers to commands.
         */
        void setCommands(CommandsVector commands);

        /**
         * Set end condition for Action.
         * @param condition Lambda function returning bool value.
         */
        void setEndCondition(EndCondition condition);

        /**
         * Get current Action type.
         * @return ActionType value.
         */
        ActionType getType();

    protected:
        /// Action type.
        ActionType _type;

        /// Vector of \link Command Commands\endlink.
        CommandsVector _commands;

        /// Lambda function defining Action end condition.
        EndCondition _endCondition = []()
        {
            return true;
        };
        
        bool _isExecuted = false;

        //TODO supported events
    };

    class ActionRepeat : public Action
    {
    public:
        ActionRepeat(StoredActions actions, unsigned int n);
        virtual void execute();

        //void setRepeatCondition(EndCondition condition);

    private:
        StoredActions _actions;
        unsigned int _n;
        unsigned int _currentIteration = 0;
        unsigned int _currentAction = 0;

//        EndCondition _repeatCondition = []()
//        {
//            return true;
//        };
    };

    class ActionDriveDistance : public Action
    {
    public:
        ActionDriveDistance(int distance);
        ActionDriveDistance(CommandsVector commands, int distance);

        int getDistance();

        virtual std::string getActionPrototype();

    private:
        int _distance;
    };

    class ActionRotate : public Action
    {
    public:
        ActionRotate(int rotation);
        ActionRotate(CommandsVector commands, int rotation);

        int getRotation();

        virtual std::string getActionPrototype();

    private:
        int _rotation;
    };
}
