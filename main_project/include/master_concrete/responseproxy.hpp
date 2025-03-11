#ifndef __RESPONSEPROXY__HPP
#define __RESPONSEPROXY__HPP
#include <memory>
#include <amessage.hpp>
#include "iinputproxy.hpp"
#include "udpserver.hpp"
#include "fd_item_hash.hpp"

class ResponseProxy : public IInputproxy
{
    public:
        explicit ResponseProxy();
        std::shared_ptr<IArgs> GetArgsTask(fd_item) override;
        ResponseProxy(const ResponseProxy& other_) = delete;
        ResponseProxy& operator=(const ResponseProxy& other_) =  delete;
        int GetFd() const;
        ~ResponseProxy() override = default;
    private:
        UDPServer r_server;
        shared_ptr<AMessage> msg;
};
#endif // __RESPONSEPROXY_HPP