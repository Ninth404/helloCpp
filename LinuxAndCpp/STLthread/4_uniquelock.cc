#include <thread>
#include <iostream>
#include <mutex>

using std::cout;
using std::thread;
using std::mutex;
using std::unique_lock;

mutex mtx;
int gCnt = 0;

void threadFunc()
{
    for(int i = 0;i<1000000;++i)
    {
        unique_lock<mutex> ul(mtx);
        ++gCnt;
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
