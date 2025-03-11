#include "raid01.hpp"
#include "minionproxy.hpp"

#define KB 1024
#define MB (1024 * (KB))
#define M_SIZE (8 * (MB))
#define M_NUM 3

Raid01::Raid01() 
{
    m_minionProxys.push_back(std::make_shared<MinionProxy>(7070, "10.1.0.7"));
    m_minionProxys.push_back(std::make_shared<MinionProxy>(7071, "10.1.0.173"));
    m_minionProxys.push_back(std::make_shared<MinionProxy>(7072, "10.1.0.173"));
}

std::pair<pair<shared_ptr<IMinion>, uint64_t>, std::pair<shared_ptr<IMinion>, uint64_t>> Raid01::GetPhysicalOffset(uint64_t offset) const
{
    size_t minion_index = (offset /(M_SIZE));
    uint64_t m_offset = offset % (M_SIZE);
    int mirrored_minion_index = (minion_index + 1) % M_NUM;
    uint64_t mirrored_m_offset = M_SIZE/2 + m_offset;
    return make_pair(make_pair(m_minionProxys[minion_index],m_offset),make_pair(m_minionProxys[mirrored_minion_index],mirrored_m_offset));
}


