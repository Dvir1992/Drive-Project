#include "w_args.hpp"
#include "keys.hpp"
W_args::W_args(std::shared_ptr<uint8_t[]> buffer, uint64_t size, uint64_t offset):m_buffer(buffer),m_size(size), m_offset(offset)
{

}

KEY W_args::GetKey() const
{
    return W;
}

uint64_t W_args::GetOffset() const
{
    return m_offset;
}

uint64_t W_args::GetSize() const
{
    return m_size;
}

std::shared_ptr<uint8_t[]> W_args::GetData() const
{
    return m_buffer;
}