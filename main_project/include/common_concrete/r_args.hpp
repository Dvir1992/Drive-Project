#ifndef __R_ARGS__HPP
#define __R__ARGS__HPP

#include "iargs.hpp"
#include <cstdint>
class R_args : public IArgs
{
    public:
        R_args(uint64_t size, uint64_t offset);
        KEY GetKey() const override;
        uint64_t GetOffset() const;
        uint64_t GetSize() const;
    private:
        uint64_t m_size;
        uint64_t m_offset;
} ;

#endif //__R_ARGS__HPP