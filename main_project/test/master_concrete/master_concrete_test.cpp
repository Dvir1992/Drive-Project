#define DIR "./plugin_master"
#include "framework.hpp"
#include "nbdproxy.hpp"
#include "responseproxy.hpp"
#include "r_command.hpp"
#include "w_command.hpp"
#include "responsewritemessage.hpp"
#include "responsereadmessage.hpp"
#include "response_manager.hpp"
#include "singleton.hpp"
#include "factory.hpp"
#include "concrete_aihandler.hpp"


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




shared_ptr<AMessage> CreateRRMessage(uint64_t data_size)
{
    return std::make_shared<ResponseReadmessage>(RR, data_size); 
}

shared_ptr<AMessage> CreateRWMessage(uint64_t data_size)
{
    return std::make_shared<ResponseWritemessage>(RW, data_size); 
}

shared_ptr<ICommand> CreateRCommand()
{
    return std::make_shared<R_Command>(make_shared<Concrete_Aihandler>());
}

shared_ptr<ICommand> CreateWCommand()
{
   return std::make_shared<W_Command>(make_shared<Concrete_Aihandler>());
}

int main()
{
    std::unordered_map<fd_item, IInputproxy*, FdItemHash> arr;
    std::vector<std::pair<KEY, std::function<std::shared_ptr<ICommand>()>>> v = 
    {
        {R, CreateRCommand},
        {W, CreateWCommand}
    };
    Singleton<Factory<KEY,std::shared_ptr<AMessage>,uint64_t>>::GetInstance()->Add(RR, CreateRRMessage); //could add to the vector of commands but not critical
    Singleton<Factory<KEY,std::shared_ptr<AMessage>, uint64_t>>::GetInstance()->Add(RW, CreateRWMessage);//could add to the vector of commands but not critical

    std::cout<<"Response proxy: ";
    int response_server_fd = Singleton<ResponseProxy>::GetInstance()->GetFd();
    fd_item response_item = {response_server_fd, Reactor::READ};
    std::cout<<"NBDProxy: ";
    int nbdproxy_server_fd = Singleton<NBDProxy>::GetInstance()->GetFd();
    fd_item nbdproxy_item = {nbdproxy_server_fd, Reactor::READ};
    arr[response_item] = Singleton<ResponseProxy>::GetInstance();
    arr[nbdproxy_item] = Singleton<NBDProxy>::GetInstance();

    std::shared_ptr<Reactor::Ilistener> m_listener =  std::make_shared<Linux_Listener>();

    Framework f(arr, m_listener,v, DIR);
    f.Run();

    return 0;
}