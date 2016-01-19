#include "Robot.h"
#include "ColorUtils.h"
#include <unistd.h>
#include <iostream>
#include <functional>
#include <future>
#include "ev3dev.h"

#include "Behaviour.h"
#include "Agent.h"
#include "EventQueue.h"
#include "Event.h"

using namespace ev3;

Robot::Robot() { }

Robot::Robot(Devices::RequiredDevices devices, AvailableActions actions)
: _requiredDevices(devices), _availableActions(actions) { }

Robot::~Robot() { }

std::thread Robot::createThread(Queue<Message> * sendQueue, Queue<Message> * receiveQueue)
{
    return std::thread([ = ]{run(sendQueue, receiveQueue);});
}

void Robot::run(Queue<Message> * sendQueue, Queue<Message> * receiveQueue)
{
    _sendQueue = sendQueue;
    _receiveQueue = receiveQueue;
    
    std::cout << _requiredDevices[0].first << " " << _requiredDevices[0].second << "\n";

    bool devicesChecked = Devices::getInstance()->checkDevices(_requiredDevices);
    if (!devicesChecked)
    {
        // EXCEPTION
        std::cout << "Nop...\n";
    }
    else
        std::cout << "Devices correct.\n";

    Message agentMsg(std::rand(), MASTER_ID, _commId++, Message::AGENT, { });

    sendQueue->push(agentMsg);

    bool stop = false;

    Message msg = receiveQueue->pop();
    while (!stop)
    {
        state = state->process(Message(std::rand(), MASTER_ID, _commId++, std::rand() % 2 == 0 ? Message::MASTER : Message::MASTER_OVER, { }));
//        state = state->process(msg);
        
        if (msg.getType() == Message::MASTER_OVER)
            break;

        if (msg.getType() == Message::MASTER)
        {
            _id = msg.getReceiverId();
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
            _sendQueue->push(Message(_id, MASTER_ID, _commId++, Message::PING,{}));

        if (msg.empty())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));

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

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));

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

    if (devicesChecked)
    {
        auto motorLeft = Devices::getInstance()->getMotor(ev3dev::OUTPUT_B);
        auto motorRight = Devices::getInstance()->getMotor(ev3dev::OUTPUT_C);

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
            return std::abs(motorLeft.getMotor().position()) > action->getDistance() * _pulsePerUnitRatio;
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
            return std::abs(motorLeft.getMotor().position()) > action2->getRotation() * _pulsePerUnitRatio;
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
    Devices::getInstance()->stopAllDevices();

    _receiveQueue->push(Message(0, 0, 0, Message::ABORT));
}
