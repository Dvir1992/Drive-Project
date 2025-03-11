
#include <iostream>
#include "responsewritemessage.hpp"

ResponseWritemessage:: ResponseWritemessage(int32_t key, uint64_t size, const Uid &uid, uint8_t status):
AMessage(key, size, uid), m_status(status)
{

}

uint8_t* ResponseWritemessage::ToBuffer(uint8_t* p)  
{
    p = AMessage::ToBuffer(p);

    *(uint8_t*)p = m_status;
    p += sizeof(uint8_t);

    return p;
}

uint8_t* ResponseWritemessage::FromBuffer(uint8_t* p)
{
    p = AMessage::FromBuffer(p);

    m_status = *(uint8_t*)p;
    p += sizeof(uint8_t);

    return p;
}

uint64_t ResponseWritemessage::GetBufferSize() const 
{
    return AMessage::GetBufferSize() +  sizeof(uint8_t);
}

uint8_t ResponseWritemessage::IsSuccess() const 
{
    return m_status;
}
 std::shared_ptr<uint8_t[]> ResponseWritemessage::GetData()
{
    //handle it later
    return nullptr;
}
void ResponseWritemessage::Print_Object() const 
{
    AMessage::Print_Object();
    std::cout<<"status is: "<<m_status<<std::endl;
}