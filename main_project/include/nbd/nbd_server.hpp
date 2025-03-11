#ifndef __NBDSERVER__HPP
#define __NBDSERVER__HPP
#include <thread>
#include <cstdint>
#include "keys.hpp"
#include "tcp_client.hpp"

class NBDServer
{
    public:
        explicit NBDServer();
        void Server();
        static int handle_read(void *buf, u_int32_t len, u_int64_t offset, void *userdata);//why static? to get down the imlicit this argument
        static int handle_write(const void *buf, u_int32_t len, u_int64_t offset, void *userdata);//why static? to get down the imlicit this argument
        NBDServer(const NBDServer& other_) = delete;
        NBDServer& operator=(const NBDServer& other_) = delete;
        ~NBDServer() = default;
    private:
        std::thread m_thread;
        static TCPClient tcp_client;//why static? to let the static functions use it.
};
#endif // __NBDSERVER__HPP