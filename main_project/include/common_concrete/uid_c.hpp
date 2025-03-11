#ifndef __UID_C_HPP__
#define __UID_C_HPP__

#include <stddef.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>


typedef struct uid
{
	uint64_t counter;
	time_t timestamp;//remember to check if there is problems with rastberry
	pid_t pid;//remember to check if there is problems with rastberry
	int64_t ip;
}my_uid_t;

extern const my_uid_t bad_uid; 

my_uid_t UID_Generate();

int UID_IsEqual(my_uid_t a, my_uid_t b);

#endif //UID_H
