#include "scheduler.hpp"
#include <cstring>
#include <ctime>
#include <iomanip>

Scheduler::Scheduler()
{
    m_timer = std::make_shared<Timer>(this);
}

Scheduler::Timer::Timer(Scheduler *sched): m_scheduler(sched)
{
    memset(&m_sig_ev, 0, sizeof(m_sig_ev));
    m_sig_ev.sigev_notify = SIGEV_THREAD; 
    m_sig_ev.sigev_value.sival_ptr = this; 
    m_sig_ev.sigev_notify_function = TimerHandler;
    if (timer_create(CLOCK_REALTIME, &m_sig_ev, &m_timerid) == -1)
    {
        throw runtime_error("Error creating timer");
    }

}

Scheduler::Timer::~Timer()
{
    Stop(); 
    timer_delete(m_timerid);
}

void Scheduler::Timer::Start(const Time &expirationTime)
{
    // Calculate the time remaining until expiration
    auto now = std::chrono::_V2::system_clock::now();
    auto timeRemaining = expirationTime - now;

    if (timeRemaining.count() <= 0)
    {
        std::cerr << "Timer expiration time is in the past, ignoring start" << std::endl;
        return;
    }
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(timeRemaining);  // Whole seconds
    auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(timeRemaining - seconds);  // Remaining nanoseconds

    memset(&m_its, 0, sizeof(m_its));
    m_its.it_value.tv_sec = seconds.count(); // Set expiration time
    m_its.it_value.tv_nsec = nanoseconds.count();
    m_its.it_interval.tv_sec = 0;  // Disable interval (one-shot timer)
    m_its.it_interval.tv_nsec = 0;

    // Start the timer with the calculated expiration time
    if (timer_settime(m_timerid, 0, &m_its, nullptr) == -1)
    {
         throw runtime_error("Error starting timer");
    }
}

void Scheduler::Timer::Stop()
{
    m_its.it_value.tv_sec = 0;
    m_its.it_value.tv_nsec = 0;

    if (timer_settime(m_timerid, 0, &m_its, nullptr) == -1)
    {
        std::cerr << "Error stopping timer" << std::endl;
    }
}


void Scheduler::AddTask(std::shared_ptr<ISchedTask> task, const std::chrono::nanoseconds& SecDelta)
{
    Time executeTime = std::chrono::system_clock::now() + SecDelta;
    auto item = std::make_pair(executeTime, task);
    std::unique_lock<std::mutex>  lock(m_mutex);  
    if (m_wq.IsEmpty() || item.first < Peek.first) 
    {
        Peek = item;
        m_timer->Start(Peek.first); 
    }
    m_wq.Push(item);
}


void Scheduler::Timer::TimerHandler(union sigval sigdata)
{
    Scheduler::Timer *timer = static_cast<Scheduler::Timer*>(sigdata.sival_ptr);
    if (timer && timer->m_scheduler) 
    {   
        Item taskItem;
        std::unique_lock<std::mutex> lock(timer->m_scheduler->m_mutex);
        timer->m_scheduler->m_wq.Pop(taskItem);
        auto task = taskItem.second; 
        if (task) 
        {  
            lock.unlock();
            task->Execute();
            lock.lock(); 
        
            if (!timer->m_scheduler->m_wq.IsEmpty()) 
            {
                timer->m_scheduler->m_wq.Pop(timer->m_scheduler->Peek);
                timer->m_scheduler->m_wq.Push(timer->m_scheduler->Peek);
                timer->m_scheduler->m_timer->Start(timer->m_scheduler->Peek.first);  // Restart the timer
            }
              
        }
        else
        {
            throw runtime_error("Error getting task");
        }
    }
}


void Scheduler::printFormattedTimePoint(const Time& tp)
{
    std::time_t time = std::chrono::system_clock::to_time_t(tp);
    std::tm* tm = std::localtime(&time);
    std::cout << std::put_time(tm, "%Y-%m-%d %H:%M:%S") << std::endl;
}