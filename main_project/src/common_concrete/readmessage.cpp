#include <iostream>
#include "readmessage.hpp"

Readmessage:: Readmessage(int32_t key, uint64_t size, const Uid &uid, uint64_t offset):
AMessage(key, size, uid),m_offset(offset)
{
    
}

uint8_t* Readmessage::ToBuffer(uint8_t* p) 
{
    p = AMessage::ToBuffer(p);

    *(uint64_t*)p = m_offset;
    p += sizeof(uint64_t);

    return p;
}

uint8_t* Readmessage::FromBuffer(uint8_t* p)
{
    p = AMessage::FromBuffer(p);

    m_offset = *(uint64_t*)p;
    p += sizeof(uint64_t);

    return p;
}

uint64_t Readmessage::GetBufferSize() const
{
    return AMessage::GetBufferSize() + sizeof(uint64_t);
}

uint64_t Readmessage::GetOffset()
{
    return m_offset;
}


void Readmessage::Print_Object() const
{
    AMessage::Print_Object();
    std::cout<<"offset is: "<<m_offset<<std::endl;
}