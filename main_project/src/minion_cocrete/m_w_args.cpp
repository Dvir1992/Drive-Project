#include "m_w_args.hpp"
#include "keys.hpp"
MW_args::MW_args(shared_ptr<uint8_t[]> buffer, uint64_t size, uint64_t offset, MasterProxy* mp):
m_buffer(buffer),m_size(size), m_offset(offset), m_mp(mp)
{

}

KEY MW_args::GetKey() const
{
    return W;
}

uint64_t MW_args::GetOffset() const
{
    return m_offset;
}

uint64_t MW_args::GetSize() const
{
    return m_size;
}

std::shared_ptr<uint8_t[]> MW_args::GetData() const
{
    return m_buffer;
}

MasterProxy* MW_args::GetMP() const
{
    return m_mp;
}