#ifndef __IINPUTPROXY_HPP
#define __IINPUTPROXY_HPP
#include "iargs.hpp"
#include "fditem.hpp"
#include <memory>
    class IInputproxy
    {
        public:
            virtual std::shared_ptr<IArgs> GetArgsTask(fd_item) = 0;
            virtual ~IInputproxy() = default;
    };
#endif // __IINPUTPROXY_HPP