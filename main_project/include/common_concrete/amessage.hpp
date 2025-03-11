#ifndef __AMessage__HPP__
#define __AMessage__HPP__
#include <cstdint>
#include <memory>
#include "ibuffermanager.hpp"
#include "uid.hpp"

class AMessage: public IBuffermanager
{
    public:
        explicit AMessage(int32_t ,uint64_t, const Uid&);
        uint8_t* ToBuffer(uint8_t*) override;
        uint8_t* FromBuffer(uint8_t*) override;
        uint64_t GetBufferSize() const override;
        uint32_t GetKey() const;
        uint64_t GetSize() const;
        const Uid& GetUid() const;
        virtual uint8_t IsSuccess() const;
        virtual std::shared_ptr<uint8_t[]> GetData();
        void Print_Object() const override;
        ~AMessage() override = 0;
    protected:
        int32_t m_key;
        uint64_t m_size;//the real data
        Uid m_uid;
};

#endif //__AMessage__HPP__