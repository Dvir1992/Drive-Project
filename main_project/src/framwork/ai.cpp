#include "ai.hpp"

Ai::Ai(std::function<bool()> func, std::chrono::milliseconds millis):m_func(func), m_interval(millis)  
{
    m_task = std::make_shared<AITask>(this); 
    Singleton<Scheduler>::GetInstance()->AddTask(m_task, m_interval);
}

void Ai::Perform()
{
    if(!m_func())
    {
       Singleton<Scheduler>::GetInstance()->AddTask(m_task, m_interval);
    }
    else
    {
        delete this;
    }
}

Ai::AITask::AITask(Ai* ai):m_ai(ai)
{

}

void Ai::AITask::Execute()
{
    m_ai->Perform();
}
