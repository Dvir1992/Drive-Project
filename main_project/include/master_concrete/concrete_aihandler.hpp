#ifndef Concrete__AI__Handler__HPP
#define Concrete__AI__Handler__HPP
#include "iai_handler.hpp"
#include "uid.hpp"

class Concrete_Aihandler : public IAiHandler
{
    public:
        Concrete_Aihandler() = default;
        void SetUids(const Uid &data_uid, const Uid &mirrored_data_uid) override;
        bool operator()() override;
        ~Concrete_Aihandler() = default;
    private:
        Uid m_data_uid;
        Uid m_mirrored_data_uid;
};

#endif //IAiHandler__HPP