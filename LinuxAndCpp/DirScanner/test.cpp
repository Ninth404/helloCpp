#include "DirScanner.h"

#include <iostream>

using std::cout;

int main()
{
    DirScanner dir_scanner;
    string dir(".");

    dir_scanner.traverse(dir);

    for(auto & ret : dir_scanner.getFiles())
    {
        cout<<ret<<" ";
    }
    cout<<"\n";

    return 0;
}

