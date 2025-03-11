#ifndef UID__HASH__HPP__
#define UID__HASH__HPP__
#include <functional>
#include "uid.hpp"
struct UidHasher 
{
    std::size_t operator()(const Uid& uid) const 
    {
        // Compute the hash based on m_uid (assumes m_uid is unique for each Uid)
        const my_uid_t& uid_data = uid.GetUidData(); // Add a public accessor for m_uid
        return std::hash<size_t>()(uid_data.counter) ^
               std::hash<time_t>()(uid_data.timestamp) ^
               std::hash<pid_t>()(uid_data.pid) ^
               std::hash<long>()(uid_data.ip);
    }
};
#endif // UID__HASH__HPP__