#pragma once

#include "ev3dev.h"
#include "Action.h"
#include "Utils.h"
#include "Queue.h"
#include "LedControl.h"
#include "Devices.h"
#include "RobotState.h"

#include <vector>
#include <thread>

namespace ev3
{

    /**
     * @class Robot
     * Main class representing actual robot. Base class for all 
     * different Robot models. Aggregates RobotState, messages and Behaviour 
     * processing as well as information exchange with Communication thread.
     */
    class Robot
    {
    public:
        /// Type for specifying all available actions for given Robot model.
        typedef std::vector<Action::ActionType> AvailableActions;

        /**
         * Default constructor.
         */
        Robot();

        /**
         * Constructor with required devices and actions parameters.
         * @param devices Vector of mapped ports and devices types.
         * @param actions Vector with Action types executable by a particular robot.
         */
        Robot(Devices::RequiredDevices devices, AvailableActions actions);

        /**
         * Default destructor.
         */
        virtual ~Robot();

        /**
         * Thread creation method (instead of running Robot in main thread).
         * @param sendQueue Out Message queue.
         * @param receiveQueue In Message queue.
         * @return New std::thread object with Robot class active.
         */
        std::thread createThread(Queue<Message> * sendQueue, Queue<Message> * receiveQueue);

        /**
         * Starts Robot procedures.
         * @param sendQueue Out Message queue.
         * @param receiveQueue In Message queue.
         */
        virtual void run(Queue<Message> * sendQueue, Queue<Message> * receiveQueue);

        /**
         * Immediately stop Robot object and all assigned motors.
         */
        void stop();

        /**
         * General sending method for logging and assigning id.
         * @param message Message to be sent to Communication thread.
         */
        void send(Message message);

        /**
         * Human-readable Robot name getter.
         * @return String with Robot name.
         */
        virtual std::string getString();

    protected:
        /**
         * Generate behaviour based on its type and parameters.
         * @param type Behaviour type.
         * @param parameters Additional parameters required by a particular Behaviour.
         * @return New shared pointer with generated Behaviour object.
         */
        virtual SharedPtrBehaviour generateBehaviour(Behaviour::BehaviourType type, StringVector parameters);

        /// This Robot's id assigned by Master.
        unsigned int _id = 0;
        
        /// Communication id (assigned to messages).
        unsigned int _commId = 0;

        /// Number of rotation pulses per one distance unit.
        /// Calculated based on attached wheel circumference.
        float _pulsePerUnitRatio = 1.f;

        /// Vector of mapped ports and devices that are required.
        Devices::RequiredDevices _requiredDevices;

        /// Vector of executable Action types.
        AvailableActions _availableActions;

        /// Out Message queue.
        Queue<Message> * _sendQueue;

        /// In Message queue.
        Queue<Message> * _receiveQueue;

        /// Object controlling behaviour of LED diodes.
        LedControl _ledControl;

        // TODO Make it a smart pointer.
        /// Current Robot state.
        RobotState * _state = new RobotStateIdle(&_ledControl);

    private:
        /**
         * Process current Robot's state (which processes Behaviour).
         */
        void processState();

        /**
         * Process all Event objects from EventQueue.
         */
        void processEvents();

        /**
         * Interprets and process received Messages.
         */
        void processMessage();

        /**
         * Sends PING Message to master.
         */
        void ping();

        /// Control flag. True if Robot has any Behaviour 
        /// assigned, false otherwise.
        bool _behaviourSet = false;

        /// Last received Message.
        Message _currentMessage;

        /// Time since last PONG Message from Master.
        HighResClock::time_point _masterPingTime = HighResClock::now();

        /// Score of the Robot.
        unsigned int _score;
    };
}
