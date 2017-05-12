#ifndef QUERYDIALOG_H
#define QUERYDIALOG_H

#include <QDialog>
#include "dict/dict.h"

namespace Ui {
class QueryDialog;
}

class QueryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QueryDialog(QWidget *parent = 0);
    ~QueryDialog();
public slots:
    void on_lineEdit_returnPressed();
    void onShowExplain(dict::ResultVectorPtr ptr);
    void showExplain(dict::ResultVectorPtr ptr);
signals:
    void doShowExplain(dict::ResultVectorPtr ptr);
private:
    Ui::QueryDialog *ui;
};

#endif // QUERYDIALOG_H
