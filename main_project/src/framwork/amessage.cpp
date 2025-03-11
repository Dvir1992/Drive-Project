#include "iostream"
#include "amessage.hpp"

AMessage::AMessage(int32_t key,uint64_t size, const Uid& uid):m_key(key), m_size(size), m_uid(uid) 
{

}

uint8_t* AMessage::ToBuffer(uint8_t *p) 
{
    *(int32_t*)p = m_key;
    p += sizeof(int32_t);

    *(uint64_t*)p = m_size;
    p += sizeof(uint64_t);

    p = m_uid.ToBuffer(p);
    return p;
}

uint8_t* AMessage::FromBuffer(uint8_t* p)
{
    m_key = *(int32_t*)p;
    p += sizeof(int32_t);
    
    m_size = *(uint64_t*)p;
    p += sizeof(uint64_t);

    p = m_uid.FromBuffer(p);
    return p;
}

uint64_t AMessage::GetBufferSize() const
{
    return sizeof(int32_t) +  sizeof(uint64_t) + m_uid.GetBufferSize();
}

uint32_t AMessage::GetKey() const
{
    return m_key;
}

uint64_t AMessage::GetSize() const
{
    return m_size;
}

const Uid& AMessage::GetUid() const
{
    return m_uid;
}

uint8_t AMessage::IsSuccess() const //does nothing
{
    return 0;
}

std::shared_ptr<uint8_t[]> AMessage::GetData()
{
    //handle it later
    return nullptr;
}

void AMessage::Print_Object() const 
{
    std::cout<<"key is: "<<m_key<<std::endl;
    std::cout<<"size is: "<<m_size<<std::endl;
    m_uid.Print_Object();
}


AMessage::~AMessage()
{
    
}