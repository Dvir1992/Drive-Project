#include <cerrno> //errno
#include <sys/select.h> //FD_SET
#include <memory>    //For std::shared_ptr
#include <unistd.h> //read
#include "reactor.hpp"
static int a = 0;
class Linux_Listener: public Reactor::Ilistener
{
    public:
        ~Linux_Listener() override;
        std::vector<Reactor::ListenPair> Listen(const std::vector<Reactor::ListenPair>& listenTo) const override;
};

std::vector<Reactor::ListenPair> Linux_Listener::Listen(const std::vector<Reactor::ListenPair>& listenTo) const 
{
     std::cout<<"hii\n";
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
Reactor reactor(m_listener);

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
        std::cout << "Read data: " << buffer << std::endl;
    }
}

void response(int fd, Reactor::Mode mode)
{   
    
    if (mode == Reactor::READ)
    {
        read_data(fd);
    }
    else if (mode == Reactor::WRITE) 
    {
        std::cerr << "I'm Ready for writing My Love" << std::endl;
    }
    std::cout<<a<<"\n";
    if (a > 5)
    {
        reactor.Stop();
        return;
    }
    
    a++;
}



int main()
{
    reactor.Register(0,Reactor::WRITE,response);
    reactor.Register(0,Reactor::READ,response);
    reactor.Run();
    a = 0;
    std::cout<<"finidhed\n";
    reactor.UnRegister(0,Reactor::WRITE);
    reactor.Run();
    std::cout<<"finidhed\n";

    return 0;
}