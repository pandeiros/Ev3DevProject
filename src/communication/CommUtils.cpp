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

CommUtils::CommUtils()
: _packetBuffer(CircularBuffer<std::string>(DEFAULT_PACKET_BUFFER_LIMIT)) { }

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

int CommUtils::sendMessage(unsigned int socket, unsigned int port, Message & message, std::string & proto, bool isMaster, unsigned int repeat)
{
    int result = -1;

    if (isMaster)
    {
        NetworkNode receiver;
        if (_remotes.find(message.getReceiverId()) != _remotes.end())
            receiver = _remotes[message.getReceiverId()];
        else if (message.getType() == Message::MASTER && _unregisteredRemotes.size() > 0)
        {
            receiver = _unregisteredRemotes.front();
            _unregisteredRemotes.pop();
        }
        else
            return -1;

        for (unsigned int i = 0; i < repeat; ++i)
        {
            int tempResult = sendMessageTo(socket, receiver.ipAddress, receiver.port, proto);
            if (result < 0)
                result = tempResult;
        }
    }
    else
    {
        int result;
        for (unsigned int i = 0; i < repeat; ++i)
        {
            int tempResult;
            if (_remotes.find(MASTER_ID) != _remotes.end())
                tempResult = sendMessageTo(socket, _remotes[MASTER_ID].ipAddress, _remotes[MASTER_ID].port, proto);
            else
                tempResult = sendBroadcastMessage(socket, port, proto);

            if (result < 0)
                result = tempResult;
        }
    }

    return result;
}

int CommUtils::sendBroadcastMessage(unsigned int socket, unsigned int port, std::string message)
{
    Buffer buffer = getBufferFromString(message);

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

int CommUtils::sendMessageTo(unsigned int socket, std::string ipAddress, unsigned int destinationPort, std::string message)
{
    Buffer buffer = getBufferFromString(message);

    struct sockaddr_in addr;
    if (makeSockAddr(ipAddress, destinationPort, &addr) < 0)
    {
        return -1;
    }

    int return_code = sendto(socket, buffer.buffer, buffer.size, 0, (struct sockaddr*) &addr, sizeof (addr));
    free(buffer.buffer);

    return return_code;
}

int CommUtils::receiveMessage(unsigned int socket, Message& message, NetworkNode & sender)
{
    Buffer buffer;
    buffer.buffer = malloc(MAX_PACKET_LENGTH);
    struct sockaddr_in sender_addr;
    socklen_t addr_len = sizeof (sender_addr);
    int return_code = recvfrom(socket, buffer.buffer, MAX_PACKET_LENGTH, 0, (struct sockaddr*) &sender_addr, (socklen_t*) & addr_len);

    if (return_code < 0)
    {
        free(buffer.buffer);
        return -1;
    }

    buffer.size = return_code;
    std::string proto = getStringFromBuffer(buffer);
    
    if (_packetBuffer.contain(proto))
    {
        free(buffer.buffer);
        return -1;
    }
    
    message = Message::decodeMessage(proto);
    _packetBuffer.push(proto);

    char * ipAddress = (char*) malloc(INET_ADDRSTRLEN);
    if (inet_ntop(AF_INET, &(sender_addr.sin_addr), ipAddress, (socklen_t) INET_ADDRSTRLEN) == NULL)
    {
        free(buffer.buffer);
        return -2;
    }
    sender.ipAddress = std::string(ipAddress);
    sender.port = ntohs(sender_addr.sin_port);

    if (!message.empty() && message.getType() != Message::AGENT)
        _remotes[message.getSenderId()] = sender;

    if (message.getType() == Message::AGENT)
        _unregisteredRemotes.push(sender);

    free(buffer.buffer);

    return return_code;
}

int CommUtils::receiveMessageDelay(unsigned int socket, Message& message, NetworkNode& sender, unsigned int delay)
{
    Buffer buffer;
    buffer.buffer = malloc(MAX_PACKET_LENGTH);
    struct sockaddr_in sender_addr;
    socklen_t addr_len = sizeof (sender_addr);

    struct timeval tv;
    tv.tv_sec = delay / 1000;
    tv.tv_usec = delay % 1000 * 1000;
    setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, (char *) &tv, sizeof (struct timeval));

    int return_code = recvfrom(socket, buffer.buffer, MAX_PACKET_LENGTH, 0, (struct sockaddr*) &sender_addr, (socklen_t*) & addr_len);
    if (return_code < 0)
    {
        free(buffer.buffer);
        return -1;
    }

    buffer.size = return_code;
    std::string proto = getStringFromBuffer(buffer);
    
    if (_packetBuffer.contain(proto))
        return -1;
    
    message = Message::decodeMessage(proto);
    _packetBuffer.push(proto);

    char * ipAddress = (char*) malloc(INET_ADDRSTRLEN);
    if (inet_ntop(AF_INET, &(sender_addr.sin_addr), ipAddress, (socklen_t) INET_ADDRSTRLEN) == NULL)
    {
        free(buffer.buffer);
        return -2;
    }
    sender.ipAddress = std::string(ipAddress);
    sender.port = ntohs(sender_addr.sin_port);

    if (!message.empty() && message.getType() != Message::AGENT)
        _remotes[message.getSenderId()] = sender;

    if (message.getType() == Message::AGENT)
        _unregisteredRemotes.push(sender);

    free(buffer.buffer);

    return return_code;
}

int CommUtils::makeSockAddr(std::string ipAddress, int portNumber, sockaddr_in * sockaddr)
{
    struct sockaddr_in addr;
    memset((char*) &addr, 0, sizeof (addr));

    if (inet_pton(AF_INET, ipAddress.c_str(), &(addr.sin_addr)) != 1)
    {
        return -1;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(portNumber);
    *sockaddr = addr;

    return 0;
}

CommUtils::Buffer CommUtils::getBufferFromString(std::string message)
{
    Buffer result;
    void* buffer;
    size_t size;

    size = strlen(message.c_str()) + 1;
    buffer = malloc(size);
    memcpy(buffer, message.c_str(), size);

    result.buffer = buffer;
    result.size = size;

    return result;
}

std::string CommUtils::getStringFromBuffer(const Buffer buffer)
{
    char* c_str = (char*) malloc(buffer.size);
    strcpy(c_str, (char*) buffer.buffer);

    return std::string(c_str);
}