#ifndef __IARGS_HPP
#define __IARGS_HPP
#include "keys.hpp"
class IArgs
{
    public:
        virtual KEY GetKey() const = 0;
        virtual ~IArgs() = default;
    private:

};
#endif // IARGS_HPP