#include<unistd.h>
#include<iostream>

#include"ThreadPool.h"
#include "WorkThread.h"
#include "Task.h"

using std::cout;

ThreadPool::ThreadPool(size_t threadNum,size_t queueSize)
:_threadNum(threadNum)
,_queueSize(queueSize)
,_threads()
,_taskQue(_queueSize)
,_isExit(false)
{
    _threads.reserve(_threadNum);
}

ThreadPool::~ThreadPool()
{
}

void ThreadPool::start()
{
    for(size_t i = 0 ;i!=_threadNum;++i)
    {
        _threads.push_back(unique_ptr<Thread>(new WorkThread(*this)));
    }

    for(auto & th:_threads)
    {
        th->start();
    }
}

void ThreadPool::stop()
{
    //如果任务未执行完，子线程不能退出
    while(!_taskQue.empty())
    {
        sleep(1);
    }
    
    _isExit = true;
    //回收之前将所有工作线程唤醒
    _taskQue.wakeup();

    //将工作线程停止
    for(auto & th:_threads)
    {
        th->stop();
    }
}
void ThreadPool::addTask(Task* pTask)
{   
    if(pTask)
    {
        _taskQue.push(pTask);
    }
}
Task* ThreadPool::getTask()
{   
    //pop获取并删除
    return _taskQue.pop();
}
void ThreadPool::doTask()
{
    //用的是线程池是否退出的标志位???
    //子线程（工作线程）在获取完任务之后，那么任务队列就为空
    //接下来子线程会执行任务，也就是执行process函数，而主线程
    //会执行stop函数中的将标志位_isExit设置为true的操作。如果
    //子线程执行process的速率非常慢，那么当子线程执行任务之前
    //主线程已经将标志位设置为了true，那么子线程就不会进入到
    //while循环中，那么程序就可以正常结束；如果子线程执行任务
    //process的速率非常的快，但是主线程还没有将标志位设置为
    //true，那么子线程执行完process后，又进入了while循环，在
    //执行getTask的时候，也就是会执行TaskQueue中的pop，然后
    //睡眠

    while(!_isExit)
    {
        Task *pTask = getTask();
        if(pTask)
        {
            pTask->process();//执行任务
            /* sleep(3); */
        }
        else
        {
            cout << "nullptr == ptask \n";
        }
    }
}
