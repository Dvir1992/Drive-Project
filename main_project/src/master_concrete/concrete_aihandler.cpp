#include "concrete_aihandler.hpp"
#include "iostream"
#include <singleton.hpp>
#include "response_manager.hpp"

bool Concrete_Aihandler::operator()() 
{
    static int func_calls = 0;
    func_calls++;
    if(5 == func_calls)
    {
        cout<<"command wasn't performed both for data and mirror, bye\n"; 
        return true;
    }
    if(4 == func_calls)
    {
        cout<<"command wasn't performed. check if the mirror command was performed\n";
        return Singleton<ResponseManager>::GetInstance()->HasResponseRecieved(m_mirrored_data_uid);
    }
    cout<<"send response back from ai\n";
    return Singleton<ResponseManager>::GetInstance()->HasResponseRecieved(m_data_uid);
}

void Concrete_Aihandler::SetUids(const Uid &data_uid, const Uid &mirrored_data_uid)
{
    m_data_uid = data_uid;
    m_mirrored_data_uid = mirrored_data_uid;
}