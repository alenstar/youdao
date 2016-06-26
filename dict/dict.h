#ifndef DICTCLASS_H
#define DICTCLASS_H
#include "dict.cpp"

#include <memory>
#include <iostream>
#include <vector>
#include <map>

namespace dict {
class Dict {

};

class Result {
public:
    std::string value;
    std::string session;

    Result() {}
    Result(std::string& session, std::string& val) {
        this->value = val;
        this->session = session;
    }
};

class ResultVector {
private:
    std::vector<Result*> m_list;

public:
    ~ResultVector() {
        for (auto v : m_list) {
            if (v) {
                delete v;
            }
        }
    }

   const Result& at(int idx) {
       if (idx < m_list.size()) {
            return *m_list[idx];
       }
       return Result();
   }

   inline Result& operator [] (int idx) const {
       if (idx < m_list.size()) {
            return *m_list[idx];
       }
       Result res;
       return res;
   }

   inline void insert(std::string session, std::string val) {
       Result* res = new Result(session, val);
       m_list.push_back(res);
   }

   inline size_t length() {
       return m_list.size();
   }

   inline size_t size() {
       return m_list.size();
   }
};

typedef std::shared_ptr<ResultVector> ResultVectorPtr;
};
#endif
