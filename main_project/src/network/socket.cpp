#include "socket.hpp"
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
Socket::Socket(int domain, int type)
{
    sockfd = socket(domain, type, 0);
    if (sockfd < 0) 
    {
         throw std::runtime_error("Socket creation failed");
    }
}

int Socket::GetSock() const 
{
    return sockfd;
}
Socket::~Socket()
{
    close(sockfd);
}
