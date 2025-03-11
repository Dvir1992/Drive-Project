#include <iostream>
#include "writemessage.hpp"

Writemessage:: Writemessage(int32_t key, uint64_t size, const Uid &uid, uint64_t offset, std::shared_ptr<uint8_t[]> buffer):
AMessage(key, size, uid), m_offset(offset), m_buffer(buffer) 
{
    
}

uint8_t* Writemessage::ToBuffer(uint8_t* p) 
{
    p = AMessage::ToBuffer(p);

    *(int64_t*)p = m_offset;
    p += sizeof(int64_t);

    std::memcpy(p, m_buffer.get(), m_size);
    p += m_size;    

    return p;
}

uint8_t* Writemessage::FromBuffer(uint8_t* p)
{
    p = AMessage::FromBuffer(p);

    m_offset = *(int64_t*)p;
    p += sizeof(int64_t);
    if(!m_buffer)
    {
        m_buffer = std::shared_ptr<uint8_t[]>(new uint8_t[m_size]);
    }
    std::memcpy(m_buffer.get(), p, m_size);
    p += m_size;

    return p;
}

uint64_t Writemessage::GetOffset()
{
    return m_offset;
}

 std::shared_ptr<uint8_t[]> Writemessage::GetData()
 {
    return m_buffer;
 }

uint64_t Writemessage::GetBufferSize() const
{
    return AMessage::GetBufferSize() + sizeof(uint64_t) + m_size;
}

void Writemessage::Print_Object() const
{
    AMessage::Print_Object();
    std::cout<<"offset is: "<<m_offset<<std::endl;
    std::cout<<"data is: ";
    for(size_t i = 0; i < m_size; ++i)
    {
        std::cout<< *(m_buffer.get() + i);
    }
    std::cout<<std::endl;
}