#pragma once

#include "Action.h"
#include "Utils.h"
#include "Sensor.h"

#include <unistd.h>

namespace ev3
{
    class Behaviour;

    // TODO Move to separate file.

    class BehaviourState
    {
    public:
        BehaviourState() = default;
        BehaviourState ( const BehaviourState & ) = default;	
        BehaviourState(Action * action, unsigned int nextState);

        unsigned int process();
        Action * getAction();
        //        bool isExecuted();
    private:
        Action * _action;
        bool _isExecuted = false;
        unsigned int _nextStateId;

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
            DRIVE_ON_SQUARE
        };

        Behaviour() = default;
        virtual ~Behaviour();
        
        Behaviour(BehaviourType type, BehaviourStates states);
        Behaviour(BehaviourType type);

        virtual void process();

        void setStates(BehaviourStates states);
        void setMeasurements(Measurements measurements);

        virtual StringVector getPrototype();

        static StringVector getParameters(StringVector proto);

    protected:
        BehaviourType _type;

        BehaviourState _currentState;

        BehaviourStates _states;

        Measurements _measurements;
    };

    class BehaviourDriveOnSquare : public Behaviour
    {
    public:
        BehaviourDriveOnSquare(unsigned int side, bool turningRight);
        BehaviourDriveOnSquare(BehaviourStates states, unsigned int side, bool turningRight);

        StringVector getPrototype() override;
    private:
        unsigned int _squareSide;
        bool _isTurningRight;
    };
}
