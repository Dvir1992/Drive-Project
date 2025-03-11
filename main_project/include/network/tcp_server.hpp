#ifndef __TCPSERVER__HPP
#define __TCPSERVER__HPP

#include "socket.hpp"
#include <memory>
#include <string>

class TCPServer : public Socket 
{
    public:
        TCPServer();
        void Bind(int port);
        void Listen(int backlog);
        void AcceptConnection();
        int GetDataFd() const;
        void ReceiveMessage(std::shared_ptr<uint8_t[]> buffer, uint64_t size, uint32_t flags);
        void SendMessage(std::shared_ptr<uint8_t[]> buffer, uint64_t size); 
        ~TCPServer();
    private:
        int client_fd;
};

#endif // __TCPSERVER__HPP