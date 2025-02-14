#include<pthread.h>
#include<unistd.h>
#include<iostream>
#include<memory>

using std::cout;
using std::cerr;
using std::unique_ptr;

class Thread
{
public:
    Thread()
    :_tid(0)
    ,_isRunning(false)
    {
    }

    virtual ~Thread();

    void start();
    void stop();

private:
    static void* threadFunc(void *);
    virtual void run() = 0;
private:
    pthread_t _tid;
    bool _isRunning;
};

Thread::~Thread(){};

void Thread::start()
{
    int ret = pthread_create(&_tid,nullptr,threadFunc,this);
    if(ret)
    {
        cerr<<"pthread_create fail\n";
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

void* Thread::threadFunc(void * arg)
{
    Thread *pth = static_cast<Thread*>(arg);
    if(pth)
    {
        pth->run();
    }
    else
    {
        cerr<<"nullpthr == pth\n";
    }
    pthread_exit(nullptr);
}

class MyThread:public Thread
{
private:
    void run() override
    {
        int cnt = 20;
        while(--cnt)
        {
            cout<<"cnt = "<<cnt<<" MyThread is running!!!\n";
            sleep(1);
        }
    }

};

int main(void)
{
    // 栈对象
    // MyThread myThread;
    // myThread.start();
    // myThread.stop();

    //堆上创建
    unique_ptr<Thread> up(new MyThread());
    up->start();
    up->stop();
    return 0;
}