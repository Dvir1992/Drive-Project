#include "dirmonitor.hpp"
#include  <dlfcn.h> 
#include <unistd.h>
#include <limits.h> //NAME_MAX
#include <string.h> //strcmp
#include <cstdio> // remove
#include <poll.h> //poll
#define BUF_LEN (10*(sizeof(struct inotify_event) + NAME_MAX + 1))


Dirmonitor::Dirmonitor(string path_name_):dir(path_name_), run(1)
{
    t = thread(&Dirmonitor::Watcher, this);
}
    
Dirmonitor::~Dirmonitor()
{
    run = 0;
    t.join();
}

void Dirmonitor::Register(ACallback<string>* callback)
{
    lock_guard<std::mutex> lock(mtx);
    m_dispatcher.Register(callback);
}

void Dirmonitor::Unregister(ACallback<string>* callback)
{
    lock_guard<std::mutex> lock(mtx);
    m_dispatcher.Unregister(callback);  
}

void Dirmonitor::Watcher()
{
    int inotify_fd = inotify_init(); //exception handling
    int wd = inotify_add_watch(inotify_fd, dir.c_str(), IN_CLOSE_WRITE);  //exception handling
    if (wd == -1) 
    {
        throw runtime_error("An error occurred in inotify_add_watch");
    }
    struct pollfd pfd;
    pfd.fd = inotify_fd;
    pfd.events = POLLIN; 
    char buffer[BUF_LEN];
    while (run) 
    {
        int poll_result = poll(&pfd, 1, 5000);
        if (poll_result == -1) 
        {
            throw runtime_error("An error occurred in poll");
        }
        if(poll_result > 0)
        {
            ssize_t length = read(inotify_fd, buffer, BUF_LEN);
            if (length == -1) 
            {
                throw runtime_error("An error occurred in read");
            }
            for (char *ptr = buffer; ptr < buffer + length; ) 
            {
                 struct inotify_event *event = (struct inotify_event *)ptr;
                lock_guard<std::mutex> lock(mtx);
                m_dispatcher.Notify(dir + "/" + event->name);
                ptr += sizeof(struct inotify_event) + event->len;
            }
        }
    }
    cout<<"GOOD BYE"<<endl;
}


DLLLoader::DLLLoader():handle(nullptr){}

void DLLLoader::Load(const string& libary)
{
    handle = dlopen(libary.c_str(), RTLD_LAZY);  
    if (nullptr == handle) 
    {
        throw runtime_error("An error occurred in dlopen");
    }
}

DLLLoader::~DLLLoader()
{
    if (handle != nullptr)
    {
            dlclose(handle);
    }
}


