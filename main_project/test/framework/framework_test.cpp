#define DIR "/home/dvir-hazut/git/main_project/plugin"
#include "framework.hpp"

typedef enum {
    A,
    B,
    C
} KEY;


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

bool ai_function()
{
    static int a = 0;
    if (a++ > 3)
    {
        cout<<"finished\n";
        return true;
    }   
    else
    {
        cout<<"not finished yet\n";
        return false;
    }
    
}

class ArgsKey_A : public IArgs
{
    public:
        ArgsKey_A(const string& s):args(s){}
        int GetKey() const{return A;}
        string GetToPrint(){return args;}
    private:
        
        string args;
};

class InputProxy_A : public IInputproxy
{
public:
    shared_ptr<IArgs> GetArgsTask(fd_item item)
    {
       read_data(item.first);
       
       return std::make_shared<ArgsKey_A>("our arguments\n");
    }
    void read_data(int fd)
{
    char buffer[1024];  // Buffer to read data from stdin
    int bytesRead = 0;
    bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesRead < 0) 
    {
        // Error reading from stdin
        std::cerr << "Error reading from stdin"<<std::endl;
    } 
    else if (bytesRead == 0) 
    {
        // EOF reached (nothing left to read)
        std::cout << "End of input (EOF) reached." << std::endl;
    } 
    else 
    {
        // Null-terminate the buffer and print it out
        buffer[bytesRead] = '\0';
        std::cout << "Read data: " << buffer;
    }
}
};

class Command_A: public ICommand
{
    public:
        std::pair<std::function<bool()>,std::chrono::milliseconds> Execute(std::shared_ptr<IArgs> task_args) override
        {
            std::shared_ptr<ArgsKey_A> p_args_a = std::dynamic_pointer_cast<ArgsKey_A>(task_args);        
            if (p_args_a)
            {
                // Get conrete args using getters:
                cout<<p_args_a->GetToPrint();
                // operate on minion
                cout<<"lets use arguments for command on minions\n";
            }        
            return std::make_pair(ai_function, std::chrono::milliseconds(200));
        }
        ~Command_A() override = default;
}; 

shared_ptr<ICommand> CreateCommand_A()
{
     return std::make_shared<Command_A>(); 
}



int main()
{
    std::unordered_map<fd_item, IInputproxy*, FdItemHash> arr;
    std::vector<std::pair<KEY, std::function<std::shared_ptr<ICommand>()>>> v = {{A,CreateCommand_A}};
    fd_item item = {0, Reactor::READ};
    InputProxy_A proxy;
    arr[item] = &proxy;
    std::shared_ptr<Reactor::Ilistener> m_listener =  std::make_shared<Linux_Listener>();
    Framework f(arr, m_listener,v, DIR);
    
    f.Run();


    return 0;
}