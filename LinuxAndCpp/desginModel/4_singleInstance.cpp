#include <iostream>

using std::cout;

class SingleInstance
{
public:
    static SingleInstance * getInstance();
    
    static void destroy();
    //对外接口
    
private:
    SingleInstance(){};
    ~SingleInstance(){};

    SingleInstance(const SingleInstance & rhs) = delete ;
    SingleInstance(const SingleInstance && rhs) = delete ;

    SingleInstance & operator=(const SingleInstance & rhs) = delete ;
    SingleInstance & operator=(const SingleInstance && rhs) = delete ;

private:
    static SingleInstance * _p_Instance;
    
};

SingleInstance * SingleInstance::getInstance()
{
    if(_p_Instance == nullptr)
    {
        _p_Instance = new SingleInstance;
    }
    
    return _p_Instance;
}

void SingleInstance::destroy()
{
    if(_p_Instance)
    {
        delete _p_Instance;
        _p_Instance = nullptr;
        cout<<"SingleInstance::destroy->_p_Instance\n";
    }
}

//饿汉式
/* SingleInstance* SingleInstance::_p_Instance = getInstance(); */

//懒汉式
SingleInstance* SingleInstance::_p_Instance = nullptr;

int main()
{
    SingleInstance *p = SingleInstance::getInstance();
    cout<<"p  ="<<p<<"\n";

    SingleInstance *p2 = SingleInstance::getInstance();
    cout<<"p2 ="<<p2<<"\n";
    
    p->destroy();
    p2->destroy();

    return 0;
}

