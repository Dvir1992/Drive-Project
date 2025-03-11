#ifndef __R_COMMAND__HPP
#define __R_COMMAND__HPP
#include <memory>
#include "iai_handler.hpp"
#include "icommand.hpp"

class R_Command : public ICommand 
{
    public:
        explicit R_Command(std::shared_ptr<IAiHandler> ai_handler);
        R_Command(const R_Command& other_) = delete;
        R_Command& operator=(const R_Command& other_) =  delete;
        std::pair<std::function<bool()>, std::chrono::milliseconds> Execute(std::shared_ptr<IArgs>) override;  
        ~R_Command() override = default;   
    private:
        std::shared_ptr<IAiHandler> m_ai_handler;
};
#endif //____R_COMMAND__HPP