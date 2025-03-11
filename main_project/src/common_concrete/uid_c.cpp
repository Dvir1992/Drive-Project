#include <atomic> // Use the C++ header instead of <stdatomic.h>
#include "uid_c.hpp"

const my_uid_t bad_uid = {0, 0, 0, 0};

my_uid_t UID_Generate() 
{
    static std::atomic<size_t> counter(0); // Use std::atomic<size_t>
    my_uid_t uid = {0, 0, 0, 0};

    uid.counter = counter.fetch_add(1);

    uid.timestamp = time(NULL);
    if (((time_t)-1) == uid.timestamp) {
        return bad_uid;
    }

    uid.pid = getpid();

    uid.ip = gethostid();
    if (-1 == uid.ip) {
        return bad_uid;
    }

    return uid;
}

int UID_IsEqual(my_uid_t a, my_uid_t b)
{
	if(a.counter != b.counter)
	{
		return 0;
	}
	if(a.timestamp != b.timestamp)
	{
		return 0;
	}
	if(a.pid != b.pid)
	{
		return 0;
	}
	if(a.ip != b.ip)
	{
		return 0;
	}
	return 1;
}
