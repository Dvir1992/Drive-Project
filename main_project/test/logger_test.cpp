#include "logger.hpp"



int main()
{
    Logger* logger = Singleton<Logger>::GetInstance();
    logger->Log(Logger::SEVERITY::INFO, "hi");

    sleep(1);
    
    logger->Log(Logger::SEVERITY::ERROR, "BADDOG");

    sleep(1);
    logger->Log(Logger::SEVERITY::WARNING, "watch out");

    return 0;
}