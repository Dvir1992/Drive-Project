#ifndef __ILRD_SCHEDULER_HPP__
#define __ILRD_SCHEDULER_HPP__

#include <chrono>
#include <memory>
#include <signal.h>
#include "singleton.hpp" 
#include "waitable_queue.hpp"

class Scheduler
{
public:
    
    class ISchedTask
    {
    public:
        virtual ~ISchedTask() = default;
        virtual void Execute() = 0;
    };

    void AddTask(std::shared_ptr<ISchedTask> task, const std::chrono::nanoseconds& SecDelta);
    ~Scheduler() noexcept = default ;

private:
    Scheduler(); // for Singleton
    friend class Singleton<Scheduler>;
    using Time = std::chrono::_V2::system_clock::time_point; //clock is templated to sytemclock, duration is templated for rep = long long and period = nano
    using Item = std::pair<Time, std::shared_ptr<ISchedTask>>;
    void printFormattedTimePoint(const Time& tp);

    class Timer
    {
    public:
        Timer(Scheduler *sched);
        ~Timer();
        void Start(const Time &expirationTime);
        void Stop();

    private:
        static void TimerHandler(union sigval sigdata);
        timer_t m_timerid;
        struct itimerspec m_its;
        struct sigevent m_sig_ev;
        Scheduler* m_scheduler;
    };
    std::shared_ptr<Timer> m_timer; 
    std::mutex m_mutex;  
    Waitable_queue<
        Item, 
        Pq<
            Item,
            std::vector<Item>,
            std::greater< std::vector<Item>::value_type>>
    > m_wq; 
    Item Peek;
};


#endif //__ILRD_SCHEDULER_HPP__