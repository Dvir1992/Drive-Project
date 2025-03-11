#include <iostream>
#include <cstring>
#include <memory>
#include <arpa/inet.h>
#include "singleton.hpp"
#include "factory.hpp"
#include "nbdproxy.hpp"
#include "nbd_server.hpp"
#include "nbd_request.hpp"
#include "responsereadmessage.hpp"
#include "responsewritemessage.hpp"
#include "buse.h"



#define DEVICE_SIZE (12 * 1024 * 1024) // 12MB virtual storage
#define IP "10.1.0.173"
#define PORT 7074
TCPClient NBDServer::tcp_client;

NBDServer::NBDServer():m_thread(std::thread(&NBDServer::Server, this))
{

    
}


int NBDServer::handle_read(void *buf, u_int32_t len, u_int64_t offset, void *userdata) 
{
    (void)userdata;
    std::cout<<"\nHELLO NBDSERVER::READ\n";
    std::shared_ptr<uint8_t[]> data_buffer(new uint8_t[len]);
    memset(data_buffer.get(),'\0', len);
    NBDRequest req(R, len, data_buffer, offset);
    cout<<"NBD Request Data Object To send: \n";
    req.Print_Object();
    cout<<"***************************************************\n";
    std::shared_ptr<uint8_t[]> request_buffer(new uint8_t[req.GetBufferSize()]);
    req.ToBuffer(request_buffer.get());
    tcp_client.SendMessage(request_buffer.get(), req.GetBufferSize());
    //cout<<"***************************************************\n";

    std::shared_ptr<uint8_t[]> response_buffer(new uint8_t[sizeof(KEY)+ sizeof(uint64_t)]);
    tcp_client.ReceiveMessage(response_buffer.get(), sizeof(KEY)+sizeof(uint64_t), MSG_PEEK);
    //cout<<"***************************************************\n";
    KEY key = *(KEY*)(response_buffer.get());
    uint64_t msg_size = *(uint64_t*)(response_buffer.get() + sizeof(KEY));
    response_buffer.reset();
    std::shared_ptr<AMessage> msg = Singleton<Factory<KEY,std::shared_ptr<AMessage>, uint64_t>>::GetInstance()->Create(key, msg_size); 
    response_buffer = std::shared_ptr<uint8_t[]>(new uint8_t[msg->GetBufferSize()]);
    tcp_client.ReceiveMessage(response_buffer.get(), msg->GetBufferSize(), 0);
    //cout<<"***************************************************\n";
    msg->FromBuffer(response_buffer.get());
    cout<<"Read: NBD response Data Object recieved from NBDproxy: \n";
    msg->Print_Object();
    cout<<"***************************************************\n";
    
    memcpy(buf, msg->GetData().get(), len);

    tcp_client.ReceiveMessage(response_buffer.get(), msg->GetBufferSize(), 0);
    //cout<<"***************************************************\n";
    msg->FromBuffer(response_buffer.get());
    cout<<"Read mirrored: NBD response Data Object recieved from NBDproxy: \n";
    msg->Print_Object();

    cout<<"***************************************************\n";
    std::cout<<"finished handle read\n";
    cout<<"***************************************************\n";

    return 0;
}

int NBDServer::handle_write(const void *buf, u_int32_t len, u_int64_t offset, void *userdata) 
{
    (void)userdata;
    std::cout<<"\nHELLO NBDSERVER::Write\n";
    std::shared_ptr<uint8_t[]> data_buffer(new uint8_t[len]);
    memset(data_buffer.get(),'\0', len);
    memcpy(data_buffer.get(),buf,len);

    NBDRequest req(W, len, data_buffer, offset);
    cout<<"NBD Request Data Object To send: \n";
    req.Print_Object();
    cout<<"***************************************************\n";
    std::shared_ptr<uint8_t[]> request_buffer(new uint8_t[req.GetBufferSize()]);
    req.ToBuffer(request_buffer.get());
    tcp_client.SendMessage(request_buffer.get(), req.GetBufferSize());
    //cout<<"***************************************************\n";

    std::shared_ptr<uint8_t[]> response_buffer(new uint8_t[sizeof(KEY)+ sizeof(uint64_t)]);
    tcp_client.ReceiveMessage(response_buffer.get(), sizeof(KEY)+sizeof(uint64_t), MSG_PEEK);
    cout<<"***************************************************\n";
    KEY key = *(KEY*)(response_buffer.get());
    uint64_t msg_size = *(uint64_t*)(response_buffer.get() + sizeof(KEY));
    response_buffer.reset();
    std::shared_ptr<AMessage> msg = Singleton<Factory<KEY,std::shared_ptr<AMessage>, uint64_t>>::GetInstance()->Create(key, msg_size); 
    response_buffer = std::shared_ptr<uint8_t[]>(new uint8_t[msg->GetBufferSize()]);
    tcp_client.ReceiveMessage(response_buffer.get(), msg->GetBufferSize(), 0);
    cout<<"***************************************************\n";
    msg->FromBuffer(response_buffer.get());
    cout<<"Write: NBD response Data Object recieved from NBDproxy:\n";
    msg->Print_Object();
    cout<<"***************************************************\n";

    tcp_client.ReceiveMessage(response_buffer.get(), msg->GetBufferSize(), 0);
    cout<<"***************************************************\n";
    msg->FromBuffer(response_buffer.get());
    cout<<"Write mirrored: NBD response Data Object recieved from NBDproxy: \n";
    msg->Print_Object();

    cout<<"***************************************************\n";
    std::cout<<"finished handle write\n";
    cout<<"***************************************************\n";
    
    return 0;
}



void NBDServer::Server() 
{
    tcp_client.Connect(IP, PORT);
    //std::shared_ptr<uint8_t[]> data_buffer(new uint8_t[4096]); //for no nbd example
    //handle_read(data_buffer.get(), 4096, 0 , nullptr); // for no nbd example
   // handle_write(data_buffer.get(), 4096, 0 , nullptr); // for no nbd example
    //sleep(1);//for prints order
    struct buse_operations ops = {};
    ops.size = DEVICE_SIZE;
    ops.read = handle_read;
    ops.write = handle_write;
    
    try 
    {
        std::cout << "Starting NBD Server..." << std::endl;
        cout<<"***************************************************\n\n";

        int ret = buse_main("/dev/nbd5", &ops, NULL);
        if (ret < 0) 
        {
            throw std::runtime_error("Failed to start the NBD server");
        }
    } 
    catch (const std::exception &e) 
    {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
    } 
    catch (...) 
    {
        std::cerr << "Unknown error occurred." << std::endl;
    }
}
