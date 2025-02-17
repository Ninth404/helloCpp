#include <thread>
#include <iostream>
#include <functional>
#include <mutex>

using std::cout;
using std::thread;
using std::function;
using std::mutex;


mutex mtx;
int gCnt = 0;

void threadFunc()
{
    for(int i = 0;i<1000000;++i)
    {
        mtx.lock();
        ++gCnt;
        mtx.unlock();
    }
}

int main()
{
    typedef void(*pFunc)(void);
    pFunc f  = &threadFunc;
    thread th(f);

    thread th2(f);

    th.join();
    th2.join();

    cout<<"gCnt = "<<gCnt<<"\n";

    return 0;
}
