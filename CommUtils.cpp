#include "CommUtils.h"

#include <sys/socket.h>
#include <netinet/ip.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include <sstream>

using namespace ev3;

int CommUtils::preparePassiveSocket(unsigned int portNumber)
{
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        return -1;
    }

    int broadcast = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST,
        &broadcast, sizeof (broadcast)) < 0)
    {
        return -1;
    }

    struct sockaddr_in addr;
    memset((char*) &addr, 0, sizeof (addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(portNumber);
    if (bind(sockfd, (struct sockaddr*) &addr, sizeof (addr)) < 0)
    {
        return -1;
    }

    return sockfd;
}

int CommUtils::sendBroadcastMessage(unsigned int socket, unsigned int port, Message message)
{
    Buffer buffer = prepareBuffer(encodeMessage(message));

    struct ifaddrs* interfaces;
    if (getifaddrs(&interfaces) == -1)
    {
        return -1;
    }

    int max_return_code = -2;
    int some_failed = 0;

    for (struct ifaddrs* interface = interfaces; interface != NULL; interface = interface->ifa_next)
    {
        if (interface->ifa_addr == NULL)
        {
            continue;
        }

        if (interface->ifa_addr->sa_family == AF_INET && interface->ifa_flags & IFF_BROADCAST)
        {
            struct sockaddr_in* addr = (struct sockaddr_in*) interface->ifa_ifu.ifu_broadaddr;
            addr->sin_port = htons(port);

            int return_code = sendto(socket, buffer.buffer, buffer.size, 0, (struct sockaddr*) addr, sizeof (*addr));
            if (return_code < 0)
            {
                some_failed = 1;
            }
            if (return_code > max_return_code)
            {
                max_return_code = return_code;
            }
        }
    }

    free(buffer.buffer);
    freeifaddrs(interfaces);

    if (max_return_code <= -1)
    {
        return -2;
    }
    if (some_failed == 1)
    {
        return -1;
    }

    return max_return_code;
}

int CommUtils::receiveMessage(unsigned int socket, Message& msg, Sender& sender)
{
    Buffer buffer;
    buffer.buffer = malloc(MAX_PACKET_LENGTH);
    struct sockaddr_in sender_addr;
    socklen_t addr_len = sizeof (sender_addr);
    int return_code = recvfrom(socket, buffer.buffer, MAX_PACKET_LENGTH, 0, (struct sockaddr*) &sender_addr, (socklen_t*) & addr_len);

    if (return_code < 0)
    {
        return -1;
    }

    buffer.size = return_code;
    msg = decodeMessage(buffer);

    char * ipAddress = (char*) malloc(INET_ADDRSTRLEN);
    if (inet_ntop(AF_INET, &(sender_addr.sin_addr), ipAddress, (socklen_t) INET_ADDRSTRLEN) == NULL)
    {
        return -1;
    }
    sender.ipAddress = std::string(ipAddress);
    sender.port = ntohs(sender_addr.sin_port);

    free(buffer.buffer);
    return return_code;
}

CommUtils::Buffer CommUtils::prepareBuffer(std::string msg)
{
    Buffer result;
    void* buffer;
    size_t size;

    size = strlen(msg.c_str()) + 1;
    buffer = malloc(size);
    memcpy(buffer, msg.c_str(), size);

    result.buffer = buffer;
    result.size = size;
    return result;
}

std::string CommUtils::encodeMessage(Message& message)
{
    std::string msg = "";
    msg += std::to_string(message.getId());
    msg += ":";
    msg += std::to_string(message.getType());
    msg += ":";
    for (auto & s : message.getParameters())
        msg += s + ":";

    return msg;
}

Message CommUtils::decodeMessage(const Buffer buffer)
{
    Message message(0, Message::PING,{"Test", "Testing...."});

    char* c_str = (char*) malloc(buffer.size);
    strcpy(c_str, (char*) buffer.buffer);

    std::string str(c_str);

    std::vector<std::string> params;
    std::istringstream f(c_str);
    std::string s;
    while (std::getline(f, s, ':'))
        params.push_back(s);

    std::cout << str << "\n";

    return message;
}


