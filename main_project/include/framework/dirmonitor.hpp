#ifndef DIRMONITOR__HPP__
#define DIRMONITOR__HPP__
#include <iostream>
#include <sys/inotify.h>
#include <mutex>
#include <thread>
#include<atomic>
using namespace std;
#include "dispatcher.hpp"




class Dirmonitor
{
    public:
        Dirmonitor(string path_name_);
        ~Dirmonitor();
        Dirmonitor(const Dirmonitor & other_)=delete;
        Dirmonitor& operator=(const Dirmonitor & other_) = delete;
        void Register(ACallback<string>* callback);
        void Unregister(ACallback<string>* callback);
        void Watcher();
    private:
        string dir;
        Dispatcher<string> m_dispatcher;
        thread t;
        mutex mtx;
        atomic_bool run;
};

class DLLLoader
{
    public:
        DLLLoader();
        ~DLLLoader();
        DLLLoader(const DLLLoader & other_)=delete;
        DLLLoader& operator=(const DLLLoader & other_) = delete;
        void Load(const string& libary);
    private:
        void* handle;
};


#endif