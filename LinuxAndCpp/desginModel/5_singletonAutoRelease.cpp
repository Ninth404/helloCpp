#include "pthread.h"

#include <iostream>

using std::cout;
/**
 *Linux平台可以使用 保证创建单例对象时的多线程安全
 *自动回收单例对象
 */
class SingletonAutoRelease
{
public:
    static SingletonAutoRelease * getInstance();
    
    static void init();
    //对外接口
    
private:
    static void destroy();

    SingletonAutoRelease(){};
    ~SingletonAutoRelease(){};

    SingletonAutoRelease(const SingletonAutoRelease & rhs) = delete ;
    SingletonAutoRelease(const SingletonAutoRelease && rhs) = delete ;

    SingletonAutoRelease & operator=(const SingletonAutoRelease & rhs) = delete ;
    SingletonAutoRelease & operator=(const SingletonAutoRelease && rhs) = delete ;

private:
    static SingletonAutoRelease * _p_Instance;
    static pthread_once_t _once;
};

SingletonAutoRelease * SingletonAutoRelease::getInstance()
{
    pthread_once(&_once,init); 

    return _p_Instance;
}

void SingletonAutoRelease::destroy()
{
    if(_p_Instance)
    {
        delete _p_Instance;
        _p_Instance = nullptr;
        cout<<"SingletonAutoRelease::destroy\n";
    }
}

void SingletonAutoRelease::init()
{
    _p_Instance = new SingletonAutoRelease;
    atexit(destroy);
}

//饿汉式
/* SingletonAutoRelease* SingletonAutoRelease::_p_Instance = getInstance(); */

//懒汉式
SingletonAutoRelease* SingletonAutoRelease::_p_Instance = nullptr;
pthread_once_t SingletonAutoRelease::_once = PTHREAD_ONCE_INIT;

int main()
{
    SingletonAutoRelease *p = SingletonAutoRelease::getInstance();
    cout<<"p  ="<<p<<"\n";

    SingletonAutoRelease *p2 = SingletonAutoRelease::getInstance();
    cout<<"p2 ="<<p2<<"\n";

    return 0;
}

