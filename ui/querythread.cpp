#include "dict/def.h"
#include "querythread.h"

QueryThread::QueryThread(QObject *parent) :
    QThread(parent)
{
    _dict = new YoudaoDict("http://dict.youdao.com/search");
}

QueryThread::~QueryThread()
{
    if(_dict != nullptr) {
        delete _dict;
    }
}

void QueryThread::run()
{
    auto _dict = new YoudaoDict("http://dict.youdao.com/search");
    auto res = _dict->query(_word, 1);
    for (int i = res->size(); i > 0; i--) {
        LOGD("%s: %s", res->at(i - 1).session.c_str(), res->at(i - 1).value.c_str());
    }
    if (res->size() > 0){
        emit this->queryResult(res);
    }
        delete _dict;
    _dict = nullptr;
}

void QueryThread::query(std::string word)
{
    this->_word = word;
    this->start();
}
