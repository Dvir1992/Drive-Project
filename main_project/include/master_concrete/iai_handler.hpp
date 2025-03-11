#ifndef IAiHandler__HPP
#define IAiHandler__HPP
#include "uid.hpp"

class IAiHandler
{
    public:
        virtual bool operator()() = 0;
        virtual void SetUids(const Uid &data_uid, const Uid &mirrored_data_uid) = 0;
        ~IAiHandler() = default;
};

#endif //IAiHandler__HPP