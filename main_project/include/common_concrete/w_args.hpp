#ifndef __W__ARGS__HPP
#define __W__ARGS__HPP

#include "iargs.hpp"
#include <memory>
class W_args : public IArgs
{
    public:
        W_args(std::shared_ptr<uint8_t[]> buffer, uint64_t size, uint64_t offset);
        KEY GetKey() const;
        uint64_t GetOffset() const;
        uint64_t GetSize() const;
        std::shared_ptr<uint8_t[]> GetData() const;

    private:
        std::shared_ptr<uint8_t[]> m_buffer;
        uint64_t m_size;
        uint64_t m_offset;
        
} ;
#endif //__W__ARGS__HPP