#include <math.h>
#include<iostream>
#include<set>

using std::set;
using std::cout;

//模板函数
template <class T>
void visitT(const T & con)
{
    for(auto & c : con)
    {
        cout<<c<<" ";
    }
    cout<<"\n";
}

void test0()
{
    set<int> num = {1,2,2,3,3,4,5};
    size_t cnt = num.count(10);
    cout<<"count cnt = "<<cnt<<"\n";

    //查找操作
    set<int>::iterator it = num.find(10);
    if(it != num.end())
    {
        cout<<"find success\n";
    }
    else
    {
        cout<<"find fail\n";
    }
}


void test1()
{
    set<int> num = {1,2,2,3,3,4,5};

    std::pair<set<int>::iterator,bool> ret = num.insert(2);
    if(ret.second)
    {
        cout<<"insert success\n";
        cout<<"insert is *it = "<<*ret.first<<"\n";
    }
    else
    {
        cout<<"insert fail\n";
    }
}

void test2()
{
    set<int> num = {1,2,2,3,3,4,5};
    set<int>::iterator it = num.begin();
    ++it;
    ++it;
    num.erase(it);
    visitT(num);
}

//set 不支持修改 为了红黑树稳定性
//set 不支持下标操作

class Point
{
public:
    Point(int x,int y)
    :_x(x)
    ,_y(y)
    {}

    float getX() const 
    {
        return _x;
    }

    float getY() const 
    {
        return _y;
    }

    float getDistance() const
    {
        return hypot(_x, _y);
    }

    // friend
    // bool operator<(const Point & lhs,const Point & rhs);

    friend
    std::ostream & operator<<(std::ostream & os,const Point & rhs);

    friend struct comparePoint;

private:
    int _x;
    int _y;
};

std::ostream & operator<<(std::ostream & os,const Point & rhs)
{
    os<<"("<<rhs._x<<","<<rhs._y<<")";
    return os;
}

// 1.运算符重载版本
// bool operator<(const Point &lhs, const Point &rhs)
// {
//     if(lhs.getDistance() < rhs.getDistance())
//     {
//         return true;
//     }
//     else if(lhs.getDistance() == rhs.getDistance())
//     {
//         if(lhs._x < rhs._x)
//         {
//             return true;
//         }
//         else if(lhs._x == rhs._x)
//         {
//             if(lhs._y < rhs._y)
//             {
//                 return true;
//             }
//             else
//             {
//                 return false;
//             }
//         }
//         else
//         {
//             return false;
//         }
//     }
//     else
//     {
//         return false;
//     }
// }

// 2.函数对象版本
struct comparePoint
{
    bool operator()(const Point & lhs,const Point & rhs)
    {
        if(lhs.getDistance() < rhs.getDistance())
    {
        return true;
    }
    else if(lhs.getDistance() == rhs.getDistance())
    {
        if(lhs._x < rhs._x)
        {
            return true;
        }
        else if(lhs._x == rhs._x)
        {
            if(lhs._y < rhs._y)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    }
};

namespace  std
{
//模板的全特化（将模板参数列表中的参数全部以特殊版本的形式展现出来）
template <>
struct less<Point>
{
    bool operator()( const Point& lhs, const Point& rhs ) const
    {
        if(lhs.getDistance() < rhs.getDistance())
        {
            return true;
        }
        else if(lhs.getDistance() == rhs.getDistance())
        {
            if(lhs.getX() < rhs.getX())
            {
                return true;
            }
            else if(lhs.getX() == rhs.getX())
            {
                if(lhs.getY() < rhs.getY())
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
};
}

void test3()
{
    //set对于自定义类型

    Point pt1(1,1);
    Point pt2(2,2);
    Point pt3(3,3);
    Point pt4(1,4);
    Point pt5(2,1);

    set<Point> pointSet = {pt1,pt3,pt2,pt4,pt5};
    // set<Point,comparePoint> pointSet = {pt1,pt3,pt2,pt4,pt5};
    visitT(pointSet);

}

int main(void)
{
    test3();
    return 0;
}