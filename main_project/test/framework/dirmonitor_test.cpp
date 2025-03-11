#define Singleton_ONLY_LIB
#include "dirmonitor.hpp"
#include <unistd.h>
#define DIR "/home/dvir-hazut/git/projects/ex_dir"
 
int main()
{
    Dirmonitor dr(DIR);
    DLLLoader dl;
    Callback<DLLLoader, string> callback(dl, &DLLLoader::Load) ;
    dr.Register(&callback);
    sleep(10);
    dr.Unregister(&callback);
   return 0;
}