#define _DEFAULT_SOURCE
#include <iostream>
#include "uid.hpp"

Uid::Uid():m_uid(UID_Generate()) 
{

}

uint8_t* Uid::ToBuffer(uint8_t* p) 
{
	*(size_t*)p = m_uid.counter;
    p += sizeof(size_t);

    *(time_t*)p = m_uid.timestamp;
    p += sizeof(time_t);

    *(pid_t*)p = m_uid.pid;
    p += sizeof(pid_t);

    *(long*)p = m_uid.ip;
    p += sizeof(long);
    return p;
}

uint8_t* Uid::FromBuffer(uint8_t* p)
{
	m_uid.counter = *(size_t*)p;
	p += sizeof(size_t);

	m_uid.timestamp = *(time_t*)p ;
    p += sizeof(time_t);

    m_uid.pid = *(pid_t*)p;
    p += sizeof(pid_t);

    m_uid.ip = *(long*)p;
    p += sizeof(long);
    return p;
}

uint64_t Uid::GetBufferSize() const
{
	return sizeof(size_t) +
		   sizeof(time_t) +
		   sizeof(pid_t) + 
		   sizeof(long);
}

const my_uid_t& Uid::GetUidData() const 
{
    return m_uid;
}

bool Uid::operator==(const Uid& other) const 
{
    return m_uid.counter == other.m_uid.counter &&
           m_uid.timestamp == other.m_uid.timestamp &&
           m_uid.pid == other.m_uid.pid &&
           m_uid.ip == other.m_uid.ip;
}

void Uid::Print_Object() const
{
    std::cout<<"counter is: "<<m_uid.counter<<std::endl;
    std::cout<<"timestamp is: "<<m_uid.timestamp<<std::endl;
    std::cout<<"pid is: "<<m_uid.pid<<std::endl;
    std::cout<<"ip is: "<<m_uid.ip<<std::endl;
}

