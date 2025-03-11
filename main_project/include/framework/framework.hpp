#ifndef __FRAMEWORK__HPP__
#define __FRAMEWORK__HPP__
#include <vector>
#include "mediator.hpp"
#include "reactor.hpp"
#include "dirmonitor.hpp"
#include "icommand.hpp"

class Framework
{
    public:
        Framework(const std::unordered_map<fd_item, IInputproxy*, FdItemHash>&, const std::shared_ptr<Reactor::Ilistener> &,  const std::vector<std::pair<KEY, std::function<std::shared_ptr<ICommand>()>>>&, const string &);
        void Run();
    private:
        Reactor reactor;
        Mediator mediator;   
        Dirmonitor dirm;
        DLLLoader dll_l;
        Callback<DLLLoader, string> callback;
        
};
#endif//__FRAMEWORK__HPP__