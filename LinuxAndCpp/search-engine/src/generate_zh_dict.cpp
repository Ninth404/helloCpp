#include "../include/Configuration.h"
#include "../include/SplitToolCppjieba.h"
#include "../include/DicProducer.h"

int main(void)
{
    string chinese_corpus_dir = Configuration::getInstance()->getConfig("chinese_corpus_dir");

    string chinese_stop_wrods_file = Configuration::getInstance()->getConfig("chinese_stop_words_file");

    SplitToolCppjieba jb;

    DicProducer zh_dict(chinese_corpus_dir, chinese_stop_wrods_file, SE_LT_Chinese, &jb);

    zh_dict.generateAllFiles();

    return 0;
}
