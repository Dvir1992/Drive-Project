    #include <functional>
    #include <memory>
    #include <vector>
    #include <thread>
    #include <stddef.h>
    #include <atomic>
    #include "waitable_queue.hpp"
    #include <semaphore.h>

   


    class ThreadPool
    {
        public:  
            typedef enum priority {LOW, MEDIUM, HIGH} priority_t;
            class ITPTask;
            class FuncTPTask;
            template<typename OUTPUT>
            class FutureTPTask;
            
            explicit ThreadPool(size_t num_threads = 4);
            ThreadPool(const ThreadPool& other_) = delete;
            ThreadPool& operator=(const ThreadPool& other_) = delete;
            ~ThreadPool() noexcept;

            void AddTask(std::pair<std::shared_ptr<ITPTask>, priority_t> task = std::make_pair(nullptr, MEDIUM)); //proroty defulat- how to do?
            void SetNumThreads(size_t N);
            void Pause();
            void Resume();
            void Thread();

            class ITPTask //why nested? // In order to not affect user's global namespace.
            {
            public:
                virtual ~ITPTask() = 0; 
                virtual void Run() = 0;
            };
            
            class FuncTPTask : public ITPTask
            {
            public:
                explicit FuncTPTask(std::function<void()>);
                ~FuncTPTask()  override; 
                void Run() override;
            private:
                std::function<void()> func;
            };
            
            template<typename OUTPUT>
            class FutureTPTask : public ITPTask 
            {
            public:
                explicit FutureTPTask(std::function<OUTPUT()>);
                ~FutureTPTask() override;
                void Run() override;
                OUTPUT Get();
            private:
                std::function<OUTPUT()> func;
                OUTPUT m_out;
                sem_t sem;
            };



        private:
            class Comparator
            {
                public: 
                    bool operator()(const std::pair<std::shared_ptr<ThreadPool::ITPTask>, priority_t>& a,
                                    const std::pair<std::shared_ptr<ThreadPool::ITPTask>, priority_t>& b) const
                    {
                        return a.second < b.second; 
                    }
            };
            Waitable_queue<
                std::pair<std::shared_ptr<ITPTask>, priority_t>, 
                Pq<
                    std::pair<std::shared_ptr<ITPTask>, priority_t>,
                    std::vector<std::pair<std::shared_ptr<ITPTask>, priority_t>>,
                    Comparator>
            > task_q; 
            std::vector<std::thread> v_threads;
            std::atomic<bool> pause_flag;
            std::atomic_size_t threads;
            std::atomic_size_t threads_temp;
            condition_variable cv;
            mutex mtx;
    };

    template<typename OUTPUT>
    ThreadPool::FutureTPTask<OUTPUT>::FutureTPTask(std::function<OUTPUT()> func_p):func(func_p)
    {
        sem_init(&sem, 0, 0);
    }

    template<typename OUTPUT>
    OUTPUT ThreadPool::FutureTPTask<OUTPUT>::Get()
    {
        sem_wait(&sem);
        return m_out;
    }

    template<typename OUTPUT>
    void ThreadPool::FutureTPTask<OUTPUT>::Run(){m_out = func(); sem_post(&sem);}

    template<typename OUTPUT>
    ThreadPool::FutureTPTask<OUTPUT>::~FutureTPTask(){}
    
