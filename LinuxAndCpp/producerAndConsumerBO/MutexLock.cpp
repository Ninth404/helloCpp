#include"MutexLock.h"

#include<iostream>

using std::cerr;
MutexLock::MutexLock()
{
    int ret = pthread_mutex_init(&_mutex,nullptr);
    if(ret)
    {
        cerr<<"pthread_mutex_init\n";
        return;
    }
}
MutexLock::~MutexLock()
{
    int ret = pthread_mutex_destroy(&_mutex);
    if(ret)
    {
        cerr<<"pthread_mutex_destory\n";
        return;
    }
}
void MutexLock::lock()
{
    int ret = pthread_mutex_lock(&_mutex);
    if(ret)
    {
        cerr<<"pthread_mutex_lock\n";
        return;
    }
}

void MutexLock::unlock()
{
    int ret = pthread_mutex_unlock(&_mutex);
    if(ret)
    {
        cerr<<"pthread_mutex_unlock\n";
        return;
    }
}
void MutexLock::trylock()
{
    int ret = pthread_mutex_trylock(&_mutex);
    if(ret)
    {
        cerr<<"pthread_mutex_trylock";
        return;
    }
}
pthread_mutex_t* MutexLock::getMutexLockPtr()
{
    return &_mutex;
}
