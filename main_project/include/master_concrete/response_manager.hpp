#ifndef __RESPONSE__MANAGER_CPP
#define __RESPONSE__MANAGER_CPP
#include <unordered_map>
#include "uid_hash.hpp"
#include "uid.hpp"
class ResponseManager
{
    public:
        explicit ResponseManager() = default;
        const Uid& RegisterCommand();
        void RegisterResponse(const Uid &uid, bool status);
        bool HasResponseRecieved(const Uid &uid);
        ResponseManager(const ResponseManager& other_) = delete;
        ResponseManager& operator=(const ResponseManager& other_) =  delete;
        ~ResponseManager() = default;

    private:
        std::unordered_map<Uid, bool, UidHasher> m_arr;

};

#endif // __RESPONSE__MANAGER_CPP