#include<iostream>
#include<list>

using std::cout;
using std::list;

//模板函数
template <class T>
void visitT(T con)
{
    for(auto & c : con)
    {
        cout<<c<<" ";
    }
    cout<<"\n";
}

struct compareList
{
    bool operator()(const int &lhs,const int & rhs) const
    {
        //grater
        return lhs>rhs;
        //less
        //return lhs<rhs;
    }
};

void test0()
{
    list<int> li = {1,4,3,2,5,5};
    cout<<"li = \n";
    visitT(li);

    cout<<"after reverse:\n";
    li.reverse();
    visitT(li);
    
    cout<<"after list::sort(std::less)\n";
    li.sort();
    visitT(li);

    cout<<"after list::sort(compareList())\n";
    li.sort(compareList());
    visitT(li);

    cout<<"after unique\n";
    li.unique();
    visitT(li);

    // cout<<"merge\n";
    list<int> liTemp = {10,9,6,8,7};
    // li.merge(liTemp);
    // li.sort();
    // visitT(li);

    li.splice(li.end(),liTemp);
    visitT(li);
}

int main()
{
    test0();
    return 0;
}