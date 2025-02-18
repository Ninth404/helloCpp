#include <iostream>

using std::cout;

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

template<class T>
class RAII
{
public:
    //1. 构造函数中初始化资源(托管资源)
    RAII(T * ptr)
    :_ptr(ptr)
    {
    }

    //2. 析构函数中释放资源
    ~RAII()
    {
        if(_ptr)
        {
            delete _ptr;
            _ptr = nullptr;
        }
    }

    //3. 提供若干资源访问的方式
    T* operator->()
    {
        return _ptr;
    }

    T & operator*()
    {
        return *_ptr;
    }

    T * get() const
    {
        return _ptr;
    }

    void set(T * ptr)
    {
        if(_ptr)
        {
            delete _ptr;
            _ptr = nullptr;
        }

        _ptr = ptr;
    }

    //不允许复制与赋值
    RAII(const RAII & rhs) = delete;
    RAII & operator=(const RAII & rhs) = delete ;
private:
    T * _ptr;
};

void test0()
{
    Point<int> *pt = new Point<int>(1,2);

    RAII<Point<int>> raii(pt);

    raii->display();
    (*raii).display();
}

int main()
{
    test0();
    return 0;
}

