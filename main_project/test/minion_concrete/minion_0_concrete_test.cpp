#define DIR "./plugin_minion_0"
#include "framework.hpp"
#include "masterproxy.hpp"
#include "readmessage.hpp"
#include "writemessage.hpp"
#include "m_r_command.hpp"
#include "m_w_command.hpp"
#include "singleton.hpp"
#include "factory.hpp"
#include <memory>

class Linux_Listener: public Reactor::Ilistener
{
    public:
        ~Linux_Listener() override;
        std::vector<Reactor::ListenPair> Listen(const std::vector<Reactor::ListenPair>& listenTo) const override;
};

std::vector<Reactor::ListenPair> Linux_Listener::Listen(const std::vector<Reactor::ListenPair>& listenTo) const 
{
     
    std::vector<Reactor::ListenPair> ret_v;
    fd_set readfds;
    fd_set writefds;
    int max_fd = 0;


    FD_ZERO(&readfds);
    FD_ZERO(&writefds);
    for(auto &element : listenTo)
    {
        if(element.second == Reactor::READ)
        {
            FD_SET(element.first, &readfds);
        }
        else
        {
            FD_SET(element.first, &writefds);
        }
        if(element.first > max_fd)
        {
            max_fd = element.first;
        }
    }
    int activity = select(max_fd + 1, &readfds, &writefds, NULL, NULL);

    if(0 == activity)
    {
        std::cout<<"time is up, bye bye\n";
    }
    else if (activity < 0) 
    {
          std::cout << "Error number: " << errno << std::endl;
    }
    else
    {
        for(auto &element : listenTo)
        {
            if (FD_ISSET(element.first, &readfds)) 
            {
                ret_v.push_back(element);
            }
            if (FD_ISSET(element.first, &writefds)) 
            {
                ret_v.push_back(element);
            }

        }  
    }
    return ret_v;
}

Linux_Listener:: ~Linux_Listener(){}

std::shared_ptr<Reactor::Ilistener> m_listener =  std::make_shared<Linux_Listener>();

shared_ptr<AMessage> CreateRMessage(uint64_t data_size)
{
    return std::make_shared<Readmessage>(R, data_size); 
}

shared_ptr<AMessage> CreateWMessage(uint64_t data_size)
{
    return std::make_shared<Writemessage>(W, data_size); 
}

shared_ptr<ICommand> CreateMRCommand()
{
    return std::make_shared<MR_Command>(); 
}

shared_ptr<ICommand> CreateMWCommand()
{
    return std::make_shared<MW_Command>(); 
}
int main()
{
    std::vector<std::pair<KEY, std::function<std::shared_ptr<ICommand>()>>> m_v = {{R, CreateMRCommand},{W, CreateMWCommand}};
    Singleton<Factory<KEY,std::shared_ptr<AMessage>, uint64_t>>::GetInstance()->Add(R, CreateRMessage);//could add to the vector of commands but not critical
    Singleton<Factory<KEY,std::shared_ptr<AMessage>, uint64_t>>::GetInstance()->Add(W, CreateWMessage);//could add to the vector of commands but not critical

    std::unordered_map<fd_item, IInputproxy*, FdItemHash> m_arr;
    MasterProxy m_proxy_0("./minion_0_disk.bin",7070);
    int server_fd = m_proxy_0.GetFd();
    fd_item m_item = {server_fd, Reactor::READ};
    m_arr[m_item] = &m_proxy_0;

    std::shared_ptr<Reactor::Ilistener> m_m_listener =  std::make_shared<Linux_Listener>();

    Framework f(m_arr, m_m_listener,m_v, DIR);
    f.Run();

    return 0;
}

