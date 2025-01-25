#include "myLogger.hh"

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
void test0()
{
    // g++ myLogger.cc main.cc -llog4cpp -lpthread

    LogDebug("this is debug");
    LogInfo("this is info");
    LogError("this is error");
    Mylogger::destory();
}

void test1()
{
   cout<<addPrefix("hello")<<endl; 
}
int main()
{
    test0();
    return 0;
}



