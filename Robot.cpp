#include "Robot.h"
#include "ColorUtils.h"
#include <unistd.h>
#include <iostream>
#include <functional>
#include <future>
#include "ev3dev.h"

#include "Behaviour.h"
#include "Agent.h"

using namespace ev3;

const ev3dev::port_type Robot::PORT_ANY{"any"};

//RobotStatus::RobotStatus() { }

//int RobotStatus::getValue(ev3dev::port_type port, unsigned int index)
//{
//    return values.at(port).at(index).first;
//}
//
//float RobotStatus::getValueF(ev3dev::port_type port, unsigned int index)
//{
//    return static_cast<float> (values.at(port).at(index).first) / values.at(port).at(index).second;
//}

Robot::Robot() { }

Robot::Robot(RequiredDevices devices, AvailableActions actions)
: _requiredDevices(devices), _availableActions(actions) { }

Robot::~Robot() { }

std::thread Robot::createThread(MessageQueue * sendQueue, MessageQueue * receiveQueue)
{
    return std::thread([ = ]{run(sendQueue, receiveQueue);});
}

void Robot::run(MessageQueue * sendQueue, MessageQueue * receiveQueue)
{
    _sendQueue = sendQueue;
    _receiveQueue = receiveQueue;

    if (!this->checkDevices())
    {
        // EXCEPTION
        std::cout << "Nop...\n";
    }
    else
        std::cout << "Devices correct.\n";

    Message agentMsg(0, MASTER_ID, _commId++, Message::AGENT,{});

    sendQueue->push(agentMsg);

    bool stop = false;

    Message msg = receiveQueue->pop();
    while (!stop)
    {
        if (msg.getType() == Message::MASTER_OVER)
            break;
        
        if (msg.getType() == Message::MASTER)
        {
            _id = msg.getReceiverId();
        }
        
        if (msg.getType() == Message::MASTER)
        {
            unsigned int id = msg.getSenderId();
            if (id == MASTER_ID)
            {
                if (_commId < msg.getMessageId())
                {
                    //_sendQueue->push(Message(MASTER_ID, id, msg.getMessageId(), Message::PONG, {}));
                    _commId = msg.getMessageId();
                }
            }
        }
        
        if (_id)
            _sendQueue->push(Message(_id, MASTER_ID, _commId++, Message::PING, {}));

        if (msg.empty())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            
            if (!receiveQueue->empty())
                msg = receiveQueue->pop();
            continue;
        }
        
//        if (_id)
//            _sendQueue->push(Message(_id, MASTER_ID, _commId++, Message::PING, {}));

        //parseMessage(msg);

//        std::cout << msg.getMessageId() << " : ";
//        for (auto & s : msg.getParameters())
//            std::cout << s << " ";
//        std::cout << "\n";

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        msg = receiveQueue->pop();
    }

//    std::cout << msg.getMessageId() << " : ";
//    for (auto & s : msg.getParameters())
//        std::cout << s << " ";
//    std::cout << "\n";

    return;

    _ledControl.on(LedControl::RED_ALL);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    _ledControl.on(LedControl::GREEN_ALL, 150);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    _ledControl.on(LedControl::RED_ALL, 100);
    _ledControl.on(LedControl::GREEN_ALL, 250);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    _ledControl.off(LedControl::RED_ALL);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    _ledControl.onExclusive(LedControl::RED_ALL);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    _ledControl.onExclusive(LedControl::GREEN_ALL);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    _ledControl.off(LedControl::ALL);
    _ledControl.flash(200, 5, 50);
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    _ledControl.endFlashing();
    _ledControl.flash(200, 0, 50);
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    _ledControl.endFlashing();

    _ledControl.onExclusive(LedControl::GREEN_ALL);
    return;

    if (_motors.size() > 0)
    {
        auto motorLeft = _motors.at(ev3dev::OUTPUT_B);
        auto motorRight = _motors.at(ev3dev::OUTPUT_C);

        //auto us = _sensors.at(ev3dev::INPUT_1);

        //std::cout << us.type_name() << "  " << us.num_values() << "  " << us.decimals() << "\n";

        ActionDriveDistance * action = new ActionDriveDistance(500);
        action->setCommands({
            new CommandMotorReset(motorLeft),
            new CommandMotorSetSpeedRegEnabled(motorLeft, true),
            new CommandMotorSetSpeed(motorLeft, 400),
            new CommandMotorRunForever(motorLeft),
            new CommandMotorReset(motorRight),
            new CommandMotorSetSpeedRegEnabled(motorRight, true),
            new CommandMotorSetSpeed(motorRight, 400),
            new CommandMotorRunForever(motorRight)
        });

        action->setEndCondition([&]()-> bool
        {
            return std::abs(motorLeft.position()) > action->getDistance() * _pulsePerUnitRatio;
        });

        ActionRotate * action2 = new ActionRotate(180);
        action2->setCommands({
            new CommandMotorReset(motorLeft),
            new CommandMotorSetSpeedRegEnabled(motorLeft, true),
            new CommandMotorSetSpeed(motorLeft, 200),
            new CommandMotorRunForever(motorLeft),
            new CommandMotorReset(motorRight),
            new CommandMotorSetSpeedRegEnabled(motorRight, true),
            new CommandMotorSetSpeed(motorRight, -200),
            new CommandMotorRunForever(motorRight)
        });

        action2->setEndCondition([&]()-> bool
        {
            return std::abs(motorLeft.position()) > action2->getRotation() * _pulsePerUnitRatio;
        });

        Action * b = new Action({
            new CommandMotorStop(motorLeft),
            new CommandMotorStop(motorRight)
        });

        ActionRepeat * rep = new ActionRepeat({action, action2}, 2);

        _currentBehaviour = Behaviour({
            rep, b
        });

        //        Behaviour beh ({
        //            rep, b
        //        });
        //        beh.execute();

        _currentBehaviour.execute();
        delete action;
        delete action2;
        delete b;
        delete rep;
    }
}

