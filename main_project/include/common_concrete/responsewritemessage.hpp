#ifndef __RESPONSE__WRITE__MESSAGE__HPP__
#define __RESPONSE__WRITE__MESSAGE__HPP__
#include <memory>
#include "amessage.hpp"
class ResponseWritemessage : public AMessage
{
    public:
        ResponseWritemessage(int32_t = 0, uint64_t = 0, const Uid &uid = Uid(), uint8_t = 0);
        uint8_t* ToBuffer(uint8_t* p) override;
        uint8_t* FromBuffer(uint8_t* p) override;
        uint64_t GetBufferSize() const override;
        uint8_t IsSuccess() const override;
        std::shared_ptr<uint8_t[]> GetData() override;
        void Print_Object() const override;
        ~ResponseWritemessage() override = default;
    private:
        uint8_t m_status;
};
#endif // __RESPONSE__WRITE__MESSAGE__HPP__

