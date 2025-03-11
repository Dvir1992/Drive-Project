#include "ai.hpp"

bool testtask()
{
    static int a = 0;
    if (a++ > 3)
    {
        return true;
    }   
    else
    {
        printf("hi\n");
        return false;
    }
    
}

int main()
{
    new Ai(testtask, std::chrono::milliseconds(500));
    sleep(10);
    return 0;
}
