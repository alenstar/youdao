#ifndef QUERYDIALOG_H
#define QUERYDIALOG_H

#include <QDialog>
#include "querythread.h"

namespace Ui {
class QueryDialog;
}

class QueryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QueryDialog(QWidget *parent = 0);
    ~QueryDialog();

private slots:
    void on_lineEdit_returnPressed();
    void queryResult(dict::ResultVectorPtr ptr);
private:
    Ui::QueryDialog *ui;
    QueryThread* _query;
};

#endif // QUERYDIALOG_H
