#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include<vector>
#include<memory>

#include"TaskQueue.h"

using std::vector;
using std::unique_ptr;

class Thread;

class ThreadPool
{
    friend class WorkThread;
public:
    ThreadPool(size_t threadNum,size_t queueSize);
    ~ThreadPool();

    void start();
    void stop();
    void addTask(Task* pTask);
private:
    Task* getTask();
    void doTask();
private:
    size_t _threadNum;
    size_t _queueSize;
    vector<unique_ptr<Thread>> _threads;    
    TaskQueue _taskQue;
    bool _isExit;
};

#endif
