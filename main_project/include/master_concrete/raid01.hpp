#ifndef _RAID01_H__
#define _RAID01_H__
#include <cstdint>
#include <memory>
#include <vector>
#include "singleton.hpp"
#include "iminion.hpp"

class Raid01
{
    public:
        std::pair<pair<shared_ptr<IMinion>, uint64_t>, std::pair<shared_ptr<IMinion>, uint64_t>> GetPhysicalOffset(uint64_t offset) const;
    private:
        Raid01();
        friend class Singleton<Raid01>;
        vector<shared_ptr<IMinion>> m_minionProxys;
};

#endif  // __RAID01_H__
