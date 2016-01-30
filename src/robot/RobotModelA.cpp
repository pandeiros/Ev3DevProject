#include "RobotModelA.h"
#include "Logger.h"

using namespace ev3;

RobotModelA::RobotModelA()
: Robot({
    {ev3dev::OUTPUT_B, ev3dev::large_motor::motor_large},
    {ev3dev::OUTPUT_C, ev3dev::large_motor::motor_large},
    {Devices::PORT_ANY, ev3dev::sensor::custom_ultrasonic}
},
{

    Action::DRIVE_DISTANCE,
            Action::STOP
})
{
    //    this->_pulsePerUnitRatio = 1.f * COUNT_PER_ROT / (M_PI * 2 * this->_wheelRadius * UNITS_PER_CENTIMETER);
    this->_pulsePerUnitRatio = COUNT_PER_ROT / (M_PI * 2 * this->_wheelRadius * UNITS_PER_CENTIMETER);
}

SharedPtrBehaviour RobotModelA::generateBehaviour(SharedPtrBehaviour & ptr, Behaviour::BehaviourType type, StringVector parameters)
{
    // TODO czemu behaviour uzalezniony od robota?

    StoredActions actions;
    //    SharedPtrBehaviour ptr;

    BehaviourStates states;

    try
    {
        switch (type)
        {
            case Behaviour::DRIVE_ON_SQUARE:
            {
                // Get square side and rotation direction.
                unsigned int side = transcode<unsigned int>(parameters[0]);
                bool isTurningRight = transcode<bool>(parameters[1]);
                Logger::getInstance()->log("Drive on square: " + std::to_string(type) +
                        ", " + std::to_string(side) + ", " +
                        std::to_string(isTurningRight), Logger::INFO);

                // Behaviour construction.
                try
                {
                    //                    states.push_back(
                    //                            BehaviourState(
                    //                            std::make_shared<ActionRepeat>(StoredActions({
                    //                                                           generateAction(std::make_shared<ActionDriveDistance>(side), Action::DRIVE_DISTANCE),
                    //                                                           generateAction(std::make_shared<ActionRotate>(isTurningRight ? 90 : -90), Action::ROTATE)
                    //
                    //                    }), 2), 0)
                    //                    );

                    ActionDriveDistance * forward = new ActionDriveDistance(side);
                    ActionRotate * rotate = new ActionRotate(isTurningRight ? 90 : -90);
                    states.push_back(
                            BehaviourState(generateAction(forward, Action::DRIVE_DISTANCE), 1));
                    states.push_back(
                            BehaviourState(generateAction(rotate, Action::ROTATE), 0));

                    //                            generateAction(forward, Action::DRIVE_DISTANCE)
                    //                            //                        generateAction(std::make_shared<ActionRotate>(isTurningRight ? 90 : -90), Action::ROTATE)
                    //
                    //                            , 0)
                    //                            );

                }
                catch (...)
                {
                    Logger::getInstance()->log("Generating Actions failed!", Logger::ERROR);
                }

                ptr = std::make_shared<BehaviourDriveOnSquare>(states, side, isTurningRight);
                break;
            }
            default:
                return std::shared_ptr<Behaviour>(nullptr);
        }
    }
    catch (...)
    {
        Logger::getInstance()->log("Generating Behaviour failed!", Logger::ERROR);
    }

    return ptr;
}

Action * RobotModelA::generateAction(Action * action, Action::ActionType type)
{

    auto motorLeft = Devices::getInstance()->getMotor(ev3dev::OUTPUT_B);
    auto motorRight = Devices::getInstance()->getMotor(ev3dev::OUTPUT_C);

    switch (type)
    {
        case Action::DRIVE_DISTANCE:

        {
            unsigned int distance = dynamic_cast<ActionDriveDistance*>
                    (action)->getDistance() * _pulsePerUnitRatio;

            action->setCommands({
                std::make_shared<CommandMotorReset>(motorLeft),
                std::make_shared<CommandMotorSetSpeedRegEnabled>(motorLeft, true),
                std::make_shared<CommandMotorSetSpeed>(motorLeft, 700),
                std::make_shared<CommandMotorRunForever>(motorLeft),
                std::make_shared<CommandMotorReset>(motorRight),
                std::make_shared<CommandMotorSetSpeedRegEnabled>(motorRight, true),
                std::make_shared<CommandMotorSetSpeed>(motorRight, 700),
                std::make_shared<CommandMotorRunForever>(motorRight),
            });
            action->setEndCondition([&, distance]()-> bool
            {
                bool v = std::abs(Devices::getInstance()->getMotor(ev3dev::OUTPUT_B)
                        .getMotor().position()) > distance;
                Logger::getInstance()->log("Functor " + std::to_string(v), Logger::VERBOSE);
                return v;
            });
            break;
        }
        case Action::ROTATE:
        {
            unsigned int position = dynamic_cast<ActionRotate*> (action)
                    ->getRotation() * _pulsePerUnitRatio;
            
            int ccw = -1;
            if (position > 0)
                ccw = 1;

            action->setCommands({
                std::make_shared<CommandMotorReset>(motorLeft),
                std::make_shared<CommandMotorSetSpeedRegEnabled>(motorLeft, true),
                std::make_shared<CommandMotorSetSpeed>(motorLeft, 200 * ccw),
                std::make_shared<CommandMotorRunForever>(motorLeft),
                std::make_shared<CommandMotorReset>(motorRight),
                std::make_shared<CommandMotorSetSpeedRegEnabled>(motorRight, true),
                std::make_shared<CommandMotorSetSpeed>(motorRight, 200 * -ccw),
                std::make_shared<CommandMotorRunForever>(motorRight)
            });
            action->setEndCondition([&, position]()-> bool
            {
                return std::abs(Devices::getInstance()->getMotor(ev3dev::OUTPUT_B).
                        getMotor().position()) > std::abs(position);
            });
            break;
        }
        default:
            return nullptr;
    }

    return action;
}
