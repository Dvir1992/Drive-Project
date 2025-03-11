#ifndef __SOCKET__HPP
#define __SOCKET__HPP

class Socket 
{
    public:
        Socket(int domain, int type);
        int GetSock() const;
        virtual ~Socket();
    protected:
        int sockfd;
};
#endif // __SOCKET__HPP