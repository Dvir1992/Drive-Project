#include "udpserver.hpp"
#include "iostream"
#include "cstring"
#include <unistd.h>

UDPServer::UDPServer(int port): Socket(AF_INET, SOCK_DGRAM), clientlen(sizeof(clientaddr)) 
{
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = INADDR_ANY;  // Bind to any address
    serveraddr.sin_port = htons(port);        // Bind to the specified port
    int optval = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
    {
        close(sockfd);
        throw std::runtime_error("Failed to set SO_REUSEADDR option");
    }
    if (bind(sockfd, (const struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0) 
    {
        close(sockfd);
        throw std::runtime_error("Bind failed");
    }
    std::cout << "UDP Server listening on port" << port << std::endl;
}

void UDPServer::ReceiveData(std::shared_ptr<uint8_t[]> buffer, uint64_t bufferSize, int flag) 
{
    memset(buffer.get(), 0, bufferSize);
    int bytes_recieved = recvfrom(sockfd, buffer.get(), bufferSize, flag, (struct sockaddr*)&clientaddr, &clientlen);
    if (bytes_recieved < 0) 
    {
        close(sockfd);
        throw std::runtime_error("server - recvfrom failed");
    }
    //std::cout<<"udp server - num of bytes recieved: "<<bytes_recieved<<std::endl;
}

void UDPServer::RespondToClient(std::shared_ptr<uint8_t[]> buffer, uint64_t bufferSize) 
{
    int bytes_sent = sendto(sockfd, buffer.get(), bufferSize, 0, (const struct sockaddr*)&clientaddr, clientlen); 
    if (bytes_sent < 0) 
    {
        close(sockfd);
        throw std::runtime_error("server - sendto failed");
    }
    //std::cout << "udp server - num of bytes sent: " << bytes_sent<< std::endl;
}