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
#include "Logger.h"

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
    //    _currentBehaviour.reset();

    _state->getBehaviour().reset();

    bool devicesChecked = true;
    devicesChecked = Devices::getInstance()->checkDevices(_requiredDevices);
    if (!devicesChecked)
    {
        // EXCEPTION
        Logger::getInstance()->log("Devices incorrect!", Logger::ERROR);
        stop();
        return;
    }
    else
        Logger::getInstance()->log("Devices correct.", Logger::INFO);

    // TEST ====================
    //        _state->getBehaviour()->setMeasurements({Sensor::ULTRASONIC});

    //    generateBehaviour(_currentBehaviour, Behaviour::DRIVE_ON_SQUARE,
    //            StringVector({"400", "1"}));
    //
    //    while (true)
    //    {
    //        if (_currentBehaviour.get() != nullptr)
    //            _currentBehaviour->process();
    //        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    //    }
    //    return;
    // =========================

    _currentMessage = receiveQueue->pop();
    while (true)
    {
        if (_currentMessage.getType() != Message::EMPTY)
            Logger::getInstance()->log(AGENT_RECEIVE + _currentMessage.getString(), Logger::VERBOSE);

        if (_currentMessage.getType() == Message::AGENT_OVER ||
            _currentMessage.getType() == Message::MASTER_OVER)
            break;

        Devices::getInstance()->update();

        processMessage();

        processState();

        processEvents();

        ping();

        //        processBehaviour();

        //respond();

        if (!receiveQueue->empty() || _currentMessage.getType() != Message::EMPTY)
            _currentMessage = receiveQueue->pop();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    stop();

    return;
}

void Robot::processState()
{
    if (_currentMessage.getType() != Message::EMPTY && _currentMessage.getSenderId() == MASTER_ID)
        _state->updateTimer();

    _state = _state->process(_currentMessage);

    //std::cout << "ROBOT STATE " << _state->getBehaviour().get() << "\n";

    Message::MessageType pending = _state->getPendingMessage();
    bool allowed = _state->isPendingEnabled();

    // End of work.
    if (pending == Message::AGENT_OVER)
    {
        _receiveQueue->push(Message(0, 0, 0, Message::AGENT_OVER,{}));
        return;
    }

    if (pending != Message::EMPTY && allowed)
    {

        Message message(_id == 0 ? std::rand() % 1000000 : _id,
                MASTER_ID,
                _commId++,
                pending, { });


        _sendQueue->push(message);
        Logger::getInstance()->log(AGENT_SEND + message.getString(), Logger::VERBOSE);
    }
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
        Logger::getInstance()->log("New ID aqcuired: " + std::to_string(_id), Logger::INFO);
    }

    if (_currentMessage.getType() == Message::MEASURE)
    {
        Measurements m;
        for (auto & s : _currentMessage.getParameters())
            m.push_back(static_cast<Sensor::SensorType> (transcode<int>(s)));

        _state->getBehaviour()->setMeasurements(m);
    }

    // Replace behaviour with a new one.
    if (_currentMessage.getType() == Message::BEHAVIOUR)
    {
        try
        {
            Logger::getInstance()->log("Obtaining Behaviour parameters...", Logger::VERBOSE);
            StringVector parameters = _currentMessage.getParameters();

            if (parameters.size() == 0)
            {
                // TODO Generate Event instead.

                Logger::getInstance()->log("Behaviour parameters incorrect!", Logger::WARNING);
                return;
            }

            _behaviourSet = false;
            unsigned int t = transcode<unsigned int>(parameters[0]);
            Behaviour::BehaviourType type = static_cast<Behaviour::BehaviourType> (t);

            // Predefined Behaviour
            if (type != Behaviour::CUSTOM)
            {
                Logger::getInstance()->log("Loading predefined Behaviour: " + std::to_string(type), Logger::INFO);
                SharedPtrBehaviour behaviour = generateBehaviour(type,
                        StringVector(parameters.begin() + 1, parameters.end()));
                _state->setBehaviour(behaviour);

                if (_state->getBehaviour().get() == nullptr || _state->getBehaviour() == nullptr)
                {
                    send(Message(_id, MASTER_ID, 0, Message::NOT,{}));
                }
                else
                {
                    send(Message(_id, MASTER_ID, 0, Message::ACK,{}));
                }
            }
            else
            {
                Logger::getInstance()->log("Loading custom Behaviour...", Logger::VERBOSE);
                // Custom behaviour creation.
            }
        }
        catch (...)
        {
            // TODO

            Logger::getInstance()->log("Processing Behaviour failed!", Logger::ERROR);
        }
    }
}

void Robot::processEvents()
{
    while (!EventQueue::getInstance()->empty())
    {
        SharedPtrEvent event = EventQueue::getInstance()->pop();

        switch (event->getType())
        {
            case Event::BEHAVIOUR_START:
                _state->getBehaviour()->start();
                break;
            case Event::BEHAVIOUR_STOP:
                _state->getBehaviour().reset();
                break;
            case Event::OBSTACLE_DETECTED:
                _state->getBehaviour()->react(event->getType());
                break;
            case Event::PROXIMITY_ALERT:
                _state->getBehaviour()->react(event->getType());
                break;
            case Event::SENSOR_WATCH:
                send(Message(_id, MASTER_ID, 0, Message::SENSOR_VALUE,
                        Sensor::prepareMessage(
                        static_cast<EventSensorWatch*> (event.get())->getValue(),
                        static_cast<EventSensorWatch*> (event.get())->getType())));
                break;

            case Event::ACTION_FINISHED:
                send(Message(_id, MASTER_ID, 0, Message::ACTION_OK,{std::to_string(static_cast<EventAction*> (event.get())->getActionType())}));
                break;
            case Event::ACTION_INTERR:
                send(Message(_id, MASTER_ID, 0, Message::ACTION_INTERR,{std::to_string(static_cast<EventAction*> (event.get())->getActionType())}));
                break;
            default:
                break;
        }
    }
}

void Robot::send(Message message)
{

    message.setMessageId(_commId++);
    Logger::getInstance()->log(AGENT_SEND + message.getString(), Logger::VERBOSE);

    _sendQueue->push(message);
}

std::string Robot::getString()
{

    return "<Base class Robot>";
}

SharedPtrBehaviour Robot::generateBehaviour(Behaviour::BehaviourType type, StringVector parameters)
{

    return std::shared_ptr<Behaviour>(nullptr);
}

void Robot::sendInfo() { }

void Robot::stop()
{

    Devices::getInstance()->stopAllDevices();
    _ledControl.endFlashing();

    _receiveQueue->push(Message(0, 0, 0, Message::AGENT_OVER));
    _sendQueue->push(Message(0, 0, 0, Message::AGENT_OVER));
}

void Robot::ping()
{
    if (DurationMilli(HighResClock::now() - _masterPingTime).count() >= RobotState::MASTER_PING_TIME)
    {
        send(Message(_id, MASTER_ID, 0, Message::PING,{}));
        _masterPingTime = HighResClock::now();
    }
}

