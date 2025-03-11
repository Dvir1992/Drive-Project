#include "responseproxy.hpp"
#include "responsereadmessage.hpp"
#include "responsewritemessage.hpp"
#include "singleton.hpp"
#include "factory.hpp"
#include "response_manager.hpp"
#include "nbdproxy.hpp"

#define MASTER_PORT 7073

#include <cstdlib>

ResponseProxy::ResponseProxy():r_server(MASTER_PORT)
{
    cout<<"***************************************************\n";
}

std::shared_ptr<IArgs> ResponseProxy::GetArgsTask(fd_item item) 
{
    (void)item;
    //std::cout<<"HELLO ResponseProxy::GetArgsTask\n";
    //cout<<"***************************************************\n";
    
    std::shared_ptr<uint8_t[]> buffer(new uint8_t[sizeof(KEY)+ sizeof(uint64_t)]);
    r_server.ReceiveData(buffer,sizeof(KEY)+sizeof(uint64_t), MSG_PEEK);
    //cout<<"***************************************************\n";
    KEY key = *(KEY*)(buffer.get());
    uint64_t msg_size = *(uint64_t*)(buffer.get() + sizeof(KEY));
    buffer.reset();
    msg = Singleton<Factory<KEY,std::shared_ptr<AMessage>, uint64_t>>::GetInstance()->Create(key, msg_size); 

    buffer = std::shared_ptr<uint8_t[]>(new uint8_t[msg->GetBufferSize()]);

    r_server.ReceiveData(buffer, msg->GetBufferSize(), 0);
    //cout<<"***************************************************\n";
    msg->FromBuffer(buffer.get()); 
    //std::cout<<"Accepted Message in ResponseProxy: \n";
    //msg->Print_Object(); 
    //cout<<"***************************************************\n";

    Singleton<ResponseManager>::GetInstance()->RegisterResponse(msg->GetUid(),msg->IsSuccess());

    Singleton<NBDProxy>::GetInstance()->NotifySuccess(msg, msg->GetBufferSize());

    return nullptr;
}

int ResponseProxy::GetFd() const
{
    return r_server.GetSock();
}