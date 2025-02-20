#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include <unordered_map>
#include <unordered_set>
#include <string>

using std::unordered_map;
using std::unordered_set;
using std::string;

//单例模式
class Configuration
{
public:
    static Configuration * getInstance();

    static void destory();

    string getConfig(string key);

    unordered_set<string> & getStopWordSet();

private:
    Configuration();
    
    Configuration(const Configuration & rhs) = delete;
    Configuration(const Configuration && rhs) = delete;

    Configuration & operator=(const Configuration & rhs) = delete;
    Configuration & operator=(const Configuration && rhs) = delete;

private:
    void readConfigurationFile();

    void readStopWordFile();

private:
    static Configuration *_ptrCfg;

    unordered_map<string,string> _cfg;

    unordered_set<string> _stopWords;
};

#endif
