#include "logger.hpp"
#include <sstream>

const string& Logger::Message::GetMessage()
{
    return message;
}

const string& Logger::Message::StrToLog()
{
    return str_to_log;
}
Logger::Message::Message():message(""), str_to_log(""){}

Logger::Message::Message(SEVERITY severity_, const std::string& string_to_log_):str_to_log(string_to_log_)
{
    auto now = chrono::system_clock::now();
    std::time_t now_time_t = chrono::system_clock::to_time_t(now);
    std::tm local_time = *localtime(&now_time_t);
    ostringstream oss;
    oss<<put_time(&local_time, "%Y-%m-%d %H:%M:%S ");
    message = Get_StrSeverity(severity_) + oss.str() + string_to_log_ + '\n';
}
 
string Logger::Message::Get_StrSeverity(Logger::SEVERITY sev)
{
    switch (sev) 
    {
        case Logger::SEVERITY::INFO:   return "INFO: ";
        case Logger::SEVERITY::WARNING: return "WARNING: ";
        case Logger::SEVERITY::ERROR:  return "ERROR: ";
        default:    return "Unknown"; 
    }
}

Logger::Logger()
{
    t = make_shared<thread>([this](){Write();}); 
}

void Logger::Log(SEVERITY severity, const std::string& string_to_log)
{
    Message msg(severity, string_to_log);
    q.Push(msg);
}



void Logger::Write()
{
    remove("./log.txt");
    try
    {
        file = fopen("./log.txt","a");
        if (file == nullptr) 
        {
            throw std::runtime_error("Failed to open the log file.");
        }
        Message out;
        while(out.StrToLog() != "_EOF_\n")
        {
            q.Pop(out);
            fprintf(file, "%s",out.GetMessage().c_str());
        }
    }
    catch (const std::exception& e) 
    {
        std::cerr << "Error while writing to the log: " << e.what() << std::endl;
        fclose(file);   
    }
}

Logger::~Logger()
{
    Message s(Logger::SEVERITY::INFO,"_EOF_\n");
    q.Push(s);
    t->join();
    if(file != nullptr)
    {
        fclose(file);
    }
}

