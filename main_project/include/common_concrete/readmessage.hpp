#ifndef __READMESSAGE__HPP
#define __READMESSAGE__HPP
#include <cstdint>
#include "amessage.hpp"
class Readmessage : public AMessage
{
    public:
        Readmessage(int32_t = 0, uint64_t = 0, const Uid& uid = Uid(), uint64_t = 0);
        uint8_t* ToBuffer(uint8_t* p) override;
        uint8_t* FromBuffer(uint8_t* p) override;
        uint64_t GetBufferSize() const override;
        void Print_Object() const override;
        uint64_t GetOffset();
        ~Readmessage() override = default;
    private:
        uint64_t m_offset;

};

#endif //__READMESSAGE__HPP
