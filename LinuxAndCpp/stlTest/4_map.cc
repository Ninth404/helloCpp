#include<iostream>
#include<map>
#include<string>

using std::cout;
using std::map;
using std::string;

//模板函数
template <class T>
void visitT(const T & con)
{
    for(auto & c : con)
    {
        cout<<c.second<<" ";
    }
    cout<<"\n";
}

void test0()
{
    map<string,int> mes = {{"hello",1},{"world",2}};
    cout<<"hello of value = "<<mes["hello"]<<"\n";

    std::pair<map<string,int>::iterator,bool> ret = mes.insert({"raoxu",2003});
    if(ret.second)
    {
        cout<<"insert success\n";
    }
    else
    {
        cout<<"insert fail\n";
    }

    cout<<"raoxu of value = "<<mes["raoxu"]<<"\n";

}

int main(void)
{
    test0();
    return 0;
}