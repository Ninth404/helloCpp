#ifndef __DICPRODUCER__
#define __DICPRODUCER__

#include "Configuration.h"
#include "SplitTool.h"

#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <string>

using std::vector;
using std::map;
using std::set;
using std::pair;
using std::unordered_set;
using std::string;

enum LanguageType{
    SE_LT_English = 0,
    SE_LT_Chinese
};

class DicProducer
{
public:
    DicProducer(const string & corpusPath,
                const string & stopWordsPath,
                LanguageType language,
                SplitTool *tool = nullptr);
public:
    void generateAllFiles();

    void generateDictFile();

    void generateDictIndexFile();

private:
    void readCorpusFiles(const string corpus_file_dir_path);
    
    void initStopWordSet(const string stop_word_file_path);

    bool isStopWord(const string & word);

    void buildEnglishDict();

    void buildChineseDict();

    void createDictIndex();

    void storeDictFile();

    void storeDictIndexFile();

    size_t nBytesCode(char ch);

    void saveWord(map<string, int> & temp_dict);

    void extractEnglishWord(string & word);

    bool isChinese(char ch);

    void extractChineseWord(string & word);

private:
    LanguageType _language;//语言类型
    
    vector<string> _files;//语料库文件的绝对路径地址

    SplitTool * _cuttor;//分词工具

    map<string,set<int>> _index;//位置索引 存储词，存储词在字典中出现位置信息

    vector<pair<string,int>> _dict;// {word,frequence}词频字典

    unordered_set<string> _stopWords; //停用词集合
};

#endif