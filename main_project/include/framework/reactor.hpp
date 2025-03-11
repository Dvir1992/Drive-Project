#ifndef __ILRD_REACTOR_HPP__
#define __ILRD_REACTOR_HPP__
#include <iostream>
#include <vector>
#include <functional>  // For std::function
#include <memory> // For std::shared_ptr
#include <unordered_map>
#include <cstddef> //size_t

class Reactor
{
public:
    enum Mode
    {
        READ, 
        WRITE
    };
    
    using ListenPair = std::pair<int, Mode>;
    
    class Ilistener
    {
    public:
        
        virtual ~Ilistener();
        virtual std::vector<ListenPair> Listen(const std::vector<ListenPair>& listenTo) const = 0;
        
    };
    
    explicit Reactor(std::shared_ptr<Ilistener> listen);
    Reactor(const Reactor&) = delete; 
    Reactor& operator=(const Reactor&) = delete;
    ~Reactor() = default;

    void Register(int fd, Mode mode, std::function<void(int, Mode)>);
    void UnRegister(int fd, Mode mode);
    void Run();
    void Stop();
    
private:
    struct HashPair
    {
        size_t operator()(const ListenPair p) const
        {
            return std::hash<int>{}(p.first * (1 + (10 * p.second))); // not concrete may change
        }
    };
    std::unordered_map<ListenPair, std::function<void(int, Mode)>, HashPair> m_umap;
    std::shared_ptr<Ilistener> m_listener;
    bool m_isStopped;
};// class Reactor

#endif //__ILRD_REACTOR_HPP__