#include "DirScanner.h"

vector<string> & DirScanner::getFiles()
{
    return _files;
}

void DirScanner::traverse(string dir)
{
    DIR* p_dir = opendir(dir.c_str());

    if(p_dir == nullptr)
    {
        perror("DirScanner::traverse -> opendir");
        return;
    }

    struct dirent * p_dirent = nullptr;

    while((p_dirent = readdir(p_dir)))
    {
        if(strcmp(p_dirent->d_name,".") == 0 || strcmp(p_dirent->d_name,"..") == 0)
        {
            // 跳过 当前目录 和 上级目录 
            continue;
        }

        if(p_dirent->d_type == DT_DIR)
        {
            //如果文件为 目录文件 则递归继续调用
            traverse(dir + "/" + p_dirent->d_name);
        }
        else
        {
            _files.emplace_back(dir+"/"+p_dirent->d_name);
        }
    }
}
