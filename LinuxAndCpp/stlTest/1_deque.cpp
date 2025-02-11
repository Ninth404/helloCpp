#include<iostream>
#include<deque>
#include<vector>

using std::cout;
using std::deque;
using std::vector;

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

void visit(deque<int> deq)
{   
    // deque遍历
    // // 1.下标
    // for(size_t idx = 0;idx!=deq.size();++idx)
    // {
    //     // cout<<vec[idx]<<" ";
    //     cout<<deq.at(idx)<<" ";
    // }

    // //2.迭代器
    // for(deque<int>::iterator it = deq.begin();it!=deq.end();++it)
    // {
    //     cout<<*it<<" ";
    // }

    //3.增强for循环
    for(auto & d : deq)
    {
        cout<<d<<" ";
    }
    cout<<"\n";
}

void test0()
{
    // 初始化
    //  1、创建一个空对象
    deque<int> deq0;
    // 2、创建count个value
    deque<int> deq1(3,1);
    // 3、迭代器范围
    vector<int> vec(3,2);
    deque<int> deq2(vec.begin(),vec.end());
    // 4、使用大括号
    deque<int> deq3 = {1,2,3,4,5};

    cout<<"deq0 :";
    visit(deq0);
    cout<<"deq1 :";
    visit(deq1);
    cout<<"deq2 :";
    visit(deq2);
    cout<<"deq3 :";
    visitT(deq3);

}

void test1()
{
    deque<int> deq = {1,2,3,4,5};
    cout<<"front = "<<deq.front()<<"\n";
    cout<<"back = "<<deq.back()<<"\n";

    deq.push_back(6);
    deq.push_front(0);
    
    deq.pop_back();

    visitT(deq);

    deque<int>::iterator it = deq.begin();
    ++it;
    ++it;
    deq.erase(it);
    visitT(deq);

    deque<int> deqTemp = {10,9,8,7,6};
    deq.swap(deqTemp);
    cout<<"after swap : \n";
    visit(deq);
    visit(deqTemp);

}

int main(void)
{   
    test1();
    return 0;
}

