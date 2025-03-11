    #include "thread_pool.hpp"
    
    #define HIGHEST 4
    #define KILL 5

    void ThreadPool::Thread() 
    {  
        std::pair<std::shared_ptr<ThreadPool::ITPTask>, priority_t> task;
        while(task.second != static_cast<priority_t>(KILL))
        {   
            task_q.Pop(task);
            if(task.first)
            {  
                task.first->Run();
            }
        }
    }

    ThreadPool::ThreadPool(size_t num_threads)
    {
        threads.store(num_threads);
        threads_temp.store(0);
        pause_flag.store(false);
        
        for(size_t i = 0; i<num_threads; ++i)
        {
            v_threads.emplace_back([this]() { Thread();});
        }
    }

    ThreadPool::~ThreadPool()
    {
        for (size_t i = 0; i<v_threads.size(); ++i) 
        {
                AddTask({std::make_shared<ThreadPool::FuncTPTask>([this](){}),static_cast<priority_t>(KILL)});     
        }
        for (std::thread& t : v_threads) 
        {
            if (t.joinable()) 
            { 
                t.join();      
            }
        }
    }

    void ThreadPool::AddTask(std::pair<std::shared_ptr<ThreadPool::ITPTask>, priority_t> task){task_q.Push(task);}

    void ThreadPool::Pause()
    {
        unique_lock<mutex> lock(mtx); 
        cv.wait(lock, [this] {return threads_temp == 0;});                     
        pause_flag.store(true); 
        
        for(size_t i=0; i< threads; ++i)
        { 
            AddTask({
                        std::make_shared<ThreadPool::FuncTPTask>
                        (
                            [this]()
                            {
                                unique_lock<mutex> lock(mtx);
                                threads_temp++;
                                cv.notify_all(); 
                                cv.wait(lock, [this] {return !pause_flag.load();});
                                threads_temp--;
                                cv.notify_all(); 
                            }
                        ),   
                        static_cast<priority_t>(HIGHEST)
                    });
        }
        cv.wait(lock, [this] {return threads_temp == threads;});
    }

    void ThreadPool::Resume()
    {
        pause_flag.store(false);
        cv.notify_all();
    }

    void  ThreadPool::SetNumThreads(size_t N)
    {
        size_t threads_num = threads;
        if(N>=threads_num)
        {
            for(size_t i = 0; i<(N-threads_num); ++i)
            {
                v_threads.emplace_back([this]() { Thread();});
            }
             
        }
        else
        {   
            for(size_t i = 0; i<(threads_num-N); ++i)
            {
              AddTask({std::make_shared<ThreadPool::FuncTPTask>([this](){}),static_cast<priority_t>(KILL)});

            }          
        }
        threads.store(N);
    
        
    }

    ThreadPool::ITPTask::~ITPTask(){}

    ThreadPool::FuncTPTask::FuncTPTask(std::function<void()> func_p):func(func_p){}

    void ThreadPool::FuncTPTask::Run(){func();}

    ThreadPool::FuncTPTask::~FuncTPTask(){}


