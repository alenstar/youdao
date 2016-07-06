#ifndef QUERYTHREAD_H
#define QUERYTHREAD_H

#include <QThread>
#include "dict/youdao.h"

class QueryThread : public QThread
{
    Q_OBJECT
public:
    explicit QueryThread(QObject *parent = 0);
    ~QueryThread();
    void run();
    void query(std::string word);
signals:
    void queryResult(dict::ResultVectorPtr ptr);
public slots:

private:
    YoudaoDict* _dict;
    std::string _word;
};

#endif // QUERYTHREAD_H
