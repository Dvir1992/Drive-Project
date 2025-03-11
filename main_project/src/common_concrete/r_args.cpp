#include "r_args.hpp"
#include "keys.hpp"
R_args::R_args(uint64_t size, uint64_t offset):m_size(size), m_offset(offset)
{

}
KEY R_args::GetKey() const
{
    return R;
}

uint64_t R_args::GetOffset() const
{
    return m_offset;
}

uint64_t R_args::GetSize() const
{
    return m_size;
}
