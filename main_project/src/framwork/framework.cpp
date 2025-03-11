#include "framework.hpp"
#include "singleton.hpp"
#include "factory.hpp"

Framework::Framework(const std::unordered_map<fd_item, IInputproxy*, FdItemHash>& arr, const std::shared_ptr<Reactor::Ilistener> &listen, const std::vector<std::pair<KEY, std::function<std::shared_ptr<ICommand>()>>> &vec, const string &path_dir)
:reactor(listen),mediator(arr, &reactor), dirm(path_dir), callback(dll_l,  &DLLLoader::Load)
{
    dirm.Register(&callback);
    for(auto &element : vec)
    {
        Singleton<Factory<KEY, std::shared_ptr<ICommand>>>::GetInstance()->Add(element.first,element.second);
    }
    //we should handle the case where each time minion fell down and revivied, all the plugin updates 
    //are loaded according to their creation date, but we don't support it right now.
    
}
 void Framework::Run()
 {
    reactor.Run();
 }