//void Robot::executeActions()
//{
//    this->updateStatus();
//}

void Robot::stop()
{
    for (auto & m : _motors)
    {
        m.second.stop();
    }

    _receiveQueue->push(Message(0, 0, 0, Message::ABORT));
}

//RobotStatus & Robot::getRobotStatus()
//{
//    return _status;
//}

bool Robot::checkDevices()
{
    _sensors.clear();
    _motors.clear();

    // Check input devices.
    for (auto & input : INPUTS)
    {
        auto ultrasonic_sensor = ev3dev::ultrasonic_sensor(input);
        if (ultrasonic_sensor.connected())
        {
            _sensors.insert({input, ultrasonic_sensor});
            continue;
        }

        auto touch_sensor = ev3dev::touch_sensor(input);
        if (touch_sensor.connected())
        {
            _sensors.insert({input, touch_sensor});
            continue;
        }

        auto color_sensor = ev3dev::color_sensor(input);
        if (color_sensor.connected())
        {
            _sensors.insert({input, color_sensor});
            continue;
        }

        auto gyro_sensor = ev3dev::gyro_sensor(input);
        if (gyro_sensor.connected())
        {
            _sensors.insert({input, gyro_sensor});
            continue;
        }

        auto infrared_sensor = ev3dev::infrared_sensor(input);
        if (infrared_sensor.connected())
        {
            _sensors.insert({input, infrared_sensor});
            continue;
        }

        auto sound_sensor = ev3dev::sound_sensor(input);
        if (sound_sensor.connected())
        {
            _sensors.insert({input, sound_sensor});
            continue;
        }

        auto light_sensor = ev3dev::light_sensor(input);
        if (light_sensor.connected())
        {
            _sensors.insert({input, light_sensor});
            continue;
        }
    }

    // Check output devices.
    for (auto & output : OUTPUTS)
    {
        auto largeMotor = ev3dev::large_motor(output);
        if (largeMotor.connected())
        {
            _motors.insert({output, largeMotor});
            continue;
        }

        auto mediumMotor = ev3dev::medium_motor(output);
        if (mediumMotor.connected())
        {
            _motors.insert({output, mediumMotor});
            continue;
        }
    }

    // Check required devices.
    unsigned int ready = _requiredDevices.size();
    for (auto & device : _requiredDevices)
    {
        for (auto & mapping : _motors)
        {
            if ((mapping.first == device.first || device.first == PORT_ANY) &&
                mapping.second.type_name() == device.second)
            {
                updateCountPerRot(mapping.second.count_per_rot());

                --ready;
                continue;
            }
        }

        for (auto & mapping : _sensors)
        {
            if ((mapping.first == device.first || device.first == PORT_ANY) &&
                mapping.second.type_name() == device.second)
            {
                --ready;
                continue;
            }
        }
    }

    return !ready;
}

//void Robot::updateStatus()
//{
//    for (auto & sensor : _sensors)
//    {
//        for (unsigned int i = 0; i < sensor.second.num_values(); ++i)
//        {
//            _status.values[sensor.first][i] = std::make_pair(sensor.second.value(i), sensor.second.decimals());
//        }
//    }
//}


