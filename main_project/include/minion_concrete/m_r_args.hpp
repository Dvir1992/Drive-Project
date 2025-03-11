#ifndef __MR_ARGS__HPP
#define __MR__ARGS__HPP
#include <cstdint>
#include <memory>
#include "iargs.hpp"
#include "masterproxy.hpp"
class MR_args : public IArgs
{
    public:
        MR_args(uint64_t size, uint64_t offset, MasterProxy*);
        KEY GetKey() const override;
        uint64_t GetOffset() const;
        uint64_t GetSize() const;
        MasterProxy* GetMP() const;
    private:
        uint64_t m_size;
        uint64_t m_offset;
        MasterProxy* m_mp;
} ;

#endif //__R_ARGS__HPP