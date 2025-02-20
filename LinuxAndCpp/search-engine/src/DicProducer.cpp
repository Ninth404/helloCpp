#include "../include/DicProducer.h"

#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <string>
#include <fstream>

using std::cout;
using std::string;
using std::ifstream;
using std::ofstream;

DicProducer::DicProducer(const string & corpusPath,const string & stopWordsPath,LanguageType language,SplitTool *tool)
:_language(language)
,_cuttor(tool)
{
    readCorpusFiles(corpusPath);
    initStopWordSet(stopWordsPath);
}

void DicProducer::generateAllFiles()
{
    generateDictFile();
    generateDictIndexFile();
}

void DicProducer::generateDictFile()
{
    switch (_language)
    {
    case SE_LT_English:buildEnglishDict();break;
    case SE_LT_Chinese:buildChineseDict();break;
    default:
        break;
    }

    storeDictFile();
}

void DicProducer::generateDictIndexFile()
{
    createDictIndex();
    storeDictIndexFile();
}

void DicProducer::readCorpusFiles(const string corpus_file_dir_path)
{
    DIR * pCorpusdir = opendir(corpus_file_dir_path.c_str());

    if(pCorpusdir == nullptr)
    {
        perror("DictProducer::readCorpusFiles -> opendir");
        return;
    }

    struct dirent * pDirent = nullptr;
    
    while((pDirent = readdir(pCorpusdir)) != nullptr)
    {
        
        if(strcmp(pDirent->d_name,".") == 0 || strcmp(pDirent->d_name,"..")== 0)
        {
            //跳过.和..目录
            continue;
        }

        if(pDirent->d_type == DT_DIR)
        {
            readCorpusFiles(corpus_file_dir_path + "/" + pDirent->d_name);
        }
        else
        {
            _files.emplace_back(corpus_file_dir_path + "/" + pDirent->d_name);
        }
    }

    closedir(pCorpusdir);
    
}

void DicProducer::initStopWordSet(const string stop_word_file_path)
{
    ifstream ifs(stop_word_file_path);

    string stopWords;

    while(ifs>>stopWords)
    {
        _stopWords.insert(stopWords);
    }

    ifs.close();
    cout<<"[INFO] : Load stop words File : " <<stop_word_file_path<<"Success...\n\n";
}

bool DicProducer::isStopWord(const string & word)
{
    unordered_set<string>::iterator targetIt = _stopWords.find(word);
    
    if(targetIt == _stopWords.end())
    {
        return false;
    }
    else
    {
        return true;
    }
}

void DicProducer::buildEnglishDict()
{
    cout<<"[INFO] : Build English Dict begin ...\n";

    map<string,int> temp_dict;

    for(auto & file_name : _files)
    {
        ifstream ifs(file_name);

        string word;

        while(ifs>>word)
        {
            extractEnglishWord(word);

            if(word == "") continue;

            if(!isStopWord(word))
            {
                ++temp_dict[word];
            }
        }

        ifs.close();

        cout<<"\t -> "<<file_name<<"success...\n";
    }

    saveWord(temp_dict);

    cout<<"[INFO] : Build English Dict Success ...\n\n";
}

void DicProducer::buildChineseDict()
{
    cout << "[INFO] : Build Chinese Dict begin...\n"
         << "[INFO] : Load Files...\n";

    map<string, int> temp_dict;

    for(auto & file_name : _files)
    {
        ifstream ifs(file_name);

        string temp, content;

        while(ifs >> temp)
        {
            extractChineseWord(temp);
            content += temp;
        }

        vector<string> split_res = _cuttor->cut(content);

        // map<string, int> temp_dict;

        for(auto & word : split_res)
        {
            if(!isStopWord(word))
            {
                temp_dict[word]++;
            }
        }

        // saveWord(temp_dict);

        ifs.close();

        cout << "\t-> " << file_name << " success\n";
    }

    saveWord(temp_dict);

    cout << "[INFO] : Build Chinese Dict Success...\n\n";
}


void DicProducer::createDictIndex()
{

    size_t dictSize = _dict.size();

    for(size_t idx = 0;idx<dictSize;++idx)
    {
        string word = _dict[idx].first;

        size_t ch_num = word.size() / nBytesCode(word[0]);

        for(size_t j = 0,pos = 0;j<ch_num;++j)
        {
            size_t cur_ch_bytes = nBytesCode(word[pos]);

            _index[word.substr(pos, cur_ch_bytes)].insert(idx);

            pos += cur_ch_bytes;
        }
    }
}

void DicProducer::storeDictFile()
{
    ofstream ofs;

    string dict_file_path = "../data/dat/";

    switch ((_language))
    {
    case SE_LT_English:
        dict_file_path += "en_dict.dat";
        break;
    case SE_LT_Chinese:
        dict_file_path += "zh_dict.dat";
        break;
    default:
        break;
    }

    ofs.open(dict_file_path);

    cout<<"[INFO] : Store Dict File ->"<<dict_file_path<<"\n";
    for(size_t idx = 0; idx < _dict.size();++idx)
    {
        ofs << _dict[idx].first << " " << _dict[idx].second << "\n";
    }

    ofs.close();
    cout << "[INFO] : Store Dict File Success...\n\n";
}

void DicProducer::storeDictIndexFile()
{
    ofstream ofs;
    string dict_index_file_path ="../data/dat/";

    switch (_language)
    {
    case SE_LT_English : dict_index_file_path += "en_dict_index.dat"; break;    
    case SE_LT_Chinese : dict_index_file_path += "zh_dict_index.dat"; break;
    default:
        break;
    }

    ofs.open(dict_index_file_path);

    cout << "[INFO] : Store Dict Index File -> " << dict_index_file_path << "\n";

    map<string,set<int>>::iterator it = _index.begin();

    while(it != _index.end())
    {
        ofs<<it->first;
        
        for(auto pos : it->second)
        {
            ofs<<" "<<pos;
        }

        ofs<<"\n";

        ++it;
    }

    ofs.close();

    cout << "[INFO] : Store Dict Index File Success...\n\n";
}

size_t DicProducer::nBytesCode(char ch)
{
    if(ch & 0x80)
    {
        int bytes = 1;
        
        for(int i = 0; i != 6; i++)
        {
            if(ch & (1 << (6 - i)))
            {
                bytes++;
            }
            else
            {
                break;
            }
        }

        return bytes;
    }

    return 1;
}

void DicProducer::saveWord(map<string, int> & temp_dict)
{
    for(auto & mit : temp_dict)
    {
        _dict.emplace_back(mit);
    }
}

void DicProducer::extractEnglishWord(string & word)
{
    auto it = word.begin();

    while(it != word.end())
    {
        if(isalpha(*it))
        {
            if(isupper(*it))
            {
                *it = tolower(*it);
            }
            ++it;
        }
        else
        {
            it = word.erase(it);
        }
    }
}

bool DicProducer::isChinese(char ch)
{
    return 0x80 & ch;
}

void DicProducer::extractChineseWord(string & word)
{
    for(size_t i = 0; i < word.size();)
    {
        size_t bytes = nBytesCode(word[i]);

        if(!isChinese(word[i]))
        {
            word.erase(i, bytes);
            continue;
        }

        i += bytes;
    }
}