#ifndef __RESPONSE__READ__MESSAGE__HPP__
#define __RESPONSE__READ__MESSAGE__HPP__

#include <memory>
#include "amessage.hpp"

class ResponseReadmessage : public AMessage
{
    public:
        ResponseReadmessage(int32_t = 0, uint64_t = 0, const Uid &uid = Uid(), std::shared_ptr<uint8_t[]> = nullptr, uint8_t = 0);
        uint8_t* ToBuffer(uint8_t* p) override;
        uint8_t* FromBuffer(uint8_t* p) override;
        uint64_t GetBufferSize() const override;
        std::shared_ptr<uint8_t[]> GetData() override;
        uint8_t IsSuccess() const ;
        void Print_Object() const override;
        ~ResponseReadmessage() override = default;
    private:
        std::shared_ptr<uint8_t[]> m_buffer;
        uint8_t m_status;
        
};

#endif // __RESPONSE__READ__MESSAGE__HPP__