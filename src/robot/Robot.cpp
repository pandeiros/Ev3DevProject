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
#include "Master.h"

using namespace ev3;

Robot::Robot() { }

Robot::Robot(Devices::RequiredDevices devices, AvailableActions actions)
: _requiredDevices(devices), _availableActions(actions) { }

Robot::~Robot()
{
    delete _state;
}

std::thread Robot::createThread(Queue<Message> * sendQueue, Queue<Message> * receiveQueue)
{
    return std::thread([ = ]{run(sendQueue, receiveQueue);});
}

void Robot::run(Queue<Message> * sendQueue, Queue<Message> * receiveQueue)
{
    _sendQueue = sendQueue;
    _receiveQueue = receiveQueue;

    bool devicesChecked = true;
    devicesChecked = Devices::getInstance()->checkDevices(_requiredDevices);
    if (!devicesChecked)
    {
        // EXCEPTION
        std::cout << "Nop...\n";
    }
    else
        std::cout << "Devices correct.\n";


    _currentMessage = receiveQueue->pop();
    while (true)
    {
        if (_currentMessage.getType() == Message::AGENT_OVER ||
            _currentMessage.getType() == Message::MASTER_OVER)
            break;

        processState();

        processMessage();

        //processBehaviour(msg);

        //Devices::getInstance()->update();

        //respond();

        if (!receiveQueue->empty() || _currentMessage.getType() != Message::EMPTY)
            _currentMessage = receiveQueue->pop();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

    return;

//    if (devicesChecked)
//    {
//        auto motorLeft = Devices::getInstance()->getMotor(ev3dev::OUTPUT_B);
//        auto motorRight = Devices::getInstance()->getMotor(ev3dev::OUTPUT_C);
//
//        //auto us = _sensors.at(ev3dev::INPUT_1);
//
//        //std::cout << us.type_name() << "  " << us.num_values() << "  " << us.decimals() << "\n";
//
//        ActionDriveDistance * action = new ActionDriveDistance(500);
//        action->setCommands({
//            new CommandMotorReset(motorLeft),
//            new CommandMotorSetSpeedRegEnabled(motorLeft, true),
//            new CommandMotorSetSpeed(motorLeft, 400),
//            new CommandMotorRunForever(motorLeft),
//            new CommandMotorReset(motorRight),
//            new CommandMotorSetSpeedRegEnabled(motorRight, true),
//            new CommandMotorSetSpeed(motorRight, 400),
//            new CommandMotorRunForever(motorRight)
//        });
//
//        action->setEndCondition([&]()-> bool
//        {
//            return std::abs(motorLeft.getMotor().position()) > action->getDistance() * _pulsePerUnitRatio;
//        });
//
//        ActionRotate * action2 = new ActionRotate(180);
//        action2->setCommands({
//            new CommandMotorReset(motorLeft),
//            new CommandMotorSetSpeedRegEnabled(motorLeft, true),
//            new CommandMotorSetSpeed(motorLeft, 200),
//            new CommandMotorRunForever(motorLeft),
//            new CommandMotorReset(motorRight),
//            new CommandMotorSetSpeedRegEnabled(motorRight, true),
//            new CommandMotorSetSpeed(motorRight, -200),
//            new CommandMotorRunForever(motorRight)
//        });
//
//        action2->setEndCondition([&]()-> bool
//        {
//            return std::abs(motorLeft.getMotor().position()) > action2->getRotation() * _pulsePerUnitRatio;
//        });
//
//        Action * b = new Action({
//            new CommandMotorStop(motorLeft),
//            new CommandMotorStop(motorRight)
//        });
//
//        ActionRepeat * rep = new ActionRepeat({action, action2}, 2);
//
//        _currentBehaviour = Behaviour({
//            rep, b
//        });
//
//        //        Behaviour beh ({
//        //            rep, b
//        //        });
//        //        beh.execute();
//
//        _currentBehaviour.execute();
//        delete action;
//        delete action2;
//        delete b;
//        delete rep;
//    }
}

void Robot::processState()
{
    if (_currentMessage.getType() != Message::EMPTY && _currentMessage.getSenderId() == MASTER_ID)
        _state->updateTimer();

    _state = _state->process(_currentMessage);

    // End of work.
    if (_state->getPendingMessage() == Message::AGENT_OVER)
    {
        _receiveQueue->push(Message(0, 0, 0, Message::AGENT_OVER,{}));
        return;
    }

    if (_state->getPendingMessage() != Message::EMPTY)
    {
        Message message(_id == 0 ? std::rand() : _id,
                MASTER_ID,
                _commId++,
                _state->getPendingMessage(),
                {
                });

        _sendQueue->push(message);
    }
}

void Robot::sendInfo() {

 }

void Robot::processMessage()
{
    unsigned int id = _currentMessage.getSenderId();
    if (id == MASTER_ID && _commId < _currentMessage.getMessageId())
    {
        _commId = _currentMessage.getMessageId();
    }

    if (_currentMessage.getType() == Message::MASTER)
    {
        _id = _currentMessage.getReceiverId();
    }
}

void Robot::stop()
{
    Devices::getInstance()->stopAllDevices();
    _ledControl.endFlashing();

    _receiveQueue->push(Message(0, 0, 0, Message::ABORT));
}
