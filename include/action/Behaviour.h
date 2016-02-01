#pragma once

#include "Action.h"
#include "Utils.h"
#include "Sensor.h"
#include "Event.h"

#include <unistd.h>
#include <string>

namespace ev3
{
    class Behaviour;

    // TODO Move to separate file.

    typedef std::map<Event::EventType, unsigned int> ReactionsTransitions;

    class BehaviourState
    {
    public:
        BehaviourState() = default;
        BehaviourState(const BehaviourState &) = default;
        BehaviourState(SharedPtrAction action, unsigned int nextState, bool isStopState = false);
        BehaviourState(SharedPtrAction action, unsigned int nextState, ReactionsTransitions reactions);

        unsigned int process();
        SharedPtrAction getAction();
        void setNextState(const unsigned int next);
        bool isStopState();
        void setReactions(ReactionsTransitions reactions);
        int getReaction(Event::EventType type);
        //        bool isExecuted();
    private:
        SharedPtrAction _action = nullptr;
        bool _isExecuted = false;
        bool _isStopState = false;
        unsigned int _nextStateId;

        ReactionsTransitions _reactions;

        // TODO events and reactions.
    };

    typedef std::shared_ptr<Behaviour> SharedPtrBehaviour;
    typedef std::vector<BehaviourState> BehaviourStates;
    typedef std::vector<Sensor::SensorType> Measurements;

    class Behaviour
    {
    public:

        enum BehaviourType
        {
            CUSTOM,
            DRIVE_ON_SQUARE,
            EXPLORE_RANDOM
        };

        Behaviour() = default;
        virtual ~Behaviour();

        Behaviour(BehaviourType type, BehaviourStates states);
        Behaviour(BehaviourType type);

        virtual void process();

        void setStates(BehaviourStates states);
        void setReactionStates(BehaviourStates reactionStates);
        void setStopState(BehaviourState state);
        void setMeasurements(Measurements measurements);

        virtual StringVector getPrototype();
        virtual std::string getString();

        static StringVector getParameters(StringVector proto);

        void stop();
        void pause();
        void resume();
        void start();
        void react(Event::EventType type);

    protected:
        BehaviourType _type;

        BehaviourState _currentState;
        BehaviourState _stopState;

        BehaviourStates _states;
        BehaviourStates _reactionStates;

        Measurements _measurements;

        bool _active = false;
    };

    class BehaviourDriveOnSquare : public Behaviour
    {
    public:
        BehaviourDriveOnSquare(unsigned int side, bool turningRight);
        BehaviourDriveOnSquare(BehaviourStates states, unsigned int side, bool turningRight);

        StringVector getPrototype() override;

        virtual std::string getString() override;

    private:
        unsigned int _squareSide;
        bool _isTurningRight;
    };

    class BehaviourExploreRandom : public Behaviour
    {
    public:
        BehaviourExploreRandom();
        BehaviourExploreRandom(BehaviourStates states);

        StringVector getPrototype() override;

        virtual std::string getString() override;
    };
}
