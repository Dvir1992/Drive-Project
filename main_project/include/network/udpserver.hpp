#ifndef __UDP__SERVER__HPP
#define __UDP__SERVER__HPP

#include "socket.hpp"
#include <arpa/inet.h>
#include <memory>
using namespace std;
class UDPServer : public Socket 
{
public:
    UDPServer(int port);
    void ReceiveData(shared_ptr<uint8_t[]> buffer, uint64_t bufferSize, int flag);
    void RespondToClient(shared_ptr<uint8_t[]> buffer, uint64_t bufferSize);

private:
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t clientlen;
};

#endif //__UDP__SERVER__HPP