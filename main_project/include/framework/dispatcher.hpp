#ifndef DISPATCHER__HPP__
#define DISPATCHER__HPP__

    #include <iostream>
    #include <list>
    #include <algorithm>
    using namespace std;

    template <typename OBSERVER, typename EVENT>
    using member_func_notify = void (OBSERVER::*)(const EVENT&);

    template <typename OBSERVER>
    using member_func_death_notify = void (OBSERVER::*)(); 

    template <typename EVENT>
    class ACallback;

    template <typename EVENT>
    class Dispatcher
    {
        public:
            Dispatcher() = default;
            ~Dispatcher();
            void Register(ACallback<EVENT>* callback);
            void Unregister(ACallback<EVENT>* callback);
            void Notify(const EVENT & event);
            
        private:
            list<ACallback<EVENT>*> icb_list;
    };

    template <typename EVENT>
    class ACallback
    {
        public:
            ACallback() = default;
            ~ACallback();
            virtual void Notify(const EVENT& event) = 0;
            virtual void NotifyDeath();
            void SetDispatcher(Dispatcher<EVENT>* disp);
        private:
            Dispatcher<EVENT> *m_dispatcher;
    };

    template <typename OBSERVER, typename EVENT>
    class Callback: public ACallback<EVENT>
    {
        public:
            Callback(OBSERVER& obs, member_func_notify<OBSERVER, EVENT> func_, member_func_death_notify<OBSERVER> d_func_ = nullptr);
            ~Callback() = default;
            void Notify(const EVENT& event) override;
            void NotifyDeath() override;
        private:
            OBSERVER &obs; 
            member_func_notify<OBSERVER, EVENT> func;
            member_func_death_notify<OBSERVER> d_func;
            
    };


    template <typename EVENT>
    void Dispatcher<EVENT>::Register(ACallback<EVENT>* callback)
    {
        callback->SetDispatcher(this);
        icb_list.push_back(callback);
       
    }

    template <typename EVENT>
    void Dispatcher<EVENT>::Unregister(ACallback<EVENT>* callback)
    {
        callback->SetDispatcher(nullptr);
        icb_list.remove(callback);
    }

    template <typename EVENT>
    void Dispatcher<EVENT>::Notify(const EVENT &event)
    { 
        
        list<ACallback<EVENT>*> copied_list(icb_list);
        for (auto &element : icb_list)
        { 
            element->Notify(event);
        }
    }

    template <typename EVENT>
    Dispatcher<EVENT>::~Dispatcher()
    {
        for (auto& element : icb_list) 
        {
            element->NotifyDeath();
        }
    }

    template <typename EVENT>
    ACallback<EVENT>::~ACallback()
    {
        if(m_dispatcher != nullptr)
        {
            m_dispatcher->Unregister(this);
            m_dispatcher = nullptr;
        }
    }

    template <typename EVENT>
    void ACallback<EVENT>::NotifyDeath()
    {
        SetDispatcher(nullptr);
    }
    template <typename EVENT>
    void ACallback<EVENT>::SetDispatcher(Dispatcher<EVENT>* disp)
    {
        m_dispatcher = disp;
    }


    template <typename OBSERVER, typename EVENT>
    Callback<OBSERVER, EVENT>::Callback(OBSERVER &obs_, member_func_notify<OBSERVER, EVENT> func_,  member_func_death_notify<OBSERVER> d_func_):
    obs(obs_), func(func_), d_func(d_func_){}

    template <typename OBSERVER, typename EVENT>
    void Callback<OBSERVER, EVENT>::Notify(const EVENT& event)
    {
        (obs.*func)(event);
    }

    template<typename OBSERVER, typename EVENT>
    void Callback<OBSERVER,EVENT>::NotifyDeath()
    {
        ACallback<EVENT>::SetDispatcher(nullptr);
        if(d_func)
        {
            ((obs).*(d_func))();
        }
    }

#endif


