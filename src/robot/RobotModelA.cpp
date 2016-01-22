#include "RobotModelA.h"

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

SharedPtrBehaviour RobotModelA::generateBehaviour(Behaviour::BehaviourType type, StringVector & parameters)
{
    StoredActions actions;
    SharedPtrBehaviour ptr;

    try
    {
        switch (type)
        {
            case Behaviour::DRIVE_ON_SQUARE:
            {
                // Get square side and rotation direction.
                unsigned int side = transcode<unsigned int>(parameters[0]);
                bool isTurningRight = transcode<bool>(parameters[1]);
                std::cout << type << " " << side << " " << isTurningRight << "\n";

                // Behaviour construction.
                actions.push_back(
                                  std::make_shared<ActionRepeat>(StoredActions({
                                                                               generateAction(std::make_shared<ActionDriveDistance>(side), Action::DRIVE_DISTANCE),
                                                                               generateAction(std::make_shared<ActionRotate>(isTurningRight ? 90 : -90), Action::ROTATE)

                }), 2));

                ptr = std::make_shared<BehaviourDriveOnSquare>(actions, side, isTurningRight);
                break;
            }
            default:
                break;
        }
    }
    catch (...)
    {

    }

    return ptr;
}

SharedPtrAction RobotModelA::generateAction(SharedPtrAction action, Action::ActionType type)
{
    auto motorLeft = Devices::getInstance()->getMotor(ev3dev::OUTPUT_B);
    auto motorRight = Devices::getInstance()->getMotor(ev3dev::OUTPUT_C);

    switch (type)
    {
        case Action::DRIVE_DISTANCE:
            action->setCommands({
                                std::make_shared<CommandMotorReset>(motorLeft),
                                std::make_shared<CommandMotorSetSpeedRegEnabled>(motorLeft, true),
                                std::make_shared<CommandMotorSetSpeed>(motorLeft, 400),
                                std::make_shared<CommandMotorRunForever>(motorLeft),
                                std::make_shared<CommandMotorReset>(motorRight),
                                std::make_shared<CommandMotorSetSpeedRegEnabled>(motorRight, true),
                                std::make_shared<CommandMotorSetSpeed>(motorRight, 400),
                                std::make_shared<CommandMotorRunForever>(motorRight),
            });
            action->setEndCondition([&]()-> bool
            {
                return std::abs(motorLeft.getMotor().position()) >
                        dynamic_cast<ActionDriveDistance*> (action.get())->getDistance() * _pulsePerUnitRatio;
            });
            break;
        case Action::ROTATE:
            action->setCommands({
                                std::make_shared<CommandMotorReset>(motorLeft),
                                std::make_shared<CommandMotorSetSpeedRegEnabled>(motorLeft, true),
                                std::make_shared<CommandMotorSetSpeed>(motorLeft, 200),
                                std::make_shared<CommandMotorRunForever>(motorLeft),
                                std::make_shared<CommandMotorReset>(motorRight),
                                std::make_shared<CommandMotorSetSpeedRegEnabled>(motorRight, true),
                                std::make_shared<CommandMotorSetSpeed>(motorRight, 200),
                                std::make_shared<CommandMotorRunForever>(motorRight)
            });
            action->setEndCondition([&]()-> bool
            {
                return std::abs(motorLeft.getMotor().position()) >
                        dynamic_cast<ActionRotate*> (action.get())->getRotation() * _pulsePerUnitRatio;
            });
            break;
        default:
            break;
    }

    return action;
}