#include "/home/dvir-hazut/git/main_project/include/singleton.hpp"
#include "/home/dvir-hazut/git/main_project/include/factory.hpp"
#include "/home/dvir-hazut/git/main_project/include/framework/icommand.hpp"

typedef enum {
    A,
    B,
    C
} KEY;
bool ai_function()
{
    static int a = 0;
    if (a++ > 3)
    {
        cout<<"finished- for new version\n";
        return true;
    }   
    else
    {
        cout<<"not finished yet - for new version\n";
        return false;
    }
    
}

class ArgsKey_A : public IArgs
{
    public:
        ArgsKey_A(const string& s):args(s){}
        KEY GetKey() const{return A;}
        string GetToPrint(){return args;}
    private:
        
        string args;
};


class Command_B: public ICommand
{
    public:
        std::pair<std::function<bool()>,std::chrono::milliseconds> Execute(std::shared_ptr<IArgs> task_args) const override
        {
            std::shared_ptr<ArgsKey_A> p_args_a = std::dynamic_pointer_cast<ArgsKey_A>(task_args);        
            if (p_args_a)
            {
                // Get conrete args using getters:
                cout<<p_args_a->GetToPrint();
                // operate on minion
                cout<<"lets use arguments for command on minions - new version\n";
            }        
            return std::make_pair(nullptr, std::chrono::milliseconds(200));
        }
        ~Command_B() override = default;
}; 

shared_ptr<ICommand> CreateCommand_B()
{
     return std::make_shared<Command_B>(); 
}


void __attribute((constructor))Main()
{
    std::cout << "insideMainLibrary\n";
    Singleton<Factory<int, std::shared_ptr<ICommand>>>::GetInstance()->Add(0,CreateCommand_B);

}
