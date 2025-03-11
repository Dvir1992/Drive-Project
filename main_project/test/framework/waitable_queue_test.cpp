#include "waitable_queue.hpp"
#include <thread>
#include <unistd.h>

template <typename Q>
void Pusher(Q &q) 
{
    for(int i = 0; i < 100; ++i)
    {
        q.Push(i);
        

    }
    
}
template <typename Q>
void Popper(Q &q) 
{
    while(true)
    {
        int out = 0;
        q.Pop(out);
        

    }
}
template <typename Q>
void Timed_Popper(Q &q) 
{
        sleep(5);
        int out = 0;
        q.Pop(5,out);   
}
int main()
{
    Waitable_queue<int> q;
    Waitable_queue<int, Pq<int>> q2;
    thread t1(Pusher<Waitable_queue<int, Pq<int>>>,ref(q2));
    thread t2(Timed_Popper<Waitable_queue<int, Pq<int>>>,ref(q2));
    thread t3(Popper<Waitable_queue<int, Pq<int>>>,ref(q2));
    thread t4(Popper<Waitable_queue<int, Pq<int>>>,ref(q2));
    t1.join();
    t2.join();
    cout<<"t2 finished"<<endl;
    t3.join();
    t4.join();
    


    return 0;
}