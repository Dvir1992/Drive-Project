#include <fstream>
#include "m_w_command.hpp"
#include "m_w_args.hpp"
#include "singleton.hpp"
#include "masterproxy.hpp"
#define TRUE 49
#define FALSE 48

std::pair<std::function<bool()>, std::chrono::milliseconds> MW_Command::Execute(std::shared_ptr<IArgs> args)
{
   std::shared_ptr<MW_args> w_args = std::dynamic_pointer_cast<MW_args>(args);
    uint8_t status = TRUE;
    if (w_args)
    {
        fstream &m_disk = w_args->GetMP()->GetDisk();
        m_disk.seekp(w_args->GetOffset(), ios::beg);
        if (m_disk.fail()) 
        {
            std::cerr << "Failed to set input position." << std::endl;
            m_disk.clear();
            status = FALSE;
            
        }
        for(uint64_t i = 0; i < w_args->GetSize(); ++i)
        {
            m_disk.write(reinterpret_cast<char*>(w_args->GetData().get() + i), 1);
        }
        if (m_disk.fail()) 
        {
            std::cerr << "Failed to write to the file." << std::endl;
            m_disk.clear();
            status = FALSE;
        }
        w_args->GetMP()->WriteResponse(status);
    }  
    return std::make_pair(nullptr, std::chrono::milliseconds(200)); //handle it
}