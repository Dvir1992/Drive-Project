#define Singleton_ONLY_LIB
#include "../include/singleton.hpp"
#include "../include/factory.hpp"
#include "../include/common_concrete/amessage.hpp"
#include "../include/framework/icommand.hpp"
#include "../include/framework/scheduler.hpp"
#include "../include/framework/thread_pool.hpp"
#include "../include/keys.hpp"

template class  Singleton<Factory<KEY, std::shared_ptr<ICommand>>>;
template class  Singleton<Factory<KEY,std::shared_ptr<AMessage>, uint64_t>>;
template class  Singleton<Scheduler>;
template class  Singleton<ThreadPool>;

