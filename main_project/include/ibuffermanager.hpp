#ifndef __IBUFFERMANAGER__HPP__
#define __IBUFFERMANAGER__HPP__
#include <cstdint>
class IBuffermanager
{
    public:
        virtual uint8_t* ToBuffer(uint8_t*) = 0;
        virtual uint8_t* FromBuffer(uint8_t*) = 0;
        virtual uint64_t GetBufferSize() const = 0; 
        virtual void Print_Object() const = 0;
        virtual ~IBuffermanager() = default;
};

#endif // __IBUFFERMANAGER__HPP__