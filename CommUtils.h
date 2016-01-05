#pragma once

#include "Message.h"
#include <string>

namespace ev3
{
    static unsigned int DEFAULT_PORT = 12345;
    static unsigned int MAX_PACKET_LENGTH = 4096;

    class CommUtils
    {
    public:

        struct Sender
        {
            unsigned int port;
            std::string ipAddress;
        };

        int preparePassiveSocket(unsigned int portNumber);
        int sendBroadcastMessage(unsigned int socket, unsigned int port, Message message);
        int receiveMessage(unsigned int socket, Message & msg, Sender & sender);

    private:

        struct Buffer
        {
            void * buffer;
            size_t size;
        };

        Buffer prepareBuffer(const std::string msg);
        std::string encodeMessage(Message & message);
        Message decodeMessage(const Buffer buffer);
    };
}


