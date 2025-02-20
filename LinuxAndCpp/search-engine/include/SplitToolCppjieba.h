#ifndef __SPLIT_TOOL_CPP_JIEBA__
#define __SPLIT_TOOL_CPP_JIEBA__

#include "Configuration.h"
#include "SplitTool.h"
#include "simhash/cppjieba/Jieba.hpp"

class SplitToolCppjieba : public SplitTool
{
public:
    SplitToolCppjieba();
    
    ~SplitToolCppjieba();

    virtual vector<string> cut(const string & file_content) override;
    
private:
    cppjieba::Jieba * _jieba;
};

#endif