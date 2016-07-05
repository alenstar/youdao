#include "dict/youdao.h"
#include "def.h"

#include "easylogging++.h"
INITIALIZE_EASYLOGGINGPP

#include <QApplication>

int main(int argc , const char** argv) {
    std::string word;
    if (argc < 2) {
        //exit(0);
        //printf("usage: %s word\n", argv[0]);
    } else {
        for (int i = 1; i < argc ; i++) {
            if (word.size()) {
            word = word + " " + std::string(argv[i]);
        } else {
                word = std::string(argv[i]);
            }

            }
    }
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime %func[%fbase] %level: %msg");

    YoudaoDict dict("http://dict.youdao.com/search");
    auto res = dict.query(word, 1);
    for (int i = res->size(); i > 0; i--) {
        LOGD("%s: %s", res->at(i - 1).session.c_str(), res->at(i - 1).value.c_str());
        printf("%s: %s\n", res->at(i - 1).session.c_str(), res->at(i - 1).value.c_str());
    }
	return 0;
}
