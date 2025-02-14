#ifndef __MUTEXLOCK_H__
#define __MUTEXLOCK_H__

#include<pthread.h>

#include"NoCopyable.h"

class MutexLock
:NonCopyable
{
public:
    MutexLock();
    ~MutexLock();
    void lock();
    void unlock();
    void trylock();
    pthread_mutex_t* getMutexLockPtr();
private:
    pthread_mutex_t _mutex;
};

class MutexLockGuard
{
public:
    MutexLockGuard(MutexLock &mutex)
    : _mutex(mutex)
    {
        _mutex.lock();
    }

    ~MutexLockGuard()
    {
        _mutex.unlock();
    }
private:
    MutexLock &_mutex;
};
#endif