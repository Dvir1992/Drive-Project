#ifndef __NBDPROXY__HPP
#define __NBDPROXY__HPP
#include <thread>
#include <memory>
#include <mutex>
#include <semaphore.h>
#include <condition_variable>
#include "iinputproxy.hpp"
#include "nbd_request.hpp"
#include "tcp_server.hpp"
#include "amessage.hpp"

class NBDProxy : public IInputproxy
{
    public:
        explicit NBDProxy();
        std::shared_ptr<IArgs> GetArgsTask(fd_item) override;
        int GetFd() const;
        NBDProxy(const NBDProxy& other_) = delete;
        NBDProxy& operator=(const NBDProxy& other_) =  delete;
        void NotifySuccess(std::shared_ptr<AMessage> msg, uint64_t size);
        ~NBDProxy() override = default;
    private:
        TCPServer tcp_server;
};
#endif // __NBDPROXY_HPP