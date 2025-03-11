#include <fstream>
#include "m_r_command.hpp"
#include "m_r_args.hpp"
#include "singleton.hpp"
#include "masterproxy.hpp"
#define TRUE 49
#define FALSE 48

std::pair<std::function<bool()>, std::chrono::milliseconds> MR_Command::Execute(std::shared_ptr<IArgs> args) 
{
    std::shared_ptr<MR_args> r_args = std::dynamic_pointer_cast<MR_args>(args); 
    uint8_t status = TRUE;
    if (r_args)
    {
        fstream &m_disk = r_args->GetMP()->GetDisk();
        std::shared_ptr<uint8_t[]> buffer(new uint8_t[r_args->GetSize()]);
        m_disk.seekg(r_args->GetOffset(), ios::beg);
        if (m_disk.fail()) 
        {
            std::cerr << "Failed to set input position." << std::endl;
            m_disk.clear();
            status = FALSE;
        }
        m_disk.read(reinterpret_cast<char*>(buffer.get()), r_args->GetSize());
        if (m_disk.fail()) 
        {
            std::cerr << "Failed to read from the file." << std::endl;
            m_disk.clear();
            status = FALSE;

        }
        r_args->GetMP()->ReadResponse(buffer, r_args->GetSize(), status);
    }  
    return std::make_pair(nullptr, std::chrono::milliseconds(200)); //handle it
}