#pragma once

#include "CommandMotor.h"
#include <memory>

/**
 * @file Action.h
 * Contains all Action classes.
 */

namespace ev3
{
    class Action;

    /// Type for Action shared_ptr.
    typedef std::shared_ptr<Action> SharedPtrAction;
    
    /// Type for storing many Actions in one container.
    /// @see ActionRepeat
    typedef std::vector<SharedPtrAction> StoredActions;
    
    /// Type for Command shared_ptr.
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
            ROTATE_RANDOM_DIR, /**< Rotate for given angle, clockwise or counterclockwise at random. */
            STOP, /**< Stop all active motors. */
            DRIVE_FOREVER /**< Drive forward or backward infinetely. */
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

        /**
         * Check if action was executed.
         * @return True if actcion was already executed, false otherwise.
         */
        virtual bool isExecuted();

        /**
         * Generate std::string prototype for Action.
         * @return Encoded Action data into std::string.
         */
        virtual std::string getActionPrototype();

        /**
         * Get human-readable Action name.
         * @return String containing Action name.
         */
        virtual std::string getString();

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

        /// True if action is already executed, false otherwise.
        bool _isExecuted = false;
    };

    /**
     * @class ActionRepeat
     * 
     * Stores many Actions in a vector and executes them in loop.
     * Number of iterations is given and may be infinite.
     */
    class ActionRepeat : public Action
    {
    public:
        /**
         * Constructor with StoredActions and iterations parameters.
         * @param actions Vector of Actions to be executed in a loop.
         * @param n Number of iterations. If 0 is given, loop will be infinite.
         */
        ActionRepeat(StoredActions actions, unsigned int n);
        
        /**
         * Continue with executing stored Actions.
         */
        virtual void execute();

        /**
         * Return human-readable ActionRepeat name.
         * @return String containing Action name.
         */
        virtual std::string getString();

    private:
        /// Vector of stored Actions to be executed.
        StoredActions _actions;
        
        /// Number of iterations.
        unsigned int _n;
        
        /// Keeps track of iterations already passed.
        unsigned int _currentIteration = 0;
        
        /// Keeps track of which Action is currently in progress.
        unsigned int _currentAction = 0;
    };

    /**
     * @class ActionDriveDistance
     * 
     * Implements Robot simple task to drive straight for a
     * given distance.
     */
    class ActionDriveDistance : public Action
    {
    public:
        /**
         * Constructor with distance parameter.
         * @param distance Integer value in Robot units to be driven.
         */
        ActionDriveDistance(int distance);
        
        /**
         * Constructor with CommandsVector and distance parameters.
         * @param commands Sequence of commands to be executed.
         * @param distance Integer value in Robot units to be driven.
         */
        ActionDriveDistance(CommandsVector commands, int distance);

        /**
         * Get distance the Robot has to drive.
         * @return Integer value in Robot units.
         */
        int getDistance();

        /**
         * Get ActionDriveDistance encoded name and its parameters.
         * @return String with encoded name and parameters.
         */
        virtual std::string getActionPrototype();

        /**
         * Get ActionDriveDistance human-readable name.
         * @return String with name and parameters
         */
        virtual std::string getString() override;

    private:
        /// Distance for the robot to drive in units.
        int _distance;
    };

    /**
     * @class ActionRotate
     * 
     * Implements Robot simple task to rotate a given angle,
     * while not driving. Rotation is made in place. 
     */
    class ActionRotate : public Action
    {
    public:
        /**
         * Constructor with rotation parameter in degrees.
         * @param rotation Number of degrees to rotate. Positive value rotates clockwise.
         */
        ActionRotate(int rotation);
        
        /**
         * Constructor with CommandsVector and rotation parameters.
         * @param commands Sequence of commands to be executed.
         * @param rotation Integer value of Robot rotation in degrees.
         */
        ActionRotate(CommandsVector commands, int rotation);

        /**
         * Get Robot rotation.
         * @return Integer value of rotation in degrees.
         */
        int getRotation();

        /**
         * Get ActionRotate encoded name and its parameters.
         * @return String with encoded name and parameters.
         */
        virtual std::string getActionPrototype();

        /**
         * Get ActionRotate human-readable name.
         * @return String with name and parameters
         */
        virtual std::string getString() override;

    protected:
        /// Angle of rotation in degrees for the Robot.
        int _rotation;
    };
    
    /**
     * @class ActionRotateRandDirection
     * 
     * Implements Robot simple task to rotate a random angle.
     * Rotation is performed in place.
     * Maximum angle in degrees is passed via constructor argument.
     */
    class ActionRotateRandDirection : public ActionRotate
    {
    public:
        /**
         * Constructor with rotation parameter in degrees.
         * @param rotation Upper limit of degrees to rotate randomly. Positive value rotates clockwise.
         */
        ActionRotateRandDirection(int rotation);
        
        /**
         * Constructor with CommandsVector and rotation parameters.
         * @param commands Sequence of commands to be executed.
         * @param rotation Upper limit of degrees to rotate randomly. Positive value rotates clockwise.
         */
        ActionRotateRandDirection(CommandsVector commands, int rotation);

        /**
         * Get ActionRotateRandDirection encoded name and its parameters.
         * @return String with encoded name and parameters.
         */
        virtual std::string getActionPrototype();

        /**
         * Get ActionRotateRandDirection human-readable name.
         * @return String with name and parameters
         */
        virtual std::string getString() override;

        /**
         * @see Action::execute
         */
        virtual void execute() override;
    };
    
    /**
     * @class ActionStop
     * 
     * Implements Robot simple task to stop all active motors.
     */
    class ActionStop : public Action
    {
    public:
        /**
         * Default constructor.
         */
        ActionStop();
        
        /**
         * Constructor with CommandsVector parameter.
         * @param commands Sequence of commands to be executed.
         */
        ActionStop(CommandsVector commands);

        /**
         * Get ActionStop encoded name and its parameters.
         * @return String with encoded name and parameters.
         */
        virtual std::string getActionPrototype();

        /**
         * Get ActionStop human-readable name.
         * @return String with name and parameters
         */
        virtual std::string getString() override;
    };
    
    /**
     * @class ActionDriveForever
     * 
     * Implements Robot simple task to drive straight forever.
     */
    class ActionDriveForever : public Action
    {
    public:
        /**
         * Constructor with direction parameter.
         * @param forward True to drive forward, false otherwise.
         */
        ActionDriveForever(bool forward = true);
        
        /**
         * Constructor with CommandsVector and direction parameter.
         * @param commands Sequence of commands to be executed.
         * @param forward True to drive forward, false otherwise.
         */
        ActionDriveForever(CommandsVector commands, bool forward = true);

        /**
         * Get ActionDriveForever encoded name and its parameters.
         * @return String with encoded name and parameters.
         */
        virtual std::string getActionPrototype();

        /**
         * Get ActionDriveForever human-readable name.
         * @return String with name and parameters
         */
        virtual std::string getString() override;
        
        /**
         * Return specified direction.
         * @return True for forward, false for backward.
         */
        bool isForward();
    
    private:
        /// Direction of driving. Either forward (true) or backward (false).
        bool _isForward;
    };
}
