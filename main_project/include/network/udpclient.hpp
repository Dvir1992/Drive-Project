#ifndef __UDP__CLIENT__HPP
#define __UDP__CLIENT__HPP

#include "socket.hpp"
#include <arpa/inet.h>
#include <memory>
using namespace std;
class UDPClient : public Socket 
{
public:
    UDPClient(const char* serverIp, int serverPort);
    void SendData(shared_ptr<uint8_t[]>, uint64_t);
    void ReceiveData(std::shared_ptr<uint8_t[]>, uint64_t);

private:
    struct sockaddr_in serveraddr;
};

#endif//__UDP__CLIENT__HPP