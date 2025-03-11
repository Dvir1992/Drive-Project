#ifndef SINGLETON__HPP__
#define SINGLETON__HPP__
    #include <iostream>
    #include <memory>
    #include <mutex>
    #include <stdlib.h>
    #include <atomic>
    using namespace std;

    template <typename T>
    class Singleton
    {
        public:
            
            ~Singleton()= delete;
            Singleton(const Singleton& other) = delete;
            Singleton& operator=(const Singleton &other) = delete;
            static T* GetInstance();
            static void Cleanup();  
        #ifdef  Singleton_ONLY_LIB
        private:
        
            Singleton() = default;
            static atomic<T*> m_instance; 
            static mutex m_mutex;
        #endif

    };
    #ifdef  Singleton_ONLY_LIB
    template <typename T>
    void  Singleton<T>::Cleanup()
    {
        delete m_instance;
    }
    template <typename T>
    atomic<T*> Singleton<T>::m_instance;

    template <typename T>
    mutex Singleton<T>::m_mutex;

    template <typename T>
    T* Singleton<T>::GetInstance() 
    {
        T* tmp = m_instance.load(std::memory_order_relaxed);
        std::atomic_thread_fence(std::memory_order_acquire);
        if (tmp == nullptr) {
            std::lock_guard<std::mutex> lock(m_mutex);
           
            tmp = m_instance.load(std::memory_order_relaxed);
            if (tmp == nullptr) {
                tmp = new T;
                
                std::atomic_thread_fence(std::memory_order_release);
                m_instance.store(tmp, std::memory_order_relaxed);
                atexit(Cleanup);
            }
        }
       
        return tmp;
    }
    #endif
#endif



