#include "response_manager.hpp"

const Uid& ResponseManager::RegisterCommand()
{
    return m_arr.insert({Uid(),0}).first->first;
}

void ResponseManager::RegisterResponse(const Uid& uid, bool status)
{
    m_arr[uid] = status;
}

bool ResponseManager::HasResponseRecieved(const Uid &uid)
{
    return m_arr[uid];
}