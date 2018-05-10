#ifndef QUERYDIALOG_H
#define QUERYDIALOG_H

#include <QDialog>
#include <QTextToSpeech>
#include "dict/dict.h"
#include "mdialog.h"
namespace Ui {
class QueryDialog;
}

class QueryDialog : public MDialog
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
private slots:
    void on_phoneticBtn_clicked();

private:
    Ui::QueryDialog *ui;
    QTextToSpeech* speech;
};

#endif // QUERYDIALOG_H
