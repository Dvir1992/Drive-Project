#include "m_r_args.hpp"
MR_args::MR_args(uint64_t size, uint64_t offset,MasterProxy* mp):m_size(size), m_offset(offset),m_mp(mp)
{

}
KEY MR_args::GetKey() const
{
    return R;
}

uint64_t MR_args::GetOffset() const
{
    return m_offset;
}

uint64_t MR_args::GetSize() const
{
    return m_size;
}

MasterProxy* MR_args::GetMP() const
{
    return m_mp;
}
