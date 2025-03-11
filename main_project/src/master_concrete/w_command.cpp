#include "w_command.hpp"
#include "w_args.hpp"
#include "raid01.hpp"
#include "singleton.hpp"
#include "response_manager.hpp"

W_Command::W_Command(std::shared_ptr<IAiHandler> ai_handler):m_ai_handler(ai_handler)
{

}

std::pair<std::function<bool()>, std::chrono::milliseconds> W_Command::Execute(std::shared_ptr<IArgs> args)  
{
    std::shared_ptr<W_args> w_args = std::dynamic_pointer_cast<W_args>(args); 


    if (w_args)
    {

        std::pair<pair<shared_ptr<IMinion>, uint64_t>, std::pair<shared_ptr<IMinion>, uint64_t>> m_data = 
        Singleton<Raid01>::GetInstance()->GetPhysicalOffset(w_args->GetOffset());
                         

        const Uid& uid = Singleton<ResponseManager>::GetInstance()->RegisterCommand();
        const Uid& uid_mirrored = Singleton<ResponseManager>::GetInstance()->RegisterCommand();
        m_data.first.first->Write(w_args->GetData(),w_args->GetSize(), uid, m_data.first.second);

        m_data.second.first->Write(w_args->GetData(),w_args->GetSize(), uid_mirrored, m_data.second.second); 
        m_ai_handler->SetUids(uid, uid_mirrored);
   
        return std::make_pair([this]() { return (*m_ai_handler)(); }, std::chrono::milliseconds(100));
    } 
    return std::make_pair(nullptr, std::chrono::milliseconds(100));
}
    