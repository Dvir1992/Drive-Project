#include "singleton.hpp"
#include <thread>

class test_class
{
    public:
        test_class(const test_class & other)=delete;
        test_class& operator=(const test_class & other)=delete;
    private:
        friend Singleton<test_class>;
        test_class() = default;
};
void thread1()
{
    test_class* x = Singleton<test_class>::GetInstance();
    cout<<"th1 :"<<x<<endl;

}

void thread2()
{
    test_class* x = Singleton<test_class>::GetInstance();
    cout<<"th2 :"<<x<<endl;

}
int main()
{
    thread th_1(thread1);
    thread th_2(thread2);
    th_1.join();
    th_2.join();
    
    return 0;
}