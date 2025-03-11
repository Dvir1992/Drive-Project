#ifndef __NBDRequest__HPP__
#define __NBDRequest__HPP__
#include <memory>
#include "ibuffermanager.hpp"
#include "keys.hpp"
class NBDRequest : public IBuffermanager
{
    public:
        NBDRequest(KEY = R,  uint64_t = 0, std::shared_ptr<u_int8_t[]> = nullptr, u_int64_t = 0);
        uint8_t* ToBuffer(uint8_t*) override;
        uint8_t* FromBuffer(uint8_t*) override;
        uint64_t GetBufferSize() const override; 
        KEY GetKey() const;
        uint64_t GetSize() const;
        std::shared_ptr<u_int8_t[]> GetData() const;
        uint64_t GetOffset() const;
        void Print_Object() const override;
        ~NBDRequest() override = default;
    private:
        KEY m_key;
        u_int64_t m_size; 
        std::shared_ptr<u_int8_t[]> m_buffer;        
        u_int64_t m_offset;   
};

#endif // __NBDRequest__HPP__