#include"Thread.h"
#include<iostream>

using std::cout;
using std::cerr;

Thread::Thread(ThreadCallback && cb)
:_tid(0)
,_isRunning(false)
,_cb(std::move(cb))
{
}

Thread::~Thread()
{
}

void Thread::start()
{
    int ret = pthread_create(&_tid,nullptr,threadFunc,this);
    if(ret)
    {
        cerr<<"pthread_create\n";
        return;
    }
    _isRunning = true;
}

void Thread::stop()
{
    if(_isRunning)
    {
        int ret = pthread_join(_tid,nullptr);
        if(ret)
        {
            cerr<<"pthread_join\n";
            return;
        }
        _isRunning = false;
    }
}

void* Thread::threadFunc(void* arg)
{
    Thread *pThread = static_cast<Thread*>(arg);
    if(pThread)
    {
        pThread->_cb();
    } 
    else
    {
        cout<<"nulltptr == pThread\n";
    }

    pthread_exit(nullptr);
}