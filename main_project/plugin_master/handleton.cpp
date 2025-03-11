#define Singleton_ONLY_LIB
#include "../include/singleton.hpp"
#include "../include/factory.hpp"
#include "../include/common_concrete/amessage.hpp"
#include "../include/framework/icommand.hpp"
#include "../include/framework/scheduler.hpp"
#include "../include/framework/thread_pool.hpp"
#include "../include/master_concrete/raid01.hpp"
#include "../include/master_concrete/responseproxy.hpp"
#include "../include/master_concrete/nbdproxy.hpp"
#include "../include/master_concrete/response_manager.hpp"
#include "../include/nbd/nbd_server.hpp"
#include "../include/master_concrete/iai_handler.hpp"


template class  Singleton<Factory<KEY, std::shared_ptr<ICommand>>>;
template class  Singleton<Factory<KEY,std::shared_ptr<AMessage>, uint64_t>>;
template class  Singleton<Scheduler>;
template class  Singleton<ThreadPool>;
template class  Singleton<Raid01>;
template class  Singleton<ResponseProxy>;
template class  Singleton<NBDProxy>;
template class  Singleton<NBDServer>;
template class  Singleton<ResponseManager>;