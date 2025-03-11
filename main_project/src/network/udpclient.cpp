#include "udpclient.hpp"
#include "iostream"
#include "cstring"
#include <unistd.h>


UDPClient::UDPClient(const char* serverIp, int serverPort) : Socket(AF_INET, SOCK_DGRAM)
{
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(serverPort);

    if (inet_pton(AF_INET, serverIp, &serveraddr.sin_addr) <= 0) 
    {
        close(sockfd);
        throw std::runtime_error("Invalid server IP address");
    }
}

void UDPClient:: SendData(shared_ptr<uint8_t[]> buffer, uint64_t size) 
{
    int bytes_sent = sendto(sockfd, buffer.get(), size, 0, (const struct sockaddr*)&serveraddr, sizeof(serveraddr));
    if (bytes_sent < 0) 
    {
        close(sockfd);
        throw std::runtime_error("client - sendto failed");
    }
    //std::cout << "udp client - num of sent bytes: " << bytes_sent<< std::endl;
    std::memset(buffer.get(), 0, size);
}

void UDPClient::ReceiveData(std::shared_ptr<uint8_t[]> buffer, uint64_t size) 
{
    socklen_t serverLen = sizeof(serveraddr);
    std::memset(buffer.get(), 0, size); 
    int bytes_recieved = recvfrom(sockfd, buffer.get(), size, 0, (struct sockaddr*)&serveraddr, &serverLen);
    if (bytes_recieved < 0) 
    {
        close(sockfd);
        throw std::runtime_error("client - recvfrom failed"); 
    }
    //std::cout << "udp client - num of recieved bytes: " << bytes_recieved << std::endl;

}