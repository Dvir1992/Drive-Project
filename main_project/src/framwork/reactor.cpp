#include <unistd.h> /* close */
#include "reactor.hpp"
Reactor::Ilistener::~Ilistener(){}

Reactor::Reactor(std::shared_ptr<Ilistener> listen): m_listener(listen)
{

}

void Reactor::Register(int fd, Mode mode, std::function<void(int, Mode)> func)
{
    ListenPair key = std::make_pair(fd, mode); // Create the ListenPair key
    m_umap.insert({key, func}); 
}

void Reactor::UnRegister(int fd, Mode mode)
{
    ListenPair key = std::make_pair(fd, mode);
    m_umap.erase(key);
}

void Reactor::Run()
{

    while(!m_isStopped)
    {
        std::vector<ListenPair> v;
        for(auto &element : m_umap)
        {
            v.insert(v.begin(), element.first);
        }

        v = m_listener->Listen(v);
        //sleep(1);

        for(auto &element : v)
        {
            if(m_umap.find(element) != m_umap.end())
            {
                (m_umap[element])(element.first, element.second);
            }
        }
    }

    m_isStopped = false;
}

void Reactor::Stop()
{
    m_isStopped = true;
}
