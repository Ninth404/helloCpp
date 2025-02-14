#include"TaskQueue.h"

TaskQueue::TaskQueue(size_t queueSize)
:_queueSize(queueSize)
,_mutex()
,_notFull(_mutex)
,_notEmpty(_mutex)
{
}

TaskQueue::~TaskQueue()
{

}
void TaskQueue::push(const int & value)
{
    MutexLockGuard autoLock(_mutex);

    while(isFull())
    {
        _notEmpty.wait();
    }

    _que.push(value);

    _notEmpty.notify();
}
int TaskQueue::pop()
{
    MutexLockGuard autoLock(_mutex);

    while(isEmpty())
    {
        _notEmpty.wait();
    }

    int tmp = _que.front();
    _que.pop();
    _notFull.notify();

    return tmp;

}
bool TaskQueue::isFull() const
{
    return _queueSize == _que.size();
}

bool TaskQueue::isEmpty() const
{
    return 0 == _que.size();
}