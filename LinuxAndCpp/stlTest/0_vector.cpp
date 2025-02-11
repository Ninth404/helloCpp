#include <iostream>
#include <vector>

using std::cout;
using std::vector;

void visit(vector<int> vec)
{
    // vector遍历

    // 1.下标
    for(size_t idx = 0;idx!=vec.size();++idx)
    {
        // cout<<vec[idx]<<" ";
        cout<<vec.at(idx)<<" ";
    }

    // 2.迭代器
    // for(vector<int>::iterator it = vec.begin();it!=vec.end();++it)
    // {
    //     cout<<*it<<" ";
    // }

    // 3.增强for循环
    // for(auto & v : vec)
    // {
    //     cout<<v<<" ";
    // }

    cout<<"\n";
}

void test0()
{
    //vector初始化
    // 1、创建一个空对象
    vector<int> vec1;
    // 2、创建count个value
    vector<int> vec2(5,2);
    vector<int> vec3(5);
    // 3、迭代器范围
    int arr[] = {1,2,3};
    vector<int> vec4(arr,arr+sizeof(arr)/sizeof(int));

    vector<int> vec5(vec3.begin(),vec3.end());
    // 4、使用大括号   
    vector<int> vec6 = {1,2,3,3,4,5,6};
    
    //遍历测试
    // cout<<"vec1 = ";visit(vec1);
    // cout<<"vec2 = ";visit(vec2);
    // cout<<"vec3 = ";visit(vec3);
    // cout<<"vec4 = ";visit(vec4);
    // cout<<"vec5 = ";visit(vec5);
    // cout<<"vec6 = ";visit(vec6);

    //成员函数测试
    // vec2.reserve(15);
    // cout<<"size = "<<vec2.size()<<" ,capacity = "<<vec2.capacity()<<"\n";

    // cout<<"before push_back: vec2 = ";visit(vec2);
    // vec2.push_back(0);
    // cout<<"after  push_back: vec2 = ";visit(vec2);

    // cout<<"front = "<<vec2.front()<<"\n";
    // cout<<"end = "<<vec2.back()<<"\n";

    // cout<<"before pop_back: vec2 = ";visit(vec2);
    // vec2.pop_back();
    // cout<<"after  pop_back: vec2 = ";visit(vec2);

    // cout<<"size = "<<vec2.size()<<" ,capacity = "<<vec2.capacity()<<"\n";
    // vec2.shrink_to_fit();
    // cout<<"size = "<<vec2.size()<<" ,capacity = "<<vec2.capacity()<<"\n";
    // vec2.resize(4);
    // cout<<"after  resize: vec2 = ";visit(vec2);
    // cout<<"size = "<<vec2.size()<<" ,capacity = "<<vec2.capacity()<<"\n";
    // cout<<"size = "<<vec5.size()<<" ,capacity = "<<vec5.capacity()<<"\n";
    // vec5.clear();
    // cout<<"after clear :\n";
    // cout<<"size = "<<vec5.size()<<" ,capacity = "<<vec5.capacity()<<"\n";


    //vector迭代器失效问题
    //因为vector动态扩容后会让原先迭代器指向位置失效，再次使用该迭代器会出现脏数据
    //解决方法再次使用之前重置迭代器
    cout<<"now vec2 = ";visit(vec2);
    cout<<"now vec4 = ";visit(vec4);
    vector<int>::iterator it = vec4.begin();
    ++it;
    ++it;
    cout<<"*it = "<<*it<<"\n";
    vec4.insert(it,vec2.begin(),vec2.end());
    visit(vec4);
    // 解决方法
    // it = vec4.begin();
    // ++it;
    // ++it;

    cout<<"*it = "<<*it<<"\n";

    //vector erase操作
    //细节不要漏元素
    cout<<"before erase: vec6 = ";visit(vec6);
    for(auto it = vec6.begin();it!=vec6.end();)
    {
        if(*it == 3)
        {
            vec6.erase(it);
        }
        else
        {
            ++it;
        }
    }
    cout<<"after erase: vec6 = ";visit(vec6);
}

int main(void)
{
    test0();
    return 0;
}