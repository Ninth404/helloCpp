#ifndef __SPLIT_TOOL_H__
#define __SPLIT_TOOL_H__

#include<vector>
#include<string>

using std::vector;
using std::string;

class SplitTool
{
public:
    SplitTool(){};

    virtual ~SplitTool(){};

    virtual vector<string> cut(const string & file_content) = 0;
};

#endif