#pragma once

#include "Action.h"
#include "Event.h"

/**
 * @file BehaviourState.h
 * Contains BehaviourState class.
 */

namespace ev3
{
    /// Type for storing Event-State pairs defining special transitions.
    typedef std::map<Event::EventType, unsigned int> ReactionsTransitions;

    /**
     * @class BehaviourState
     * Encapsulates action and other information in a form of a state. It can
     * contain reactions to different events.
     */
    class BehaviourState
    {
    public:
        /**
         * Default constructor.
         */
        BehaviourState() = default;
        
        /**
         * Default copy constructor.
         * @param Other BehaviourState object.
         */
        BehaviourState(const BehaviourState &) = default;
        
        /**
         * Constructor with action, next state id and stop state flag.
         * @param action Action object to be executed within this state.
         * @param nextState Id of the next state that will replace this one.
         * @param isStopState Flag defining this state as a in-between, stopping state.
         */
        BehaviourState(SharedPtrAction action, unsigned int nextState, bool isStopState = false);
        
        /**
         * Constructor with action, next state id and event-state map.
         * @param action Action object to be executed within this state,
         * @param nextState Id of the next state that will replace this one.
         * @param reactions Map containing event-state pairs describing reactions.
         */
        BehaviourState(SharedPtrAction action, unsigned int nextState, ReactionsTransitions reactions);

        /**
         * Process state in every iteration.
         * @return Id of the next state.
         */
        unsigned int process();
        
        /**
         * State's Action getter.
         * @return Action shared_ptr object.
         */
        SharedPtrAction getAction();
        
        /**
         * Next state id setter.
         * @param next Integer defining next state id.
         */
        void setNextState(const unsigned int next);
        
        /**
         * Stop flag getter.
         * @return True if state is flagged as a stop state, false otherwise.
         */
        bool isStopState();
        
        /**
         * Reactions setter.
         * @param reactions Map with Event-State pair.
         */
        void setReactions(ReactionsTransitions reactions);
        
        /**
         * Reaction getter.
         * @param type EventType to which reaction occurs.
         * @return Id of the reaction state.
         */
        int getReaction(Event::EventType type);

    private:
        /// Encapsulated action.
        SharedPtrAction _action = nullptr;
        
        /// True if state was executed, false otherwise.
        bool _isExecuted = false;
        
        /// Stop flag.
        bool _isStopState = false;
        
        /// Id of the next state.
        unsigned int _nextStateId;

        /// Map of event-triggered transitions.
        ReactionsTransitions _reactions;
    };
}