#pragma once

#include "CommUtils.h"
#include "RobotState.h"
#include "Message.h"
#include "Behaviour.h"

namespace ev3
{
    /**
     * @class Agent
     * Master-side representative of a robot unit.
     * Lacks all device references and action execution.
     */
    class Agent
    {
    public:
        /**
         * Agent id getter.
         * @return Id given by Master.
         */
        unsigned int getId();
        
        /**
         * Agent id setter.
         * @param id New id for this Agent.
         */
        void setId(const unsigned int id);

        /**
         * Current communication id getter.
         * @return Id of Message id synchronised between Agent and Robot.
         */
        unsigned int getCommId();
        
        /**
         * Communication id setter.
         * @param commId New communication id.
         */
        void setCommId(const unsigned int commId);
        
        /**
         * Process received Message to produce response.
         * @param message Message to be analyzed.
         * @param retMessage Modified Message to be sent to Robot.
         */
        void processMessage(Message * message, Message * retMessage);
        
        /**
         * Update data concerning last message sent.
         * @param message Last Message sent to corresponding Robot.
         */
        void updateLastMessage(Message * message);
        
        /**
         * Set currently executing Behaviour.
         * @param behaviour Behaviour shared_ptr object.
         */
        void setBehaviour(SharedPtrBehaviour behaviour);
        
        /**
         * Set measurements that must be done on corresponding Robot.
         * @param measurements Vector of Sensor types.
         */
        void setMeasurement(Measurements measurements);
        
    private:
        /// Currently active Behaviour.
        SharedPtrBehaviour _currentBehaviour;
        
        /// Vector with Sensor types. These Sensors measure values
        /// that are sent to the master.
        Measurements _measurements;
        
        /// Current state of the corresponding Robot.
        RobotState::States _state = RobotState::IDLE;
        
        /// Assigned Agent id.
        unsigned int _id;
        
        /// Message id.
        unsigned int _commId = 0;
        
        /// Type of the last Message sent.
        Message::MessageType _lastMessageType;
    };
}