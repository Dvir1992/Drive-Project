#ifndef FDITEMHASH__HPP__
#define FDITEMHASH__HPP__
#include "fditem.hpp"
struct FdItemHash 
{
    size_t operator()(const fd_item &item) const 
    {
        return std::hash<int>()(item.first) ^ (std::hash<int>()(static_cast<int>(item.second)) << 1);
    }
};
#endif