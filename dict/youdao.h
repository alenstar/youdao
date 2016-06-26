#ifndef YOUDAO_H
#define YOUDAO_H
#include "dict.h"
#include <map>
#include <cpr/cpr.h>

class YoudaoDict:public dict::Dict {
private:
    std::string m_url;
    std::map<std::string, std::string> m_params;
    std::map<std::string, std::string> m_headers;
    //Barbeque* m_bbq { new Barbeque()};
public:
     ~YoudaoDict(){
        /*
         if (m_bbq) {
            delete m_bbq;
         }
         */
     }

    YoudaoDict();
    YoudaoDict(const char* url);
    YoudaoDict(std::string& url);

    dict::ResultVectorPtr query(const char* word, int tyep = 0);
    dict::ResultVectorPtr query(std::string word, int type = 0);
};

#endif
