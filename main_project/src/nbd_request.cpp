#include <cstring>
#include "iostream"
#include "nbd_request.hpp"

NBDRequest::NBDRequest(KEY key, uint64_t size, std::shared_ptr<u_int8_t[]> buffer, u_int64_t offset):
                        m_key(key), m_size(size), m_buffer(buffer), m_offset(offset)
{

}

uint8_t* NBDRequest::ToBuffer(uint8_t *p) 
{
    *(KEY*)p = m_key;
    p += sizeof(int32_t);

    *(uint64_t*)p = m_size;
    p += sizeof(uint64_t);

    memcpy(p, m_buffer.get(), m_size);
    p += m_size;

    *(uint64_t*)p = m_offset;
    p += sizeof(uint64_t);

    return p;
}

uint8_t* NBDRequest::FromBuffer(uint8_t* p)
{
    m_key = *(KEY*)p;
    p += sizeof(KEY);

    m_size = *(uint64_t*)p;
    p += sizeof(uint64_t);

    if(!m_buffer)
    {
        m_buffer = std::shared_ptr<uint8_t[]>(new uint8_t[m_size]);
    }
    memcpy(m_buffer.get(), p, m_size);
    p += m_size;

    m_offset = *(uint64_t*)p;
    p += sizeof(uint64_t);

    return p;
}

uint64_t NBDRequest::GetBufferSize() const
{
    return sizeof(KEY) + sizeof(uint64_t) + m_size + sizeof(uint64_t);
}

KEY NBDRequest::GetKey() const
{
    return m_key;
}

uint64_t NBDRequest::GetSize() const
{
    return m_size;
}

std::shared_ptr<u_int8_t[]> NBDRequest::GetData() const
{
    return m_buffer;
}

uint64_t NBDRequest::GetOffset() const
{
    return m_offset;
}




void NBDRequest::Print_Object() const 
{
    std::cout<<"key is: "<<m_key<<std::endl;
    std::cout<<"size is: "<<m_size<<std::endl;
    std::cout<<"data is: ";
    for(size_t i = 0; i < m_size; ++i)
    {
        std::cout<< *(m_buffer.get() + i);
    }
    std::cout<<std::endl;
    std::cout<<"offset is: "<<m_offset<<std::endl;
}
