#include "mediator.hpp"
#include "icommand.hpp"
#include "ai.hpp" 
#include "factory.hpp"

void Mediator::Callback(int fd, Reactor::Mode mode)
{
    auto it = m_arr.find(fd_item(fd, mode));
    if (it != m_arr.end()) 
    {    
        std::shared_ptr<IArgs> taskargs = it->second->GetArgsTask(fd_item(fd, mode));

        if(taskargs)
        {     
         
            Singleton<ThreadPool>::GetInstance()->AddTask(std::make_pair(std::make_shared<TPTask>(taskargs), ThreadPool::MEDIUM));   
        }

    }
}

Mediator::Mediator(const  std::unordered_map<fd_item, IInputproxy*, FdItemHash> &arr, Reactor *reactor):m_arr(arr)
{
    for(auto &element: arr)
    {
        reactor->Register(element.first.first, element.first.second, std::bind(&Mediator::Callback, this, std::placeholders::_1,std::placeholders::_2));
    }    
}

Mediator::TPTask::TPTask(shared_ptr<IArgs> taskargs):m_taskargs(taskargs)
{

}


void Mediator::TPTask::Run()
{
    KEY factory_key = m_taskargs->GetKey();
    shared_ptr<ICommand> cmd = Singleton<Factory<KEY,shared_ptr<ICommand>>>::GetInstance()->Create(factory_key);
                   
    std::pair<std::function<bool()>, std::chrono::milliseconds> res = cmd->Execute(m_taskargs);
    if(res.first != nullptr)
    {
        new Ai(res.first, res.second);
    }
}


