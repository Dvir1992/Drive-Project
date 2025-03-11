#ifndef __MW__ARGS__HPP
#define __MW__ARGS__HPP
#include <memory>
#include "iargs.hpp"
#include "masterproxy.hpp"

class MW_args : public IArgs
{
    public:
        MW_args(shared_ptr<uint8_t[]> , uint64_t , uint64_t , MasterProxy*);
        KEY GetKey() const;
        uint64_t GetOffset() const;
        uint64_t GetSize() const;
        shared_ptr<uint8_t[]> GetData() const;
        MasterProxy* GetMP() const;

    private:
        shared_ptr<uint8_t[]> m_buffer;
        uint64_t m_size;
        uint64_t m_offset;
        MasterProxy* m_mp;
        
} ;
#endif //__W__ARGS__HPP