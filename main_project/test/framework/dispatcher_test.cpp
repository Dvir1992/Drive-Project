#define Singleton_ONLY_LIB
#include "dispatcher.hpp"
#include "singleton.hpp"
#include <iostream>
#include <thread>
int flag = 0;
int flag2 = 0;
class A
{
public:
    void Add(const int &num){m_i += num; std::cout<< "in A: " << m_i << std::endl;}
    int GetInt(){return m_i;}
    friend class Singleton<A>;

private:
    A():m_i(0){}
    int m_i;

};

class B
{
public:
    void Sub(const int & num){m_i -= num; std::cout<< "in B: " << m_i << std::endl;}
    int GetInt(){return m_i;}
    friend class Singleton<B>;
private:
    B():m_i(10){}
    int m_i;

};

class C
{
public:
    void Multi(const int & num){m_i *= num; std::cout<< "in C: " << m_i << std::endl;}
    int GetInt(){return m_i;}
    friend class Singleton<C>;
private:
    C():m_i(1){}
    int m_i;

};

class E
{
public:
    void Div(const int & num){m_i /= num; std::cout<< "in E: " << m_i << std::endl;}
    int GetInt(){return m_i;}
    friend class Singleton<E>;
private:
    E():m_i(50){}
    int m_i;

};



class D
{
public:    
    void Register(ACallback<int>& callback){m_dispatcher.Register(&callback);}
    void Unregister(ACallback<int>& callback){m_dispatcher.Unregister(&callback);}
    void NumInput(){ std::cout << "insert num" << std::endl;std::cin >> m_i; m_dispatcher.Notify(m_i);}
    friend class Singleton<D>;
private:
    D():m_i(0){}
    int m_i;
    Dispatcher<int> m_dispatcher;
};

void funcA()
{
    std::cout << "A starting" << std::endl;
    D* d = Singleton<D>::GetInstance();
    A* a = Singleton<A>::GetInstance();
    Callback<A, int> callback(*a,&A::Add);
    d->Register(callback);
    while(flag2 == 0 && a->GetInt() < 10)
    {
        ;
    }
    std::cout << "A done" << std::endl;
    ++flag; 
}
void funcB()
{
    std::cout << "B starting" << std::endl;
    D* d = Singleton<D>::GetInstance();
    B* b = Singleton<B>::GetInstance();
    Callback<B, int> callback(*b,&B::Sub);
    d->Register(callback);
    while(flag2 == 0 && b->GetInt() > 0)
    {
        ;
    }
    std::cout << "B done" << std::endl;
    ++flag;
}

void funcC()
{
    std::cout << "C starting" << std::endl;
    D* d = Singleton<D>::GetInstance();
    C* c = Singleton<C>::GetInstance();
    Callback<C, int> callback(*c,&C::Multi);
    d->Register(callback);
    while(flag2 == 0 && c->GetInt() < 50)
    {
        ;
    }
    std::cout << "C done" << std::endl;
    ++flag;
}

void funcE()
{
    std::cout << "E starting" << std::endl;
    D* d = Singleton<D>::GetInstance();
    E* e = Singleton<E>::GetInstance();
    Callback<E, int> callback(*e,&E::Div);
    d->Register(callback);
    while(flag2 == 0 && e->GetInt() > 0)
    {
        ;
    }
    std::cout << "E done" << std::endl;
    ++flag;
}
void funcD()
{
    std::cout << "D starting" << std::endl;
    D* d = Singleton<D>::GetInstance();
    while(flag != 3)
    {
        d->NumInput();
    }
    std::cout << "D done" << std::endl;
    ++flag2;
}

int main()
{
    std::thread t1(funcA);
    std::thread t2(funcB);
    std::thread t3(funcC);
    std::thread t4(funcD);
    t1.join();
    t2.join();
    std::thread t5(funcE);
    t3.join();
    t4.join();
    t5.join();

}
