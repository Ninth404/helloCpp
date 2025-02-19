#include <iostream>
#include <memory>
#include <string>

using std::cout;
using std::unique_ptr;
using std::shared_ptr;
using std::string;

struct FILEDeleter
{
    void operator()(FILE * fp)
    {
        if(fp)
        {
            fclose(fp);
        }
    }
};

//针对unique_ptr 删除器在类模板
void test0()
{
    string msg = "hello,world\n";
    unique_ptr<FILE,FILEDeleter> up(fopen("test.txt","a+"));

    fwrite(msg.c_str(),1,msg.size(),up.get());
}

//针对shared_ptr 删除器在构造函数
void test1()
{
    string msg = "hello,world\n";
    
    shared_ptr<FILE> sp(fopen("test.txt","a+"),FILEDeleter());

    fwrite(msg.c_str(),1,msg.size(),sp.get());
}

int main()
{
    /* test0(); */
    test1();
    return 0;
}

