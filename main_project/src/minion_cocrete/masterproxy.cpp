#include "masterproxy.hpp"
#include "writemessage.hpp"
#include "readmessage.hpp"
#include "responsewritemessage.hpp"
#include "responsereadmessage.hpp"
#include "m_w_args.hpp"
#include "m_r_args.hpp"
#include "factory.hpp"
#include "singleton.hpp"

#define RESPONSE_PORT 7073 
#define RESPONSE_MASTER_IP "10.1.0.173" 
#define MINION_SIZE (8 * 1024 * 1024) // 8MB storage

MasterProxy::MasterProxy(const string & disk_path, int port):m_disk(disk_path.c_str(), ios::in | ios::out | ios::binary),
                                                             m_server(port),
                                                             m_client(RESPONSE_MASTER_IP, RESPONSE_PORT)
{
   if (!m_disk) 
   {
      cerr << "Failed to open file." << std::endl;
   }   
   char zero = '\0';
   for(uint64_t i = 0; i < MINION_SIZE; ++i)
   {
      m_disk.write(&zero, 1);
   } // we should handle the case where every time the minion falls we save the data, but we dont care about it right now.
   m_disk.seekp(0, std::ios::beg);
   if (!m_disk)
    {
        cerr << "Failed to write to file." << std::endl;
        
    }
}
std::shared_ptr<IArgs> MasterProxy:: GetArgsTask(fd_item item)
{
   (void)item;
   //std::cout<<"HELLO MasterProxy::GetArgsTask\n";
   //cout<<"***************************************************\n";   
   std::shared_ptr<uint8_t[]> buffer(new uint8_t[sizeof(KEY)+ sizeof(uint64_t)]);
   m_server.ReceiveData(buffer,sizeof(KEY)+sizeof(uint64_t), MSG_PEEK);
   //cout<<"***************************************************\n"; 
   KEY key = *(KEY*)(buffer.get());
   uint64_t msg_size = *(uint64_t*)(buffer.get() + sizeof(KEY));
   buffer.reset();
   msg = Singleton<Factory<KEY,std::shared_ptr<AMessage>, uint64_t>>::GetInstance()->Create(key, msg_size); 

   buffer = std::shared_ptr<uint8_t[]>(new uint8_t[msg->GetBufferSize()]);

   m_server.ReceiveData(buffer, msg->GetBufferSize(), 0);
   //cout<<"***************************************************\n"; 
   msg->FromBuffer(buffer.get());
   //std::cout<<"Accepted Message in MasterProxy: \n";
   //msg->Print_Object(); 
   //cout<<"***************************************************\n";    

   if(msg->GetKey() == W) 
   {
      shared_ptr<Writemessage> w_msg =std::dynamic_pointer_cast<Writemessage>(msg);
      return std::make_shared<MW_args>(w_msg->GetData(), w_msg->GetSize(), w_msg->GetOffset(),this);
   }
   else 
   {
      shared_ptr<Readmessage> r_msg =std::dynamic_pointer_cast<Readmessage>(msg);
      return std::make_shared<MR_args>(r_msg->GetSize(), r_msg->GetOffset(),this);
   }
    
}

 int MasterProxy::GetFd() const
 {
    return m_server.GetSock();
 }

 fstream& MasterProxy::GetDisk() 
 {
    return m_disk;
 }

 MasterProxy::~MasterProxy()
 {
    m_disk.close();
 }

void MasterProxy::ReadResponse(shared_ptr<uint8_t[]> buffer,uint64_t size, uint8_t status) 
{
   cout<<"send bask read response\n";
   ResponseReadmessage r_res_msg(RR, size, msg->GetUid(), buffer, status);
   std::shared_ptr<uint8_t[]> message(new uint8_t[r_res_msg.GetBufferSize()]);
   r_res_msg.ToBuffer(message.get());
   m_client.SendData(message,r_res_msg.GetBufferSize());
   //cout<<"***************************************************\n";   
      
}

void MasterProxy::WriteResponse(uint8_t status)
{
   cout<<"send back write response\n";
   ResponseWritemessage w_res_msg(RW, 0, msg->GetUid(), status);
   std::shared_ptr<uint8_t[]> message(new uint8_t[w_res_msg.GetBufferSize()]);
   w_res_msg.ToBuffer(message.get());
   m_client.SendData(message,w_res_msg.GetBufferSize());
   //cout<<"***************************************************\n";   
}

