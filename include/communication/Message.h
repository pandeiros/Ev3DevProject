#pragma once

#include "Utils.h"

#include <vector>
#include <string>

/**
 * @file Message.h
 * Contains Message class.
 */

namespace ev3
{
    /// Default Message delimiter between parts of encoded message string.
    static const char MESSAGE_DELIM = ':';

    /**
     * @class Message
     * Stores information passed between physical system units (another
     * robots or master).
     */
    class Message
    {
    public:

        /**
         * Messge Type
         */
        enum MessageType
        {
            EMPTY, /**< Empty message, no meaning. */
            ACK, /**< Accept previously received request. */
            NOT, /**< Deny previously received request. */
            AGENT, /**< Agent side synchronization. */
            MASTER, /**< Master side synchronization. */
            MASTER_OVER, /**< Master work finished. */
            PING, /**< Connection sustain request. */
            PONG, /**< Connection sustain answer. */
            AGENT_OVER, /**< Agent work finished. */
            ABORT, /**< Exit processing now. */
            BEHAVIOUR, /**< Behaviour definition received. */
            START, /**< Behaviour start. */
            RESUME, /**< Behaviour resume. */
            PAUSE, /**< Behaviour pause. */
            ACTION_OK, /**< Action finished correctly. */
            ACTION_INTERR, /**< Action interrupted. */
            SENSOR_VALUE, /**< Sensor measurement occured. */
            MEASURE /**< Instructions what to measure. */
        };

        /**
         * Default constructor.
         */
        Message();

        /**
         * Full message constructor.
         * @param senderId  Id of the sender (given by master).
         * @param receiverId Id of the receiver.
         * @param messageId Consequently incremented message id.
         * @param type Predefined Message type.
         * @param parameters Vector of additional, optional string parameters.
         */
        Message(unsigned int senderId, unsigned int receiverId, unsigned int messageId, MessageType type, StringVector parameters = {});

        /**
         * Sender id getter.
         * @return Id of the message sender (should be set to the value of
         * the main class executing this method). 
         */
        unsigned int getSenderId();

        /**
         * Receiver id getter.
         * @return Id of the message receiver.
         */
        unsigned int getReceiverId();

        /**
         * Consequently incremented integer id getter.
         * @return Id of the message.
         */
        unsigned int getMessageId();

        /**
         * Message type getter.
         * @return Enum value with Message type.
         */
        MessageType getType();

        /**
         * Message parameters getter.
         * @return String vector with all optional parameters.
         */
        StringVector getParameters();

        /**
         * Sender id setter.
         * @param id Id of the message sender (should be set to the value of
         * the main class executing this method). 
         */
        void setSenderId(unsigned int id);

        /**
         * Receiver id setter.
         * @param id Id of the message receiver.
         */
        void setReceiverId(unsigned int id);

        /**
         * Consequently incremented integer id setter.
         * @param id Id of the message.
         */
        void setMessageId(unsigned int id);

        /**
         * Message type setter.
         * @param type Enum value with Message type.
         */
        void setType(MessageType type);

        /**
         * Message parameters setter.
         * @param parameters String vector with all optional parameters.
         */
        void setParameters(StringVector parameters);

        /**
         * Tell whether Message type is EMPTY.
         * @return True if Messge is EMPTY, false otherwise.
         */
        bool empty();

        /**
         * Human-readable name getter.
         * @return Formatted string containing name and all parameters.
         */
        std::string getString();

        /**
         * Encode message data into string.
         * @param message Reference to message object to be encoded.
         * @return String with encoded data of the message.
         */
        static std::string encodeMessage(Message & message);

        /**
         * Decode string into Message object.
         * @param message String value to be decoded.
         * @return Message object decoded, if processed successfully.
         */
        static Message decodeMessage(const std::string message);

        /**
         * Reset all values to default ones and type to EMPTY.
         */
        void reset();

    private:
        /**
         * Human-readable Message type name (mainly for logging).
         * @return String with Message type name.
         */
        std::string getStringType();

        /// Message id.
        unsigned int _id;

        /// Message sender id.
        unsigned int _sender;

        /// Message receiver id.
        unsigned int _receiver;

        /// Message type.
        MessageType _type = EMPTY;

        /// Vector with all optional parameters.
        StringVector _parameters;
    };
}
