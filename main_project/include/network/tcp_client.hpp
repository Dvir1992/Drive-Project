#ifndef __TCPCLIENT__HPP
#define __TCPCLIENT__HPP

#include "socket.hpp"
#include <cstdint> 
#include <string>

class TCPClient : public Socket 
{
    public:
        TCPClient();
        void Connect(const std::string &ip, int port);
        void SendMessage(uint8_t* buffer, uint64_t size)  ;
        void ReceiveMessage(uint8_t* buffer, uint64_t size, uint32_t flag) ;
};

#endif // __TCPCLIENT__HPP