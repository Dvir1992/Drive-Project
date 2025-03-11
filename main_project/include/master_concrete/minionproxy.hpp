#ifndef _MINION_PROXY_HPP__
#define _MINION_PROXY_HPP__
#include <memory>
#include <cstdint>
#include <string>
#include "iminion.hpp"
#include "udpclient.hpp"

class MinionProxy: public IMinion
{
    public:
        MinionProxy(int port, const std::string& ipAddres);
        ~MinionProxy() override = default;
        void Read(uint64_t size, const Uid &uid, uint64_t offset) override;
        void Write(std::shared_ptr<uint8_t[]> data, uint64_t size, const Uid &uid, uint64_t offset) override;
    private:
        UDPClient client;
};

#endif //_MINION_PROXY_H__
