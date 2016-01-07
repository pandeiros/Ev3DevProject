#pragma once

#include "Message.h"
#include "CircularBuffer.h"
#include <string>
#include <netinet/in.h>
#include <map>
#include <queue>

namespace ev3
{
    static const unsigned int DEFAULT_PORT = 12345;
    static const unsigned int MAX_PACKET_LENGTH = 4096;
    static const unsigned int DEFAULT_RECEIVE_DELAY = 1; // In milliseconds.
    static const unsigned int MASTER_ID = 1;
    static const unsigned int SENT_MESSAGE_COPIES = 5;
    static const unsigned int DEFAULT_PACKET_BUFFER_LIMIT = 50;

    class CommUtils
    {
    public:
        CommUtils();

        struct NetworkNode
        {
            unsigned int port;
            std::string ipAddress;
        };

        int preparePassiveSocket(unsigned int portNumber);

        int sendMessage(unsigned int socket, unsigned int port, Message message, bool isMaster, unsigned int repeat = SENT_MESSAGE_COPIES);

        int receiveMessage(unsigned int socket, Message & msg, NetworkNode & sender);
        int receiveMessageDelay(unsigned int socket, Message & msg, NetworkNode & sender, unsigned int msDelay = DEFAULT_RECEIVE_DELAY);

    private:

        struct Buffer
        {
            void * buffer;
            size_t size;
        };

        int sendBroadcastMessage(unsigned int socket, unsigned int port, Message message);
        int sendMessageTo(unsigned int socket, std::string ipAddress, unsigned int destinationPort, Message message);

        int makeSockAddr(std::string ipAddress, int portNumber, struct sockaddr_in * sockaddr);
        Buffer getBufferFromString(const std::string msg);
        std::string getStringFromBuffer(const Buffer buffer);

        std::map<unsigned int, NetworkNode> _remotes;
        std::queue<NetworkNode> _unregisteredRemotes;
        
        CircularBuffer<std::string> _packetBuffer;
    };
}


