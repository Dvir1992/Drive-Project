#ifndef __MR_COMMAND__HPP
#define __MR_COMMAND__HPP
#include "icommand.hpp"
class MR_Command : public ICommand 
{
    public:
        ~MR_Command() override = default;
        explicit MR_Command() = default;
        MR_Command(const MR_Command& other_) = delete;
        MR_Command& operator=(const MR_Command& other_) =  delete;
        std::pair<std::function<bool()>, std::chrono::milliseconds> Execute(std::shared_ptr<IArgs>) override;   
    private:
       
} ;
#endif //__MR_COMMAND__HPP