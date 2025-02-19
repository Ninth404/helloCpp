#include <iostream>
#include <vector>
#include <memory>

using std::cout;
using std::vector;
using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;

template<class T>
class Point
{
public:
    Point(T x,T y)
    :_x(x)
    ,_y(y)
    {

    }

    void display()
    {
        cout<<"("<<_x<<","<<_y<<")\n";
    }

    T getDistance();

private:
    T _x;
    T _y;
};

void test0()
{//unique_ptr
    unique_ptr<int> up(new int(10));

    cout<<"*up = "<<*up<<"\n";
    cout<<"up.get() = "<<up.get()<<"\n";
    
    vector<unique_ptr<Point<int>>> vecP;
    unique_ptr<Point<int>> upPoint(new Point<int>(2,2));
    vecP.push_back(std::move(upPoint));

    vecP.push_back(unique_ptr<Point<int>>(new Point<int>(1,1)));

    for(auto & p : vecP)
    {
        if(p)
        {
            p->display();
        }
    }
}

class Derived;

class Base
{
public:
    Base(){};
    ~Base(){};
    shared_ptr<Derived> sp;
};

class Derived
{
public:
    Derived(){};
    ~Derived(){};
    /* shared_ptr<Base> sp; */
    weak_ptr<Base> wp;
};

void test1()
{
    //shared_ptr & weak_ptr 解决shared_ptr循环引用问题
    shared_ptr<Base> BasePtr(new Base());
    shared_ptr<Derived> DerivedPtr(new Derived());
    //获取到的引用计数都是1
    cout << "BasePtr.use_count():" << BasePtr.use_count() << "\n";
    cout << "DerivedPtr.use_count():" << DerivedPtr.use_count() << "\n";
    BasePtr->sp = DerivedPtr;
    DerivedPtr->wp= BasePtr;
    //获取到的引用计数都是2
    cout << "BasePtr.use_count():" << BasePtr.use_count() << "\n";
    cout << "DerivedPtr.use_count():" << DerivedPtr.use_count() << "\n"; 
}

void test2()
{
    //weak_ptr up
    weak_ptr<int> wp;
    shared_ptr<int> sp(new int(2));
    wp = sp;
    
    shared_ptr<int> sp2 = wp.lock();
    if(sp2)
    {
        cout<<"Success\n";
        cout<<"*sp2 = "<<*sp2<<"\n";
    }
    else
    {
        cout<<"Failed\n";
    }
}
int main()
{
    /* test0(); */
    /* test1(); */
    test2();
    return 0;
}

