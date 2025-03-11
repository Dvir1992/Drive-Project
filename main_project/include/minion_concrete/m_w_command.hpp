#ifndef __MW_COMMAND__HPP
#define __MW_COMMAND__HPP
#include "icommand.hpp"
class MW_Command : public ICommand 
{
    public:
        ~MW_Command() override = default;
        explicit MW_Command() = default;
        MW_Command(const MW_Command& other_) = delete;
        MW_Command& operator=(const MW_Command& other_) =  delete;
        std::pair<std::function<bool()>, std::chrono::milliseconds> Execute(std::shared_ptr<IArgs>) override;
    private:
        
        
} ;
#endif //__MW_COMMAND__HPP