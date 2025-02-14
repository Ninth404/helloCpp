#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__

#include<iostream>
#include<queue>
#include"MutexLock.h"
#include"Condition.h"

using std::queue;

class TaskQueue
{
public:
    TaskQueue(size_t queueSize);
    ~TaskQueue();
    void push(const int & value);
    int pop();
    bool isFull() const;
    bool isEmpty() const;
private:
    size_t _queueSize;
    queue<int> _que;
    MutexLock _mutex;
    Condition _notFull;
    Condition _notEmpty;
};

#endif