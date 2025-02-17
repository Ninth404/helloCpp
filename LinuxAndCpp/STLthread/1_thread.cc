#include <thread>
#include <iostream>
#include <functional>

using std::cout;
using std::thread;
using std::function;

void threadFunc(int x)
{
    cout<<"x = "<<x<<"\n";
    cout<<"tid = "<<std::this_thread::get_id()<<"\n";
}

class Example
{
public:
    void operator()(int x){
        cout<<"x = "<<x<<"\n";
        cout<<"tid = "<<std::this_thread::get_id()<<"\n";
    }
};

int main()
{
    // 1 函数指针形式
    /* typedef void (*pFunc)(int); */
    /* pFunc f = &threadFunc; */
    /* thread th(f,2); */
    
    // 2  普通函数形式
    /* thread th(threadFunc,1); */
    
    // 3 函数对象形式
    /* thread th(Example(),3); */
    
    // 4 lambda表达式形式
    /* thread th([](int x){ */
    /*           cout<<"x = "<<x<<"\n"; */
    /*           cout<<"tid = "<<std::this_thread::get_id()<<"\n"; */
    /*           },4); */


    // 5 传递function对象
    using namespace std::placeholders;
    function<void(int)> f = bind(threadFunc,_1);
    thread th(f,5);

    th.join();
    return 0;
}
