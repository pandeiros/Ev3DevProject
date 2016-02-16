#pragma once

#include "Message.h"
#include "CircularBuffer.h"
#include <string>
#include <netinet/in.h>
#include <map>
#include <queue>

/**
 * @file CommUtils.h
 * Contains CommUtils class.
 */

namespace ev3
{
    /// Default port number.
    static const unsigned int DEFAULT_PORT = 12345;

    /// Maximum packet size in bytes.
    static const unsigned int MAX_PACKET_LENGTH = 4096;

    /// Default time in milliseconds to wait for message (used by non-blocking receive method).
    static const unsigned int DEFAULT_RECEIVE_DELAY = 1; // In milliseconds.

    /// Default master id.
    static const unsigned int MASTER_ID = 1;

    /// Default number of copies to be sent every time (preventing packet loss).
    static const unsigned int SENT_MESSAGE_COPIES = 5;

    /// Maximum number of stored message prototypes (preventing duplicates).
    static const unsigned int DEFAULT_PACKET_BUFFER_LIMIT = 50;

    /**
     * @class CommUtils
     * Responsible for low-level communication. Uses socket API and UNIX
     * sending and receiving methods.
     */
    class CommUtils
    {
    public:
        /**
         * Default constructor.
         */
        CommUtils();

        /**
         * @struct NetworkNode
         * Stores information about a particular node in the network.
         */
        struct NetworkNode
        {
            /// Port number.
            unsigned int port;

            /// Node's ipv4 address.
            std::string ipAddress;
        };

        /**
         * Prepares socket for transmission on given port.
         * @param portNumber Port number to assign socket to.
         * @return Id of the socket assigned.
         */
        int preparePassiveSocket(unsigned int portNumber);

        /**
         * General method for sending messages.
         * @param socket Previously prepared socket.
         * @param port Number of port to communicate through.
         * @param message Message to be sent.
         * @param proto Message prototype passed to avoid its multiple encoding.
         * @param isMaster Flag from Communication class. True if master is the sender.
         * @param repeat Number of copies to be sent.
         * @return Error code or positive integer with number of bytes sent.
         */
        int sendMessage(unsigned int socket, unsigned int port, Message & message, std::string & proto, bool isMaster, unsigned int repeat = SENT_MESSAGE_COPIES);

        /**
         * General receive method.
         * @param socket Previously prepared socket.
         * @param message Message reference to be set after receiving.
         * @param sender NetworkNode to be set after receiving.
         * @return Error code or positive integer with number of bytes received.
         */
        int receiveMessage(unsigned int socket, Message & message, NetworkNode & sender);
        
        /**
         * General receive method with waiting delay.
         * @param socket Previously prepared socket.
         * @param message Message reference to be set after receiving.
         * @param sender NetworkNode to be set after receiving.
         * @param msDelay Maximum time in milliseconds to wait for message.
         * @return Error code or positive integer with number of bytes received.
         */
        int receiveMessageDelay(unsigned int socket, Message & message, NetworkNode & sender, unsigned int msDelay = DEFAULT_RECEIVE_DELAY);

    private:
        /**
         * @struct Buffer
         * Contains buffer and its size. Used by low-level methods.
         */
        struct Buffer
        {
            /// Pointer to allocated buffer.
            void * buffer;
            
            /// Size of bytes allocated.
            size_t size;
        };

        /**
         * Send message to all recipients in current network.
         * @param socket Previously prepared socket.
         * @param port Number of port to communicate through.
         * @param message Message to be sent.
         * @return Error code or positive integer with number of bytes sent.
         */
        int sendBroadcastMessage(unsigned int socket, unsigned int port, std::string message);
        
        /**
         * Send message to specific ipv4 address.
         * @param socket Previously prepared socket.
         * @param ipAddress String containing ipv4 address.
         * @param destinationPort Number of recipient port.
         * @param message Message to be sent.
         * @return Error code or positive integer with number of bytes sent.
         */
        int sendMessageTo(unsigned int socket, std::string ipAddress, unsigned int destinationPort, std::string message);

        /**
         * Prepares sockaddr_in structure.
         * @param ipAddress String containing ipv4 address.
         * @param portNumber Number of port to communicate.
         * @param sockaddr Structure to be set after calling.
         * @return Error code.
         */
        int makeSockAddr(std::string ipAddress, int portNumber, struct sockaddr_in * sockaddr);
        
        /**
         * Converts Message prototype to Buffer structure.
         * @param message String prototype to be converted.
         * @return Buffer object after memory allocation.
         */
        Buffer getBufferFromString(const std::string message);
        
        /**
         * Converts Buffer structure into Message prototype.
         * @param buffer Structure with allocated memory with data.
         * @return String with Message prototype.
         */
        std::string getStringFromBuffer(const Buffer buffer);

        /// Map used to register all acquired nodes in the network.
        std::map<unsigned int, NetworkNode> _remotes;
        
        /// Queue storing temporal information about not yet registered remotes (agents).
        std::queue<NetworkNode> _unregisteredRemotes;

        /// Circular buffer used to store limited number of 
        /// previous Message prototypes received.
        CircularBuffer<std::string> _packetBuffer;
    };
}


