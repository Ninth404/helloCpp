#include "../include/Configuration.h"

#include <fstream>
#include <sstream>
#include <memory>

using std::ifstream;
using std::istringstream;

//饿汉式
Configuration * Configuration::_ptrCfg = nullptr;

Configuration::Configuration(){}

void Configuration::readConfigurationFile()
{
    ifstream ifs("../config/myconf.conf");

    string line;

    while(getline(ifs,line))
    {
        istringstream iss(line);

        string key,equal,value;

        iss>>key>>equal>>value;

        _cfg.insert({key,value});
    }

    ifs.close();
}

Configuration * Configuration::getInstance()
{
    if(_ptrCfg == nullptr)
    {
        _ptrCfg = new Configuration;
    }

    return _ptrCfg;
}

void Configuration::destory()
{
    if(_ptrCfg)
    {
        delete _ptrCfg;
        _ptrCfg = nullptr;
    }
}

string Configuration::getConfig(string key)
{
    if(_cfg.size() == 0)
    {
        readConfigurationFile();
    }

    unordered_map<string,string>::iterator it = _cfg.find(key);
    
    if(it == _cfg.end())
    {
        return "";
    }

    return it->second;
}

unordered_set<string> & Configuration::getStopWordSet()
{
    if(_stopWords.size() == 0)
    {
        readStopWordFile();
    }

    return _stopWords;
}


void Configuration::readStopWordFile()
{
    //中英停用词插入停用词集合

    ifstream zh_stop_words_ifs(_cfg["chinese_stop_words_file"]);
    ifstream en_stop_words_ifs(_cfg["english_stop_words_file"]);

    string stopWordsLine;

    while(en_stop_words_ifs>>stopWordsLine)
    {
        _stopWords.insert(stopWordsLine);
    }

    while(zh_stop_words_ifs>>stopWordsLine)
    {
        _stopWords.insert(stopWordsLine);
    }

    zh_stop_words_ifs.close();
    en_stop_words_ifs.close();
}