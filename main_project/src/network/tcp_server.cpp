#include "tcp_server.hpp"
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>


TCPServer::TCPServer() : Socket(AF_INET, SOCK_STREAM) {}

void TCPServer::Bind(int port) 
{ 
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    int optval = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
    {
        close(sockfd);
        throw std::runtime_error("Failed to set SO_REUSEADDR option");
    }
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) 
    {
        close(sockfd);
        throw std::runtime_error("Failed to bind socket");

    }
}

void TCPServer::Listen(int backlog) 
{    
    if (listen(sockfd, backlog) == -1) 
    {
        close(sockfd);
        throw std::runtime_error("Failed to listen on socket");
    }
    std::cout << "Server is listening..." << std::endl;
}

void TCPServer::AcceptConnection() 
{
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    client_fd = accept(sockfd, (struct sockaddr*)&client_addr, &client_addr_len);
    if (client_fd == -1) 
    {
        close(sockfd);
        close(client_fd);
        throw std::runtime_error("Failed to accept connection");
    }
    std::cout << "Client connected" << std::endl;
}

void TCPServer::ReceiveMessage(std::shared_ptr<uint8_t[]> buffer, uint64_t size, uint32_t flags) 
{
    std::memset(buffer.get(), 0, size); 
    ssize_t received = recv(client_fd, buffer.get(), size, flags);
    if (received == -1) 
    {
        close(sockfd);
        close(client_fd);
        throw std::runtime_error("Failed to receive message");
    }
    //std::cout<<"tcp server - num of bytes recieved: "<<received<<std::endl;
}

void TCPServer::SendMessage(std::shared_ptr<uint8_t[]> buffer, uint64_t size) 
{
    ssize_t sent = send(client_fd, buffer.get(), size, 0);
    if (sent == -1) 
    {
        close(sockfd);
        close(client_fd);
        throw std::runtime_error("Failed to send message");
    }
    std::memset(buffer.get(), 0, size); 
    //std::cout<<"tcp server - num of bytes sent: "<<sent<<std::endl;
}

int TCPServer::GetDataFd() const
{
    return client_fd;
}

 TCPServer::~TCPServer()
{
    close(client_fd);
}