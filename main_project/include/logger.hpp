#define Singleton_ONLY_LIB
#include "singleton.hpp"
#include "waitable_queue.hpp"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <thread>
#include <unistd.h>

class Logger 
{
    public:
        Logger(const Logger & other)=delete;
        Logger& operator=(const Logger & other)=delete;
        ~Logger();
        enum class SEVERITY
        {
            INFO,
            WARNING,
            ERROR,
        };
        class Message
        {
            public:
                Message();
                Message(SEVERITY severity_, const std::string& string_to_log_);
                const string& GetMessage();
                const string& StrToLog();
            private:
                string Get_StrSeverity(SEVERITY sev);
                string message;
                string str_to_log;
        };
        void Log(SEVERITY severity, const std::string& string_to_log);
        void Write();
    private:
        Logger();
        friend Singleton<Logger>;
        Waitable_queue<Message> q;
        FILE* file;
        shared_ptr<thread> t;
        string is_finish;
};
