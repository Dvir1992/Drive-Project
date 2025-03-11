#ifndef _MASTER_PROXY_HPP__
#define _MASTER_PROXY_HPP__
#include <memory>
#include <fstream>
#include <unordered_map>
#include "fd_item_hash.hpp"
#include "iinputproxy.hpp"
#include "amessage.hpp"
#include "udpserver.hpp"
#include "udpclient.hpp"


class MasterProxy: public IInputproxy
{
    public:
        explicit MasterProxy(const string & disk_path, int port);
        std::shared_ptr<IArgs> GetArgsTask(fd_item) override;
        MasterProxy(const MasterProxy& other_) = delete;
        MasterProxy& operator=(const MasterProxy& other_) =  delete;
        void ReadResponse(shared_ptr<uint8_t[]> ,uint64_t, uint8_t);
        void WriteResponse(uint8_t);
        int GetFd() const;
        fstream& GetDisk();
        ~MasterProxy() override;
    private:
        shared_ptr<AMessage> msg;
        fstream m_disk;
        UDPServer m_server; 
        UDPClient m_client;  
};

#endif //_MINION_PROXY_H__
