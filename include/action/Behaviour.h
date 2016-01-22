#pragma once

#include "Action.h"
#include "Utils.h"

#include <unistd.h>

namespace ev3
{
    class Behaviour;
    
    typedef std::shared_ptr<Behaviour> SharedPtrBehaviour;
        
    class Behaviour
    {
    public:
        
        enum BehaviourType {
            CUSTOM,
            DRIVE_ON_SQUARE
        };

        Behaviour() = default;
        Behaviour(BehaviourType type, StoredActions actions);
        Behaviour(BehaviourType type);

        virtual void execute();
        
        void setActions(StoredActions actions);
        
        static StringVector getParameters(StringVector proto);
        
    protected:
        BehaviourType _type;
        
        StoredActions _actions;
    };
    
    
    class BehaviourDriveOnSquare : public Behaviour
    {
    public:
        BehaviourDriveOnSquare(StoredActions actions, unsigned int side, bool turningRight);
        
    private:
        unsigned int _squareSide;
        bool _isTurningRight;
    };
}
