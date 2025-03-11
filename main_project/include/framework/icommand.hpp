#ifndef ICOMMAND__HPP__ 
#define ICOMMAND__HPP__
#include <utility>
#include <functional>
#include <chrono>
#include <memory>
#include "iargs.hpp"

class ICommand
{
    public:
        virtual std::pair<std::function<bool()>, std::chrono::milliseconds> Execute(std::shared_ptr<IArgs>) = 0;
        virtual ~ICommand() = default;

};

#endif  