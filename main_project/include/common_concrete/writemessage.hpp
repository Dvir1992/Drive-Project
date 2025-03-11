#ifndef __WRITEMESSAGE__HPP
#define __WRITEMESSAGE__HPP
#include <cstdint>
#include <cstring>
#include <memory>
#include "amessage.hpp"
class Writemessage : public AMessage
{
    public:
        Writemessage(int32_t = 0, uint64_t = 0, const Uid &uid=Uid(), uint64_t = 0, std::shared_ptr<uint8_t[]> = 0);
        uint8_t* ToBuffer(uint8_t* p) override;
        uint8_t* FromBuffer(uint8_t* p) override;
        uint64_t GetBufferSize() const override;
        uint64_t GetOffset();
        std::shared_ptr<uint8_t[]> GetData();
        void Print_Object() const override;
        ~Writemessage() override = default;
    private:
        uint64_t m_offset;
        std::shared_ptr<uint8_t[]> m_buffer;
};

#endif //__WRITEMESSAGE__HPP