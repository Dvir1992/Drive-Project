#ifndef FACTORY__HPP_
#define FACTORY__HPP_
#include <functional>
#include <stdexcept>
#include <map>

template <typename KEY, typename BASE, typename ...ARGS>
class Factory
{
    public:
        Factory() = default;
        ~Factory() = default;
        Factory& operator=(const Factory & other_) = delete;
        Factory(const Factory & other_) = delete;
        BASE Create(KEY key, ARGS... args);
        void Add(KEY key, std::function<BASE(ARGS...)> func_p);
    private:
        std::map<KEY, std::function<BASE(ARGS...)>> mp;
};


template <typename KEY, typename BASE, typename ...ARGS>
BASE Factory<KEY, BASE, ARGS...>::Create(KEY key, ARGS... args)
 {
    auto it = mp.find(key);
    if (it == mp.end()) {
        throw std::out_of_range("Function not found");
    }
    return mp[key](args...);
 }

 template <typename KEY, typename BASE, typename ...ARGS>
void Factory<KEY, BASE, ARGS...>::Add(KEY key, std::function<BASE(ARGS...)> func_p)
{
    mp[key] = func_p;
}

#endif