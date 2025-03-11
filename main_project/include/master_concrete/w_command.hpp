#ifndef __W__COMMAND__HPP
#define __W__COMMAND__HPP
#include <memory>
#include "icommand.hpp"
#include "iai_handler.hpp"
class W_Command : public ICommand 
{
    public:

        explicit W_Command(std::shared_ptr<IAiHandler> ai_handler);
        W_Command(const W_Command& other_) = delete;
        W_Command& operator=(const W_Command& other_) =  delete;
        std::pair<std::function<bool()>, std::chrono::milliseconds> Execute(std::shared_ptr<IArgs>) override; 
        ~W_Command() override = default;
    private:
        std::shared_ptr<IAiHandler> m_ai_handler;
} ;
#endif //__W__COMMAND__HPP