#ifndef __MYLOGGER_H__
#define __MYLOGGER_H__

#include <log4cpp/Category.hh>
#include <iostream>
#include <string>

using namespace log4cpp;

#define addPrefix(msg) string(" [ ").append(__FILE__)\
                                .append(" : ").append(__func__)\
                                .append(" : ").append(std::to_string(__LINE__))\
                                .append(" ] ").append(msg).c_str()

#define LogDebug(msg) Mylogger::getInstace()->debug(addPrefix(msg))

#define LogError(msg) Mylogger::getInstace()->error(addPrefix(msg))

#define LogInfo(msg) Mylogger::getInstace()->info(addPrefix(msg))

class Mylogger
{

public:
    static Mylogger *getInstace();
    static void destory();

    void warn(const char * msg);
    void error(const char * msg);
    void debug(const char * msg);
    void info(const char * msg);

private:
    Mylogger();
    ~Mylogger();

private:
    static Mylogger *_pInstance;
    Category & _mycat;

};

#endif
