#include "minionproxy.hpp"
#include "writemessage.hpp"
#include "readmessage.hpp"
#include "keys.hpp"
#include <iostream>
MinionProxy::MinionProxy(int port, const std::string& ipAddres):client(ipAddres.c_str(), port)
{

}

void MinionProxy::Write(std::shared_ptr<uint8_t[]> data, uint64_t size, const Uid &uid, uint64_t offset)
{
    Writemessage w_msg(W, size, uid, offset, data);
    std::shared_ptr<uint8_t[]> message(new uint8_t[w_msg.GetBufferSize()]);
    w_msg.ToBuffer(message.get());
    //std::cout<<"Hello from MinionProxy::Write\n";
    //cout<<"***************************************************\n";   
    client.SendData(message, w_msg.GetBufferSize());
    //cout<<"***************************************************\n";
}

void MinionProxy::Read(uint64_t size, const Uid &uid, uint64_t offset)
{
    Readmessage r_msg(R, size, uid, offset);
    std::shared_ptr<uint8_t[]> message(new uint8_t[r_msg.GetBufferSize()]);
    r_msg.ToBuffer(message.get());
    //std::cout<<"Hello from MinionProxy::Read\n";
    //cout<<"***************************************************\n";    
    client.SendData(message, r_msg.GetBufferSize());
    //cout<<"***************************************************\n";

}




