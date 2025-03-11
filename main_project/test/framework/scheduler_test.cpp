#include <thread>

#include "scheduler.hpp"

class TestTask : public Scheduler::ISchedTask
{
public:
    TestTask(int n) : m_n(n){} 
    void Execute(){/* sleep(3); */printf("executed - %d\n", m_n);}

private:
    int m_n; 
};

void ThreadFunc(Scheduler *sched)
{
    shared_ptr<TestTask> a = make_shared<TestTask>(3);
    sched->AddTask(a, std::chrono::milliseconds(4500));
    shared_ptr<TestTask> b = make_shared<TestTask>(1);
    sched->AddTask(b, std::chrono::milliseconds(550));
    shared_ptr<TestTask> c = make_shared<TestTask>(2);
    sched->AddTask(c, std::chrono::milliseconds(1550));
}

int main()
{
    Scheduler *sched = Singleton<Scheduler>::GetInstance();
    shared_ptr<TestTask> a = make_shared<TestTask>(4);
    sched->AddTask(a, std::chrono::milliseconds(5000));
    thread t1(ThreadFunc, sched);
    t1.join();
    sleep(6);
    shared_ptr<TestTask> b = make_shared<TestTask>(5);
    sched->AddTask(b, std::chrono::milliseconds(100));
    sleep(/* 20 */1);
    return 0;
}

  