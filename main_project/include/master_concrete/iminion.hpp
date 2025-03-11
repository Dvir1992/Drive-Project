#ifndef __I_MINION_H__
#define __I_MINION_H__
#include "uid.hpp"
class IMinion
{
    public:
        virtual void Read(uint64_t size, const Uid &uid, uint64_t offset) = 0;
        virtual void Write(std::shared_ptr<uint8_t[]> data, uint64_t size, const Uid &uid, uint64_t offset) = 0;
        virtual ~IMinion() = default;
};


#endif // __I_MINION_H__
