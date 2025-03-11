    #ifndef __MEDIATOR__HPP__
    #define __MEDIATOR__HPP__
    #include <unordered_map>
    #include "iinputproxy.hpp"
    #include "thread_pool.hpp"
    #include "fd_item_hash.hpp"
  
    class Mediator
    {
        public:
        class TPTask : public ThreadPool::ITPTask
        {
            public:
                TPTask(shared_ptr<IArgs>);
                void Run() override;
                ~TPTask() override = default;
            private:
                shared_ptr<IArgs> m_taskargs;
        };
            Mediator(const  std::unordered_map<fd_item, IInputproxy*, FdItemHash> &m_arr, Reactor *reactor);
            void Callback(int, Reactor::Mode);
        private:
            std::unordered_map<fd_item, IInputproxy*, FdItemHash> m_arr;
    };

    #endif // __MEDIATOR__HPP__