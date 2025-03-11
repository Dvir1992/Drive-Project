#include <iostream>
#include <memory>
#include <cstring>
#include <netinet/in.h>
#include "nbdproxy.hpp"
#include "nbd_server.hpp"
#include "singleton.hpp"
#include "w_args.hpp"
#include "r_args.hpp"


NBDProxy::NBDProxy()
{
    tcp_server.Bind(7074);
    tcp_server.Listen(1);
    Singleton<NBDServer>::GetInstance();
    tcp_server.AcceptConnection();
    cout<<"***************************************************\n";
}

std::shared_ptr<IArgs> NBDProxy::GetArgsTask(fd_item item)
{
    (void)item;  
    //std::cout<<"HELLO NBDProxy::GetArgsTask\n";
    std::shared_ptr<uint8_t[]> buffer(new uint8_t[sizeof(KEY)+sizeof(uint64_t)]);
    tcp_server.ReceiveMessage(buffer,sizeof(KEY)+sizeof(uint64_t), MSG_PEEK);
    uint64_t msg_size = *(uint64_t*)(buffer.get() + sizeof(KEY));
    NBDRequest req(R ,msg_size);

    buffer.reset();
    buffer =  std::shared_ptr<uint8_t[]>(new uint8_t[req.GetBufferSize()]);
    //cout<<"***************************************************\n";    
    tcp_server.ReceiveMessage(buffer,req.GetBufferSize(), 0);
    req.FromBuffer(buffer.get());
    // cout<<"***************************************************\n";    
    // std::cout<<"Accepted NBD request in NBDProxy: \n";
    // req.Print_Object();
    // cout<<"***************************************************\n";    

    if(req.GetKey() == W)
    {       
        return std::make_shared<W_args>(req.GetData(), req.GetSize(), req.GetOffset());
    }
    else
    {
    
        return std::make_shared<R_args>(req.GetSize(), req.GetOffset());
    }
}

void NBDProxy::NotifySuccess(std::shared_ptr<AMessage> msg, uint64_t size)
{
    std::shared_ptr<uint8_t[]> buffer(new uint8_t[size]);
    memset(buffer.get(), 0, sizeof(buffer));
    msg->ToBuffer(buffer.get());
    //std::cout<<"Hello from NBDProxy::NotifySuccess: \n";
    tcp_server.SendMessage(buffer, size);
    //cout<<"***************************************************\n"; 
    //std::cout<<"HELLO NBDSERVER::READ After Recieveing\n";
}

int NBDProxy::GetFd() const
{
    return tcp_server.GetDataFd();
}

