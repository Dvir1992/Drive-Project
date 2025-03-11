#include <iostream>
#include <cstring>
#include "responsereadmessage.hpp"

ResponseReadmessage:: ResponseReadmessage(int32_t key, uint64_t size, const Uid &uid, std::shared_ptr<uint8_t[]> buffer, uint8_t status):
AMessage(key, size, uid), m_buffer(buffer),m_status(status)
{
    
}

uint8_t* ResponseReadmessage::ToBuffer(uint8_t* p) 
{
    p = AMessage::ToBuffer(p);
    std::memcpy(p, m_buffer.get(), m_size);
    p += m_size;

    *(uint8_t*)p = m_status;
    p += sizeof(uint8_t);
    
    return p;
}

uint8_t* ResponseReadmessage::FromBuffer(uint8_t* p)
{
    p = AMessage::FromBuffer(p);
    if(!m_buffer)
    {
        m_buffer = std::shared_ptr<uint8_t[]>(new uint8_t[m_size]);
    }
    std::memcpy(m_buffer.get(),p, m_size);
    p += m_size;
    
    m_status = *(uint8_t*)p;
    p += sizeof(uint8_t);



    return p;
}

uint64_t ResponseReadmessage::GetBufferSize() const
{
    return AMessage::GetBufferSize() + m_size + sizeof(uint8_t);
}

std::shared_ptr<uint8_t[]> ResponseReadmessage::GetData()
{
    return m_buffer;
}

uint8_t ResponseReadmessage::IsSuccess() const
{
    return m_status;
}


void ResponseReadmessage::Print_Object() const
{
    AMessage::Print_Object();
    std::cout<<"status is: "<<m_status<<std::endl;
    std::cout<<"data is: ";
    for(size_t i = 0; i < m_size; ++i)
    {
        std::cout<< *(m_buffer.get() + i);
    }
    std::cout<<std::endl;
    
}