#pragma once

#include "Action.h"
#include "Utils.h"
#include "Sensor.h"
#include "Event.h"
#include "BehaviourState.h"

#include <unistd.h>
#include <string>

/**
 * @file Behaviour.h
 * Contains all Behaviour classes.
 */

namespace ev3
{
    class Behaviour;

    /// Type for Behaviour shared_ptr.
    typedef std::shared_ptr<Behaviour> SharedPtrBehaviour;

    /// Type for storing Behaviour states in one container.
    typedef std::vector<BehaviourState> BehaviourStates;

    /// Type for storing sensors' desired measurements in one container.
    typedef std::vector<Sensor::SensorType> Measurements;

    /**
     * @class Behaviour
     * Base class for all defined behaviours.
     * It's responsible for maintaining active actions in a form of a 
     * state machine as well as keep track of sensors' measurements.
     */
    class Behaviour
    {
    public:

        /**
         * Type of Behaviour.
         */
        enum BehaviourType
        {
            CUSTOM, /**< Custom, user-defined behaviour. */
            DRIVE_ON_SQUARE, /**< Follow square-shaped route. */
            EXPLORE_RANDOM /**< Drive in a direction and rotate randomly. */
        };

        /**
         * Default constructor.
         */
        Behaviour() = default;

        /**
         * Constructor with type and states vector parameters.
         * @param type Behaviour type.
         * @param states Vector of available Behaviour states.
         */
        Behaviour(BehaviourType type, BehaviourStates states);

        /**
         * Constructor with behaviour type.
         * @param type Behaviour type.
         */
        Behaviour(BehaviourType type);

        /**
         * Available states setter.
         * @param states Vector of states for this Behaviour.
         */
        void setStates(BehaviourStates states);

        /**
         * Special reaction states which occur when event is fired.
         * @param reactionStates Vector of reaction states for this Behaviour.
         */
        void setReactionStates(BehaviourStates reactionStates);

        /**
         * Special stop state, used mainly to get precise sensor measurements.
         * @param state BehaviourState object for stop state.
         */
        void setStopState(BehaviourState state);

        /**
         * Sensor which measurements will be required.
         * @param measurements Vector of sensor types.
         */
        void setMeasurements(Measurements measurements);

        /**
         * Get Behaviour encoded name and its parameters.
         * @return StringVector with encoded name and parameters as its members.
         */
        virtual StringVector getPrototype();

        /**
         * Get Behaviour human-readable name.
         * @return String with name and parameters
         */
        virtual std::string getString();

        /**
         * Updates behaviour in every iteration.
         */
        virtual void process();

        /**
         * Stops Behaviour execution definetely.
         */
        void stop();

        /**
         * Pauses Behaviour execution until it's resumed.
         */
        void pause();

        /**
         * Resumes paused Behaviour.
         */
        void resume();

        /**
         * Starts Behaviour execution.
         */
        void start();

        /**
         * Performs special actions based on Event passed.
         * @param type Event type that will be processed.
         */
        void react(Event::EventType type);

    protected:
        /// Type of Behaviour.
        BehaviourType _type;

        /// Currently processed Behaviour.
        BehaviourState _currentState;

        /// Special stop state for measurements and accurate action execution.
        BehaviourState _stopState;

        /// Vector with all Behaviour available states.
        BehaviourStates _states;

        /// Vector with all reaction states, occuring after specific events.
        BehaviourStates _reactionStates;

        /// Vector of all Sensor ids that will be measured.
        Measurements _measurements;

        /// Specified whether Behaviour is currently active or not.
        bool _active = false;
    };

    /**
     * @class BehaviourDriveOnSquare
     * Implements complex behaviour of driving on a square-shaped route.
     * Square side and direction (right/left) can be implicitly defined.
     */
    class BehaviourDriveOnSquare : public Behaviour
    {
    public:
        /**
         * Constructor with square side and direction (either left or right).
         * @param side Length of square side in units.
         * @param turningRight True for turning right, false otherwise.
         */
        BehaviourDriveOnSquare(unsigned int side, bool turningRight);

        /**
         * Constructor with Behaviour states and driving parameters.
         * @param states Vector of Behaviour states to be processed.
         * @param side Length of square side in units.
         * @param turningRight True for turning right, false otherwise.
         */
        BehaviourDriveOnSquare(BehaviourStates states, unsigned int side, bool turningRight);

        /**
         * Get BehaviourDriveOnSquare encoded name and its parameters.
         * @return StringVector with encoded name and parameters as its members.
         */
        virtual StringVector getPrototype();

        /**
         * Get BehaviourDriveOnSquare human-readable name.
         * @return String with name and parameters
         */
        virtual std::string getString();

    private:
        /// Length of square side in units.
        unsigned int _squareSide;

        /// Drive direction. True for turning right, false otherwise.
        bool _isTurningRight;
    };

    /**
     * @class BehaviourExploreRandom
     * Implements complex behaviour of exploring the surrounding with
     * random rotation.
     */
    class BehaviourExploreRandom : public Behaviour
    {
    public:
        /**
         * Default constructor.
         */
        BehaviourExploreRandom();

        /**
         * Constructor with Behaviour states parameter.
         * @param states Vector of available Behaviour states.
         */
        BehaviourExploreRandom(BehaviourStates states);

        /**
         * Get BehaviourExploreRandom encoded name and its parameters.
         * @return StringVector with encoded name and parameters as its members.
         */
        virtual StringVector getPrototype();

        /**
         * Get BehaviourExploreRandom human-readable name.
         * @return String with name and parameters
         */
        virtual std::string getString();
    };
}
