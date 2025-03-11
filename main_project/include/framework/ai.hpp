#ifndef __ILRD_AI_HPP__
#define __ILRD_AI_HPP__
#include <functional>
#include <memory>
#include "scheduler.hpp"

class Ai
{
public:

    class AITask : public Scheduler::ISchedTask
    {
        public:
            AITask(Ai*);
            ~AITask() = default;
            void Execute();
        private:
            Ai *m_ai;
    };
    Ai(std::function<bool()>, std::chrono::milliseconds millis);
    void Perform();
private:
    shared_ptr<AITask> m_task;
    std::function<bool()> m_func;
    std::chrono::duration<int,std::milli> m_interval;
};


#endif //__ILRD_AI_HPP__