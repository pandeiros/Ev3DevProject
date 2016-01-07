#pragma once

#include "CommandMotor.h"

namespace ev3
{

    class Action
    {
    public:

        enum ActionType
        {
            NOP,
            REPEAT_FOREVER,
            DRIVE_DISTANCE,
            ROTATE,
            STOP
        };

        //        enum ConditionType
        //        {
        //            GREATER,
        //            SMALLER,
        //            EQUAL
        //        };

        static const std::string EMPTY_PROTO;

        typedef std::vector<Command*> CommandsVector;
        typedef std::function<bool(void) > EndCondition;

        Action(CommandsVector commands, ActionType type);
        Action(CommandsVector commands);
        Action(ActionType type);
        virtual ~Action();

        virtual void execute();
        virtual bool isFinished();
        virtual std::string getActionPrototype();

        void setCommands(CommandsVector commands);
        void setEndCondition(EndCondition condition);
        //        void setEndCondition(std::function<int(void)> func, ConditionType type);

        ActionType getType();

    protected:
        ActionType _type;
        CommandsVector _commands;

        EndCondition _endCondition = []()
        {
            return true;
        };
    };

    class ActionRepeat : public Action
    {
    public:
        ActionRepeat(std::vector<Action*> actions, unsigned n);
        virtual void execute();

        void setRepeatCondition(EndCondition condition);

    private:
        std::vector<Action*> _actions;
        unsigned int _n;

        EndCondition _repeatCondition = []()
        {
            return true;
        };
    };

    class ActionDriveDistance : public Action
    {
    public:
        ActionDriveDistance(int distance);

        int getDistance();

        virtual std::string getActionPrototype();

    private:
        int _distance;
    };

    class ActionRotate : public Action
    {
    public:
        ActionRotate(int rotation);

        int getRotation();

        virtual std::string getActionPrototype();

    private:
        int _rotation;
    };
}