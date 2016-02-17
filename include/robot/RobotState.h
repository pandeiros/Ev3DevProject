#pragma once

#include "Message.h"
#include "LedControl.h"
#include "Utils.h"
#include "Behaviour.h"

#include <map>
#include <chrono>

namespace ev3
{
    /**
     * @class RobotState
     * Base class for all Robot states. Contains of transitions, timing 
     * methods and Behaviour processing.
     */
    class RobotState
    {
    public:

        /**
         * State names (types).
         */
        enum States
        {
            IDLE,       /**< Powered, but not connected. */
            ACTIVE,     /**< Conected, but no task assigned. */
            WORKING,    /**< Processing Behaviour. */
            PAUSED,     /**< Behaviour processing paused. */
            PANIC       /**< Lost connection or no connection at all. */
        };

        /// Default time to enter PANIC state.
        const static float MASTER_TIMEOUT;
        
        /// Time interval for PING-PONG Message exchange.
        const static float MASTER_PING_TIME;

        /// Type for defining transitions when particular Messages occur.
        typedef std::map<Message::MessageType, States> ChangeMap;

        /**
         * Constructor with transitions map and LED control pointer.
         * @param changes List of available transitions.
         * @param led Pointer to LedControl object for diodes control.
         */
        RobotState(ChangeMap changes, LedControl * led);
        
        /**
         * Processes currently assigned state.
         * @param msg Message to be interpreted withing current state.
         * @return Pointer to new state or 'this'.
         */
        virtual RobotState * process(Message msg);

        /**
         * Get Message to be sent to Master.
         * @return Type of Message that has to be forwarded.
         */
        Message::MessageType getPendingMessage();
        
        /**
         * Updates timeouts and pings.
         */
        void updateTimer();

        /**
         * Get information whether state is waiting for response.
         * @return True if new Messages can be sent, false otherwise.
         */
        bool isPendingEnabled();

        /**
         * Set new Behaviour for this state.
         * @param behaviour Behaviour shared pointer object.
         */
        void setBehaviour(SharedPtrBehaviour behaviour);
        
        /**
         * Behaviour getter.
         * @return Shared pointer with stored Behaviour object.
         */
        SharedPtrBehaviour getBehaviour();
        
    protected:
        /**
         * Normal state changing method. 
         * @param type Messgae type indicating new state to be assigned.
         * @return Pointer to created state.
         */
        RobotState* switchState(Message::MessageType type);
        
        /**
         * Force state changing method.
         * @param state New state to be assigned.
         * @return Pointer to created state.
         */
        RobotState* changeState(States state);

        /// Currently processed Behaviour.
        SharedPtrBehaviour _currentBehaviour;

        /// Current state type.
        States _state;
        
        /// Map of state transitions.
        ChangeMap _changes;
        
        /// LED diodes controlling pointer.
        LedControl * _led;
        
        /// Type of Message that's going to be forwarded.
        Message::MessageType _pendingMessage = Message::EMPTY;
        
        /// Time to wait for response.
        float _pendingTimeout = 0.f;

        /// Time for measuring master PING response.
        HighResClock::time_point _masterTimeout = HighResClock::now();
        
        /// Time for measuring master response for a particular Message.
        HighResClock::time_point _messageDelay = HighResClock::now();
    };

    /**
     * @class RobotStateIdle
     * State in which Robot is powered but not connected to Master.
     */
    class RobotStateIdle : public RobotState
    {
    public:
        /**
         * Constructor with LED controller.
         * @param led LedControl pointer.
         */
        RobotStateIdle(LedControl * led);
        
         /**
         * Overriden process method.
         */
        RobotState * process(Message msg);
    };

    /**
     * @class RobotStateActive
     * State in which Robot is connected but has no assigned Behaviour.
     */
    class RobotStateActive : public RobotState
    {
    public:
        /**
         * Constructor with LED controller.
         * @param led LedControl pointer.
         */
        RobotStateActive(LedControl * led);
        
        /**
         * Overriden process method.
         */
        RobotState * process(Message msg);
    };

    /**
     * @class RobotStateWorking
     * State in which Robot is processing assigned Behaviour.
     */
    class RobotStateWorking : public RobotState
    {
    public:
        /**
         * Constructor with LED controller.
         * @param led LedControl pointer.
         */
        RobotStateWorking(LedControl * led);
        
        /**
         * Overriden process method.
         */
        RobotState * process(Message msg);
    };

    /**
     * @class RobotStatePaused
     * State in which Robot's Behaviour processing is paused.
     */
    class RobotStatePaused : public RobotState
    {
    public:
        /**
         * Constructor with LED controller.
         * @param led LedControl pointer.
         */
        RobotStatePaused(LedControl * led);
        
        /**
         * Overriden process method.
         */
        RobotState * process(Message msg);
    };

    /**
     * @class RobotStatePanic
     * State in which Robot lost connection with Master or had no
     * connection at all.
     */
    class RobotStatePanic : public RobotState
    {
    public:
        /**
         * Constructor with LED controller.
         * @param led LedControl pointer.
         */
        RobotStatePanic(LedControl * led);
        
        /**
         * Overriden process method.
         */
        RobotState * process(Message msg);
    };
}

