#include "RobotModelA.h"
#include "Logger.h"

using namespace ev3;

RobotModelA::RobotModelA()
: Robot({
    {ev3dev::OUTPUT_B, ev3dev::large_motor::motor_large},
    {ev3dev::OUTPUT_C, ev3dev::large_motor::motor_large},
    {ev3dev::INPUT_2, ev3dev::sensor::ev3_touch},
    {ev3dev::INPUT_1, ev3dev::sensor::ev3_ultrasonic}
},
{

    Action::DRIVE_DISTANCE,
            Action::STOP
})
{
    //    this->_pulsePerUnitRatio = 1.f * COUNT_PER_ROT / (M_PI * 2 * this->_wheelRadius * UNITS_PER_CENTIMETER);
    this->_pulsePerUnitRatio = COUNT_PER_ROT / (M_PI * 2 * this->_wheelRadius * UNITS_PER_CENTIMETER);
    Devices::getInstance()->setSafetyTouchSensor(ev3dev::INPUT_2);
    Devices::getInstance()->setProximitySensor(ev3dev::INPUT_1);
}

std::string RobotModelA::getString()
{
    return "<Robot model A>";
}

SharedPtrBehaviour RobotModelA::generateBehaviour(Behaviour::BehaviourType type, StringVector parameters)
{
    BehaviourStates states;
    BehaviourStates reactionStates;
    BehaviourState stopState;
    ReactionsTransitions reactions;
    SharedPtrBehaviour behaviour;

    try
    {
        switch (type)
        {
            case Behaviour::DRIVE_ON_SQUARE:
            {
                // Get square side and rotation direction.
                unsigned int side = transcode<unsigned int>(parameters[0]);
                bool isTurningRight = transcode<bool>(parameters[1]);

                // Behaviour construction.
                try
                {

                    states.push_back(
                            BehaviourState(generateAction(std::make_shared<ActionDriveDistance>(side), Action::DRIVE_DISTANCE), 1,
                    {
                        {Event::OBSTACLE_DETECTED, 0},
                        {Event::PROXIMITY_ALERT, 1}
                    }));
                    states.push_back(
                            BehaviourState(generateAction(std::make_shared<ActionRotate>(isTurningRight ? 90 : -90), Action::ROTATE), 0));

                    stopState = BehaviourState(generateAction(std::make_shared<ActionStop>(), Action::STOP), 0, true);

                    reactionStates.push_back(
                            BehaviourState(generateAction(std::make_shared<ActionDriveDistance>(-100), Action::DRIVE_DISTANCE), 1));

                    reactionStates.push_back(
                            BehaviourState(generateAction(std::make_shared<ActionStop>(), Action::STOP), 1));

                }
                catch (...)
                {
                    Logger::getInstance()->log("Generating Actions failed!", Logger::ERROR);
                }

                behaviour = std::make_shared<BehaviourDriveOnSquare>(states, side, isTurningRight);
                break;
            }
            case Behaviour::EXPLORE_RANDOM:
            {
                // Behaviour construction.
                try
                {

                    states.push_back(
                            BehaviourState(generateAction(std::make_shared<ActionDriveForever>(true), Action::DRIVE_FOREVER), 1,
                    {
                        {Event::OBSTACLE_DETECTED, 0},
                        {Event::PROXIMITY_ALERT, 1}
                    }));
                    states.push_back(
                            BehaviourState(generateAction(std::make_shared<ActionRotateRandDirection>(360), Action::ROTATE_RANDOM_DIR), 0));

                    stopState = BehaviourState(generateAction(std::make_shared<ActionStop>(), Action::STOP), 0, true);

                    reactionStates.push_back(
                            BehaviourState(generateAction(std::make_shared<ActionDriveDistance>(-100), Action::DRIVE_DISTANCE), 1));

                    reactionStates.push_back(
                            BehaviourState(generateAction(std::make_shared<ActionStop>(), Action::STOP), 1));

                }
                catch (...)
                {
                    Logger::getInstance()->log("Generating Actions failed!", Logger::ERROR);
                }

                behaviour = std::make_shared<Behaviour>(Behaviour::EXPLORE_RANDOM, states);
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

    behaviour->setStopState(stopState);
    behaviour->setReactionStates(reactionStates);
    std::cout << behaviour.get() << "\n";
    Logger::getInstance()->log(this->getString() + " " + behaviour->getString(), Logger::INFO);
    return behaviour;
}

SharedPtrAction RobotModelA::generateAction(SharedPtrAction action, Action::ActionType type)
{
    auto motorLeft = Devices::getInstance()->getMotor(ev3dev::OUTPUT_B);
    auto motorRight = Devices::getInstance()->getMotor(ev3dev::OUTPUT_C);

    switch (type)
    {
        case Action::DRIVE_DISTANCE:
        {
            int distance = dynamic_cast<ActionDriveDistance*>
                    (action.get())->getDistance() * _pulsePerUnitRatio;

            int direction = distance < 0 ? -1 : 1;

            action->setCommands({
                std::make_shared<CommandMotorReset>(motorLeft),
                std::make_shared<CommandMotorReset>(motorRight),
                std::make_shared<CommandMotorSetSpeedRegEnabled>(motorLeft, true),
                std::make_shared<CommandMotorSetSpeed>(motorLeft, 700 * direction),
                std::make_shared<CommandMotorRunForever>(motorLeft),
                std::make_shared<CommandMotorSetSpeedRegEnabled>(motorRight, true),
                std::make_shared<CommandMotorSetSpeed>(motorRight, 700 * direction),
                std::make_shared<CommandMotorRunForever>(motorRight),
            });
            action->setEndCondition([&, distance, action]()-> bool
            {
                bool v = std::abs(Devices::getInstance()->getMotor(ev3dev::OUTPUT_B)
                        .getMotor().position()) > std::abs(distance);
                return v;
            });
            break;
        }
        case Action::ROTATE:
        {
            unsigned int position = dynamic_cast<ActionRotate*> (action.get())->getRotation() * _pulsePerUnitRatio;

            int ccw = -1;
            if (position > 0)
                ccw = 1;

            action->setCommands({
                std::make_shared<CommandMotorReset>(motorLeft),
                std::make_shared<CommandMotorReset>(motorRight),
                std::make_shared<CommandMotorSetSpeedRegEnabled>(motorLeft, true),
                std::make_shared<CommandMotorSetSpeed>(motorLeft, 200 * ccw),
                std::make_shared<CommandMotorRunForever>(motorLeft),
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
        case Action::ROTATE_RANDOM_DIR:
        {
            unsigned int position = dynamic_cast<ActionRotateRandDirection*> (action.get())->getRotation() * _pulsePerUnitRatio;

            action->setCommands({
                std::make_shared<CommandMotorReset>(motorLeft),
                std::make_shared<CommandMotorReset>(motorRight),
                std::make_shared<CommandMotorSetSpeedRegEnabled>(motorLeft, true),
                //                std::make_shared<CommandMotorSetSpeed>(motorLeft, 200 * ccw),
                //                std::make_shared<CommandMotorRunForever>(motorLeft),
                std::make_shared<CommandMotorSetSpeedRegEnabled>(motorRight, true)
                //                std::make_shared<CommandMotorSetSpeed>(motorRight, 200 * -ccw),
                //                std::make_shared<CommandMotorRunForever>(motorRight)
            });
            action->setEndCondition([&, position]()-> bool
            {
                return std::abs(Devices::getInstance()->getMotor(ev3dev::OUTPUT_B).
                        getMotor().position()) > std::abs(std::rand() % position);
            });
            break;
        }
        case Action::DRIVE_FOREVER:
        {
            int direction = dynamic_cast<ActionDriveForever*>
                    (action.get())->isForward() ? 1 : -1;
            action->setCommands({
                std::make_shared<CommandMotorReset>(motorLeft),
                std::make_shared<CommandMotorReset>(motorRight),
                std::make_shared<CommandMotorSetSpeedRegEnabled>(motorLeft, true),
                std::make_shared<CommandMotorSetSpeed>(motorLeft, 700 * direction),
                std::make_shared<CommandMotorRunForever>(motorLeft),
                std::make_shared<CommandMotorSetSpeedRegEnabled>(motorRight, true),
                std::make_shared<CommandMotorSetSpeed>(motorRight, 700 * direction),
                std::make_shared<CommandMotorRunForever>(motorRight)
            });
            action->setEndCondition([&]()-> bool
            {
                return false;
            });
            break;
        }
        case Action::STOP:
        {
            action->setCommands({
                std::make_shared<CommandMotorSetStopMode>(motorLeft, CommandMotorSetStopMode::BRAKE),
                std::make_shared<CommandMotorSetStopMode>(motorRight, CommandMotorSetStopMode::BRAKE),
                std::make_shared<CommandMotorStop>(motorLeft),
                std::make_shared<CommandMotorStop>(motorRight)
            });
            break;
        }
        default:
            return nullptr;
    }

    return action;
}
