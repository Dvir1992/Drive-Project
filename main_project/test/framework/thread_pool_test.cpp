#include <unistd.h> /*write sleep (for testing)*/
#include <iostream> /*cout (for testing)*/
#include <string.h>/*strlen, strcpy (for testing)*/
#include "thread_pool.hpp"


class TestTask: public ThreadPool::ITPTask
{
public:
    TestTask(const char* data_){strcpy(str, data_);}
    ~TestTask(){} 
    void Run() {  mutex mutex;
    mutex.lock();write(0, str, strlen(str) +1);mutex.unlock();}

private:
 char str[100];
};

mutex g_mutex;

void func1()
{    
    g_mutex.lock();
    write(0, "this\n", strlen("this\n"));
    g_mutex.unlock();
}
void func2()
{
    g_mutex.lock();
    write(0, "is\n", strlen("is\n"));
    g_mutex.unlock();
}
void func3()
{
    g_mutex.lock();
    write(0, "working\n", strlen("working\n"));
    g_mutex.unlock();
    
}
void func4()
{
    sleep(2);

    g_mutex.lock(); 
    write(0, "like it should\n", strlen("like it should\n"));
    g_mutex.unlock();
}


int func5()
{
    sleep(6);
    return 5;
}
int func6()
{
    sleep(3);
    return 6;
}
void test1()
{
    shared_ptr<ThreadPool::ITPTask> tp4 = make_shared<TestTask>("like it should\n");
    shared_ptr<ThreadPool::ITPTask> tp3 = make_shared<TestTask>("working\n");
    shared_ptr<ThreadPool::ITPTask> tp2 = make_shared<TestTask>("is\n");
    shared_ptr<ThreadPool::ITPTask> tp1 = make_shared<TestTask>("this\n");
    ThreadPool tp;
    tp.Pause();
    tp.AddTask({tp4, ThreadPool::LOW});
    tp.AddTask({tp2,ThreadPool::MEDIUM});
    tp.AddTask({tp1,ThreadPool::HIGH});
    tp.AddTask({tp3,ThreadPool::MEDIUM});
    // sleep(2);
    tp.Resume();
    sleep(2);
}
void test2()
{
     shared_ptr<ThreadPool::ITPTask> tp4 = make_shared<ThreadPool::FuncTPTask>(func4);
    shared_ptr<ThreadPool::ITPTask> tp3 = make_shared<ThreadPool::FuncTPTask>(func3);
    shared_ptr<ThreadPool::ITPTask> tp2 = make_shared<ThreadPool::FuncTPTask>(func2);
    shared_ptr<ThreadPool::ITPTask> tp1 = make_shared<ThreadPool::FuncTPTask>(func1);
    ThreadPool tp;
    tp.Pause();
    tp.AddTask({tp4, ThreadPool::LOW});
    tp.AddTask({tp2,ThreadPool::MEDIUM});
    tp.AddTask({tp1,ThreadPool::HIGH});
    tp.AddTask({tp3,ThreadPool::MEDIUM});
    // sleep(2);
    tp.Resume();
    sleep(2);
}
void testthreadfunc(const shared_ptr<ThreadPool::FutureTPTask<int>>& tp1)
{
        cout  << tp1->Get() << endl;
}

void test3()
{
    shared_ptr<ThreadPool::FutureTPTask<int>> tp1 = make_shared<ThreadPool::FutureTPTask<int>>(func5);
    shared_ptr<ThreadPool::FutureTPTask<int>> tp2 = make_shared<ThreadPool::FutureTPTask<int>>(func6);
    ThreadPool tp;
    tp.Pause();
    thread t1(testthreadfunc,tp1);
    thread t2(testthreadfunc,tp2);
    tp.AddTask({tp1,ThreadPool::MEDIUM});
    tp.AddTask({tp2,ThreadPool::HIGH});
    sleep(1);
    tp.Resume();    
    sleep(2);
    t1.join();
    t2.join();
}
void test4()
{
    ThreadPool tp(5);
    cout<<"threads: "<<std::thread::hardware_concurrency()<<endl;
    tp.SetNumThreads(2);
    tp.SetNumThreads(5);    
    tp.Pause();
    tp.Resume();
    tp.SetNumThreads(2);
    tp.Pause();
    tp.Resume();
    tp.Pause();
    tp.Resume();
    tp.Pause();
    tp.Resume();


}
int main()
{
    // test1();
    // cout << "after test1" << endl;
    // test2();
    // cout << "after test2" << endl;
    // test3();
    // cout << "after test3" << endl;
    test4();
    cout << "after test4" << endl;

   
 }
