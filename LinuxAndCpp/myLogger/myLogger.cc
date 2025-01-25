#include "myLogger.hh"
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Priority.hh>
#include <iostream>

using namespace std;
using namespace log4cpp;

Mylogger* Mylogger::getInstace()
{
    if(Mylogger::_pInstance == nullptr)
    {
        _pInstance = new Mylogger();

    }
    return _pInstance;
    
}

void Mylogger::destory()
{
    if(_pInstance)
    {
        delete _pInstance;
        _pInstance = nullptr;
    }
}

void Mylogger::warn(const char * msg)
{
    _mycat.warn(msg);
}

void Mylogger::error(const char * msg)
{
    _mycat.error(msg);
}

void Mylogger::debug(const char * msg)
{
    _mycat.debug(msg);
}

void Mylogger::info(const char * msg)
{
    _mycat.info(msg);
}

Mylogger::Mylogger()
:_mycat(Category::getRoot().getInstance("myroot"))
{
    // 格式化器
    PatternLayout *ppl1 = new PatternLayout();
    ppl1->setConversionPattern("%d %c [%p] %m%n");

    PatternLayout *ppl2 = new PatternLayout();
    ppl2->setConversionPattern("%d %c [%p] %m%n");
    
    PatternLayout *ppl3 = new PatternLayout();
    ppl3->setConversionPattern("%d %c [%p] %m%n");

    // 过滤器
    _mycat.setPriority(Priority::DEBUG);

    // 输出器
    OstreamAppender *pos = new OstreamAppender("consle",&cout);
    pos->setLayout(ppl1);

    FileAppender *fpos = new FileAppender("FileAppender","mylogger.log");
    fpos->setLayout(ppl2);
    
    RollingFileAppender *rpos = new RollingFileAppender("rollingfile",
                                                        "myrollingfile.log",
                                                        5 * 1024,
                                                        10);//回卷文件
    rpos->setLayout(ppl3);

    _mycat.addAppender(pos);
    _mycat.addAppender(fpos);
    _mycat.addAppender(rpos);
}

Mylogger::~Mylogger()
{
    Category::shutdown();
}

//“懒汉”创建
Mylogger *Mylogger::_pInstance = nullptr;

