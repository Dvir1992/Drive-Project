#include "tcp_client.hpp"
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

TCPClient::TCPClient() : Socket(AF_INET, SOCK_STREAM) 
{

}

void TCPClient::Connect(const std::string &ip, int port) 
{
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr);

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) 
    {
        close(sockfd);
        throw std::runtime_error("Failed to connect to server");

    }
}

void TCPClient::SendMessage(uint8_t* buffer, uint64_t size) 
{
    ssize_t sent = send(sockfd, buffer, size, 0);
    if (sent == -1) 
    {
        close(sockfd);
        throw std::runtime_error("Failed to send message");
    }
    std::memset(buffer, 0, size); 

    //std::cout<<"tcp client - num of sent bytes: "<<sent<<std::endl;
}

void TCPClient::ReceiveMessage(uint8_t* buffer, uint64_t size, uint32_t flag) 
{
    std::memset(buffer, 0, size); 
    ssize_t received = recv(sockfd, buffer, size , flag);
    if (received == -1) 
    {
        close(sockfd);
        throw std::runtime_error("Failed to receive message");
    }
    //std::cout<<"tcp client - num of recieved: "<<received<<std::endl; 
}
