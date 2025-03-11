#ifndef WAITABLE_QUEUE__HPP
#define WAITABLE_QUEUE__HPP
#include <iostream>
#include <queue>
#include <chrono>
#include <mutex>
#include <condition_variable>
using namespace std;
template <typename Item, typename Q=queue<Item>> 
class Waitable_queue
{
    public:
        Waitable_queue() = default;
        ~Waitable_queue() = default;
        void Push(Item &item);
        bool Pop(time_t timeout, Item& out_i);
        void Pop(Item& out_i);
        bool IsEmpty() const;

    private:
        Q queue;
        timed_mutex tmtx;
        condition_variable_any cv;




};
template <typename Item, typename Container=std::vector<Item>, typename Compare=std::less<typename Container::value_type>, typename PQ = priority_queue<Item,Container, Compare>> 
class Pq:private PQ
{
    public:
    Pq() = default;
    ~Pq() = default;
    const Item& front(){return PQ::top();}
    using PQ::pop;
    using PQ::push;
    using PQ::empty;
};


template <typename Item, typename Q>
void Waitable_queue <Item,Q>::Push(Item &item)
{
    unique_lock<timed_mutex> lock(tmtx); 
    queue.push(item);
    cv.notify_one();
}

template <typename Item, typename Q>
void Waitable_queue <Item,Q>::Pop(Item &out_i)
{
    unique_lock<timed_mutex> lock(tmtx); 
    cv.wait(lock, [this] { return !IsEmpty();});
    out_i = queue.front();
    queue.pop(); 
}

template <typename Item, typename Q>
bool Waitable_queue <Item,Q>::Pop(time_t timeout, Item &out_i)
{
    unique_lock<timed_mutex> lock(tmtx, defer_lock);
    const chrono::time_point<chrono::system_clock> time = chrono::system_clock::now() + chrono::seconds(timeout);
    if(lock.try_lock_until(time))
    {   
         if(cv.wait_until(lock, time, [this] { return !IsEmpty();}))
         {
            out_i = queue.front();
            queue.pop(); 
            return true;
         }
    }
    return false;
}

template <typename Item, typename Q>
bool Waitable_queue <Item,Q>::IsEmpty() const
{
    return queue.empty();
}

#endif //WAITABLE_QUEUE__HPP







